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
 * @file   AmqpManagedExampleApp.cpp
 * @author Scott Brauer
 * @date   04-15-2021
 */

#include <iostream>
#include <regex>

#include "easylogging++.h"

#include "offcenter/common/InterruptHandler.hpp"
using namespace offcenter::common;

#include "offcenter/amqp/Listener.hpp"
#include "offcenter/amqp/URLSchemeHost.hpp"
#include "offcenter/amqp/ProducerMessageProducer.hpp"

using namespace offcenter;

#include "AmqpManagedExampleApp.hpp"

AmqpManagedExampleApp::AmqpManagedExampleApp():
		IAmqpManagedServerApp()
{

}

AmqpManagedExampleApp::~AmqpManagedExampleApp() {
	// TODO Auto-generated destructor stub
}

void AmqpManagedExampleApp::onInitProgramOptions(
        program_options::ProgramOptionsManager &optionsManager)
{
	m_amqpOption = optionsManager.add<AmqpExampleProgramOptions>();
}

void AmqpManagedExampleApp::onInitAMQP(amqp::ConnectionURIOptions& options)
{
	amqp::URLSchemeHost tcpHost(amqp::URLSchemeHost::URLScheme::tcp, m_amqpOption->tcpHost());
	options.protocol.setTCPProtocol(tcpHost);
	options.connection.sendTimeout = m_amqpOption->connectionSendTimeout();
	options.failoverTransport.timeout = m_amqpOption->failoverTransportTimeout();
	LOG(INFO) << "AMQP URI: " << options.uri();
}

void AmqpManagedExampleApp::onInitAMQPSessions(amqp::ConnectionPtr connection)
{
	// Create a Session
	m_session = offcenter::amqp::helper::sessionFactory(connection->createSession(cms::Session::AUTO_ACKNOWLEDGE));

}


void AmqpManagedExampleApp::onSetUp()
{
}

void AmqpManagedExampleApp::onExecute()
{
	// Create the destination (Topic or Queue)
	offcenter::amqp::DestinationPtr inputDestination = offcenter::amqp::helper::destinationFactory(m_session->createTopic("offcenter.test.input"));
	offcenter::amqp::DestinationPtr outputDestination = offcenter::amqp::helper::destinationFactory(m_session->createTopic("offcenter.test.output"));

	offcenter::amqp::MessageConsumerPtr consumer1 = offcenter::amqp::helper::messageConsumerFactory(m_session->createConsumer(inputDestination.get()));
	offcenter::amqp::ProducerMessageHandler producer1(m_session, outputDestination);
	producer1()->setDeliveryMode(cms::DeliveryMode::NON_PERSISTENT);

	offcenter::amqp::MessageConsumerPtr consumer2 = offcenter::amqp::helper::messageConsumerFactory(m_session->createConsumer(inputDestination.get()));
	offcenter::amqp::ProducerMessageHandler producer2(m_session, outputDestination);
	producer2()->setDeliveryMode(cms::DeliveryMode::NON_PERSISTENT);

	offcenter::amqp::Listener<AmqpDataElementInner, AmqpDataElementInner::MessageType> listener1(
			consumer1,
			[&producer1](const cms::Message *cmsMessage, const AmqpDataElementInner& amqpInner) {
				std::cout << "Receive message 1 (AmqpDataElement): "
						<< amqpInner.name << " : "
						<< amqpInner.description << " : "
						<< amqpInner.date << " : "
						<< amqpInner.value
						<< std::endl;

				AmqpDataElementOuter amqpOuter;
				amqpOuter = amqpInner;
				producer1.send(amqpOuter);
	});

	offcenter::amqp::Listener<AmqpDataElementInner, AmqpDataElementInner::MessageType> listener2(
			consumer2,
			[&producer2](const cms::Message *cmsMessage, const AmqpDataElementInner& amqpInner) {
				std::cout << "Receive message 2 (AmqpDataElement): "
						<< amqpInner.name << " : "
						<< amqpInner.description << " : "
						<< amqpInner.date << " : "
						<< amqpInner.value
						<< std::endl;

				AmqpDataElementOuter amqpOuter;
				amqpOuter = amqpInner;
				producer2.send(amqpOuter);
	});

	offcenter::common::interrupthandler::waitForUserInterrupt();

	LOG(DEBUG) << "Close consumers";
	consumer2->close();
	consumer2.reset();
	consumer1->close();
	consumer1.reset();
	LOG(DEBUG) << "Close destinations";
	inputDestination.reset();
	outputDestination.reset();
}

void AmqpManagedExampleApp::onTearDown()
{
	LOG(DEBUG) << "Close session";
	m_session->close();
	m_session.reset();
}

void AmqpManagedExampleApp::onHelp(const std::string &help)
{
}

void AmqpManagedExampleApp::onVersion()
{
}

void AmqpManagedExampleApp::onStart()
{
}

void AmqpManagedExampleApp::onStop()
{
}

void AmqpManagedExampleApp::onPause()
{
}

void AmqpManagedExampleApp::onResume()
{
}
