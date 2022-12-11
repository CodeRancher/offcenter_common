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
 * @file   AmqpConsumerExampleApp.cpp
 * @author Scott Brauer
 * @date   04-15-2021
 */

#include <iostream>
#include <regex>

#include "easylogging++.h"

#include "offcenter/common/InterruptHandler.hpp"
using namespace offcenter::common;

#include "offcenter/common/amqp/Listener.hpp"
#include "offcenter/common/amqp/URLSchemeHost.hpp"
using namespace offcenter;

#include "AmqpConsumerExampleApp.hpp"



PersistOandaForexDataToCSV::PersistOandaForexDataToCSV():
	IAmqpServerApp()
{

}

PersistOandaForexDataToCSV::~PersistOandaForexDataToCSV() {
	// TODO Auto-generated destructor stub
}

void PersistOandaForexDataToCSV::onInitProgramOptions(
		program_options::ProgramOptionsManager &optionsManager)
{
	m_amqpOption = optionsManager.add<AmqpExampleProgramOptions>();
}

void PersistOandaForexDataToCSV::onInitAMQP(amqp::ConnectionURIOptions& options)
{
	amqp::URLSchemeHost tcpHost(amqp::URLSchemeHost::URLScheme::tcp, m_amqpOption->tcpHost());
	options.protocol.setTCPProtocol(tcpHost);
	options.connection.sendTimeout = m_amqpOption->connectionSendTimeout();
	options.failoverTransport.timeout = m_amqpOption->failoverTransportTimeout();
	LOG(INFO) << "AMQP URI: " << options.uri();
}

void PersistOandaForexDataToCSV::onInitAMQPSessions(amqp::ConnectionPtr connection)
{
	// Create a Session
	m_session = offcenter::amqp::helper::sessionFactory(connection->createSession(cms::Session::AUTO_ACKNOWLEDGE));

	// Create the destination (Topic or Queue)
	m_destination = offcenter::amqp::helper::destinationFactory(m_session->createTopic("offcenter.test.output"));
}


void PersistOandaForexDataToCSV::onSetUp()
{
}

void PersistOandaForexDataToCSV::onExecute()
{
	offcenter::amqp::MessageConsumerPtr consumer1 = offcenter::amqp::helper::messageConsumerFactory(m_session->createConsumer(m_destination.get()));

	/*
	offcenter::amqp::Listener<AmqpDataElementOuter, AmqpDataElementOuter::MessageType> listener1(
			consumer1,
			[](const cms::Message *cmsMessage, const AmqpDataElementOuter& amqpMessage) {
				std::cout << "Receive message 1 (AmqpDataElement): "
						<< amqpMessage.name << " : "
						<< amqpMessage.description << " : "
						<< amqpMessage.date << " : "
						<< amqpMessage.value << " : "
						<< amqpMessage.dateSquare << " : "
						<< amqpMessage.valueSquare
						<< std::endl;
	});
*/
	offcenter::amqp::MessageConsumerPtr consumer2 = offcenter::amqp::helper::messageConsumerFactory(m_session->createConsumer(m_destination.get()));
	/*
	offcenter::amqp::Listener<AmqpDataElementOuter, AmqpDataElementOuter::MessageType> listener2(
			consumer2,
			[](const cms::Message *cmsMessage, const AmqpDataElementOuter& amqpMessage) {
				std::cout << "Receive message 2 (AmqpDataElement): "
						<< amqpMessage.name << " : "
						<< amqpMessage.description << " : "
						<< amqpMessage.date << " : "
						<< amqpMessage.value << " : "
						<< amqpMessage.dateSquare << " : "
						<< amqpMessage.valueSquare
						<< std::endl;
	});
	*/

	offcenter::common::interrupthandler::waitForUserInterrupt();

	consumer2->close();
	consumer2.reset();
	consumer1->close();
	consumer1.reset();
}


void PersistOandaForexDataToCSV::onTearDown()
{
	LOG(DEBUG) << "Close consumer";
	LOG(DEBUG) << "Close destination";
	m_destination.reset();
	LOG(DEBUG) << "Close session";
	m_session->close();
	m_session.reset();
}

void PersistOandaForexDataToCSV::onHelp(const std::string &help)
{

}

void PersistOandaForexDataToCSV::onVersion()
{
}
