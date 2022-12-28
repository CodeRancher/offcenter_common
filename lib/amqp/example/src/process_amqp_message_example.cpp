/**
 * Copyright 2021 Scott Brauer
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an  BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

/**
 * @file   process_amqp_message_example.cpp
 * @author Scott Brauer
 * @date   10-17-2021
 */

#include <cms/MapMessage.h>

#include "easylogging++.h"

INITIALIZE_EASYLOGGINGPP

#include "offcenter/common/amqp/threading/ProcessAmqpMessageThread.hpp"
#include "offcenter/common/amqp/Helper.hpp"
#include "offcenter/common/amqp/ProducerMessageProducer.hpp"
#include "offcenter/common/amqp/ActiveMQCPP.hpp"

/*
 * A thread safe print method
 *
 * value - The string to print
 */
void printString(const std::string& value) {
	static std::mutex printMutex;

	std::lock_guard<std::mutex> lock {printMutex};
	std::cout << value << std::endl;
}

/**
 * Example data element
 */
struct ExampleData {
	int start;
	int end;

	using MessageType = cms::MapMessage;
};

void to_cmsMessage(ExampleData::MessageType* j, const ExampleData& p) {
	j->setInt("start", p.start);
	j->setInt("end", p.end);
}

void from_cmsMessage(const ExampleData::MessageType* j, ExampleData& p) {
	p.start = j->getInt("start");
	p.end = j->getInt("end");
}

/*
 * This example is a counter. It will listen on a topic for an new max number to reach. Once that number is reached,
 * it will block until a new max is received.
 */
class ExampleThread:
		public offcenter::common::amqp::threading::ProcessAmqpMessageThread<ExampleData, ExampleData::MessageType>
{
public:
	ExampleThread() = delete;
	explicit ExampleThread(offcenter::common::amqp::SessionPtr session, const std::string& topic):
		ProcessAmqpMessageThread(session, topic),
		m_current(0)
	{}
	virtual ~ExampleThread() = default;

protected:
	/*
	 * This is called when a new data element is received.
	 */
	void onNewData() override {
		::printString("onNewData: " + std::to_string(data().start) + ", " + std::to_string(data().end));
		LOG(INFO) << "onNewData: " << data().start << ", " << data().end;
		if (m_current < data().end) {
			// A new max has been received so unblock and count
			unblock();
		}
	}

	/*
	 * This is called to process the next data element. When there are no more data elements to process,
	 * the task manager will be blocked.
	 */
	void task() override {
		m_current++;
		LOG(INFO) << "Task: " << "Current(" << m_current << ") End(" << data().end << ")";
		// If before at at max, process element
		if (m_current <= data().end) {
			::printString("Current: " + std::to_string(m_current));
			LOG(INFO) << "Current: " << m_current;
		}

		// If at or past max block. We should never be past max.
		if (m_current >= data().end) {
			block();
			::printString("Blocking: " + std::to_string(m_current));
			LOG(INFO) << "Blocking: " << m_current;
		}
	}

	void stopped() override {
		::printString("ExampleThread: Stopped");
	}

private:
	int m_current;
};

/**
 *
 */
int main(int argc, char* argv[])
{
	START_EASYLOGGINGPP(argc, argv);

	std::cout << "Process Amqp Message Example!" << std::endl;

	el::Loggers::reconfigureAllLoggers(el::ConfigurationType::ToFile, "true");
	el::Loggers::reconfigureAllLoggers(el::ConfigurationType::ToStandardOutput, "false");
	el::Loggers::reconfigureAllLoggers(el::ConfigurationType::Format, "%datetime:%thread [%level] %msg");
	el::Loggers::reconfigureAllLoggers(el::ConfigurationType::Filename, "./process_amqp_message_example.log");

	LOG(INFO) << "--------------------------------------------------------------------------------";

	offcenter::common::amqp::ActiveMQCPP activeMQCpp;

	std::string brokerURI = "tcp://rpiactivemq:61616?connection.sendTimeout=100&timeout=100";
	offcenter::common::amqp::ConnectionPtr connection;
	{
		// Create a ConnectionFactory
		offcenter::common::amqp::ActiveMQConnectionFactoryPtr connectionFactory(offcenter::common::amqp::helper::activeMQConnectionFactoryFactory(brokerURI));
		// Create a Connection
		connection = offcenter::common::amqp::helper::connectionFactory(connectionFactory->createConnection());
	}

	connection->start();

	offcenter::common::amqp::SessionPtr session = offcenter::common::amqp::helper::sessionFactory(connection->createSession(cms::Session::AUTO_ACKNOWLEDGE));
	offcenter::common::amqp::DestinationPtr outputDestination = offcenter::common::amqp::helper::destinationFactory(session->createTopic("process.amqp.message.example"));
	offcenter::common::amqp::ProducerMessageHandler producer(session, outputDestination);
	producer()->setDeliveryMode(cms::DeliveryMode::NON_PERSISTENT);

	LOG(DEBUG) << "Starting thread";
	int millisecondsSleep = 500;
	auto thread = std::make_unique<ExampleThread>(session, "process.amqp.message.example");
	thread->run();

	ExampleData data {0, 0};
	std::this_thread::sleep_for(std::chrono::milliseconds(millisecondsSleep));
	data.end += 3;
	producer.send(data);

	std::this_thread::sleep_for(std::chrono::milliseconds(millisecondsSleep));
	data.end += 0;
	producer.send(data);

	std::this_thread::sleep_for(std::chrono::milliseconds(millisecondsSleep));
	data.end += 20;
	producer.send(data);

	std::this_thread::sleep_for(std::chrono::milliseconds(millisecondsSleep));
	data.end += 100;
	producer.send(data);

	data.end += 20;
	producer.send(data);

	std::this_thread::sleep_for(std::chrono::milliseconds(millisecondsSleep));
	LOG(DEBUG) << "Stopping thread";
	thread->stop();
	thread->join();

	LOG(DEBUG) << "Close connection";
	connection->close();

	LOG(DEBUG) << "main exit";
}
