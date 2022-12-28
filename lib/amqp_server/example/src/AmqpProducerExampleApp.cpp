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
 * @file   AmqpProducerExampleApp.cpp
 * @author Scott Brauer
 * @date   04-15-2021
 */

#include <iostream>
#include <regex>
#include <string>

#include "easylogging++.h"

#include "offcenter/common/amqp/URLSchemeHost.hpp"
using namespace offcenter;

#include "AmqpProducerExampleApp.hpp"
#include "AmqpDataElement.hpp"

AmqpProducerExampleApp::AmqpProducerExampleApp():
	IAmqpServerApp(),
	m_amqpOption(),
	m_session(),
	m_destination()//,
	//m_producer()
{

}

AmqpProducerExampleApp::~AmqpProducerExampleApp() {
	// TODO Auto-generated destructor stub
}

void AmqpProducerExampleApp::onInitProgramOptions(offcenter::common::program_options::ProgramOptionsManager &optionsManager)
{
	m_amqpOption = optionsManager.add<AmqpExampleProgramOptions>();
}

void AmqpProducerExampleApp::onInitAMQP(offcenter::common::amqp::ConnectionURIOptions& options) {

	offcenter::common::amqp::URLSchemeHost tcpHost(offcenter::common::amqp::URLSchemeHost::URLScheme::tcp, m_amqpOption->tcpHost());
	options.protocol.setTCPProtocol(tcpHost);
	options.connection.sendTimeout = m_amqpOption->connectionSendTimeout();
	options.failoverTransport.timeout = m_amqpOption->failoverTransportTimeout();
	LOG(INFO) << "AMQP URI: " << options.uri();
}

void AmqpProducerExampleApp::onInitAMQPSessions(offcenter::common::amqp::ConnectionPtr connection) {
	// Create a Session
	m_session = offcenter::common::amqp::helper::sessionFactory(connection->createSession(cms::Session::AUTO_ACKNOWLEDGE));

	// Create the destination (Topic or Queue)
	m_destination = offcenter::common::amqp::helper::destinationFactory(m_session->createTopic("offcenter.test.input"));
}


void AmqpProducerExampleApp::onSetUp()
{
}

void AmqpProducerExampleApp::onExecute()
{
	offcenter::common::amqp::ProducerMessageHandler producer(m_session, m_destination);
	producer()->setDeliveryMode(cms::DeliveryMode::NON_PERSISTENT);

	for (int cnt = 1; cnt <= 100; cnt++) {
		std::string name = "Inner:" + std::to_string(cnt);
		std::string description = "Description" + std::to_string(cnt);
		float flt = static_cast <float> (rand()) / (static_cast <float> (RAND_MAX/100.0));
		AmqpDataElementInner dataElement1 = { name, description, cnt, flt };
		std::cout << "Send message (AmqpDataElement): "
				<< dataElement1.name << " : "
				<< dataElement1.description << " : "
				<< dataElement1.date << " : "
				<< dataElement1.value << std::endl;

		producer.send(dataElement1);
	}
}

void AmqpProducerExampleApp::onTearDown()
{
	LOG(DEBUG) << "Close consumer";
	LOG(DEBUG) << "Close destination";
	m_destination.reset();
	LOG(DEBUG) << "Close session";
	m_session->close();
	m_session.reset();
}

void AmqpProducerExampleApp::onHelp(const std::string &help)
{
}

void AmqpProducerExampleApp::onVersion()
{
}
