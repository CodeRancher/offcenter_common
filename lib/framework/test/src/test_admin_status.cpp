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
 * @file   test_admin_status.cpp
 * @author Scott Brauer
 * @date   04-27-2019
 */

#include <gtest/gtest.h>

#include "easylogging++.h"

#include "offcenter/common/framework/admin/AdminStatusProducer.hpp"
#include "offcenter/common/framework/admin/AdminStatusConsumer.hpp"
#include "offcenter/common/framework/admin/AdminStatusMessage.hpp"
#include "offcenter/common/WaitForMessage.hpp"

//*****************************************************************************
class AdminStatusFixture : public ::testing::Test {
public:
	explicit AdminStatusFixture() {
		activemq::library::ActiveMQCPP::initializeLibrary();

		offcenter::amqp::ConnectionURIOptions options;
		offcenter::amqp::URLSchemeHost tcpHost(offcenter::amqp::URLSchemeHost::URLScheme::tcp, "rpiactivemq");
		options.protocol.setTCPProtocol(tcpHost);
		options.connection.sendTimeout = 1000;
		options.failoverTransport.timeout = 1000;

		// Connect to the AMQP server
		LOG(DEBUG) << "Open Connection Factory";
		offcenter::amqp::ActiveMQConnectionFactoryPtr connectionFactory(offcenter::amqp::helper::activeMQConnectionFactoryFactory(options.uri()));

	    // Create a Connection
		LOG(DEBUG) << "Open Connection";
		m_connection = offcenter::amqp::helper::connectionFactory(connectionFactory->createConnection());

		offcenter::amqp::ConnectionSettings connectionSettings(
				cms::Session::AcknowledgeMode::AUTO_ACKNOWLEDGE,
				offcenter::amqp::ConnectionSettings::QueueType::Topic,
				"offcenter.test.AdminControl");

		m_statusProducer = offcenter::common::framework::admin::AdminStatusProducer::factory(
				offcenter::amqp::SessionProducer::factory(m_connection, connectionSettings),
				"test_admin_status");

		m_statusConsumer = offcenter::common::framework::admin::AdminStatusConsumer::factory(
				offcenter::amqp::SessionConsumer::factory(m_connection, connectionSettings),
				[&m_statusMessage=m_statusMessage, &m_waitForMessage=m_waitForMessage](const cms::Message* message, const offcenter::common::framework::admin::AdminStatusMessage& statusMessage)
				{
					m_statusMessage = statusMessage;
					m_waitForMessage.messageReceived();
				});
	}

	virtual ~AdminStatusFixture() {
		LOG(DEBUG) << "Close Destination";
		m_statusConsumer.reset();
		m_statusProducer.reset();

		LOG(DEBUG) << "Close Connection";
		m_connection->close();
		m_connection.reset();

		LOG(DEBUG) << "Shutdown ActiveMQCPP";
		activemq::library::ActiveMQCPP::shutdownLibrary();
	}

protected:
	void SetUp() override {
		m_connection->start();
	}

	void TearDown() override {
		m_statusConsumer.reset();
		m_statusProducer.reset();
	}

protected:
	offcenter::common::framework::admin::AdminStatusProducer::Ptr m_statusProducer;
	offcenter::common::framework::admin::AdminStatusConsumer::Ptr m_statusConsumer;

	offcenter::common::framework::admin::AdminStatusMessage m_statusMessage;

	offcenter::amqp::ConnectionPtr m_connection;
	offcenter::amqp::SessionPtr m_providerSession;
	offcenter::amqp::DestinationPtr m_providerDestination;
	offcenter::amqp::SessionPtr m_consumerSession;
	offcenter::amqp::DestinationPtr m_consumerDestination;

	offcenter::common::WaitForMessage m_waitForMessage;

	// void TearDown() override {}

	//using App = framework::application::AppManager<BasicAppWithConfigTest>;
	//App m_basicAppTest;
};

TEST_F (AdminStatusFixture, SimpleMessages)
{
	EXPECT_EQ(m_statusMessage.appID(), "");
	EXPECT_EQ(m_statusMessage.state(), offcenter::common::framework::admin::AdminStatusState::Unknown);

	m_statusProducer->ready();
	m_waitForMessage.waitForMessage();
	EXPECT_EQ(m_statusMessage.appID(), "test_admin_status");
	EXPECT_EQ(m_statusMessage.state(), offcenter::common::framework::admin::AdminStatusState::Ready);

	m_statusProducer->starting();
	m_waitForMessage.waitForMessage();
	EXPECT_EQ(m_statusMessage.appID(), "test_admin_status");
	EXPECT_EQ(m_statusMessage.state(), offcenter::common::framework::admin::AdminStatusState::Starting);

	m_statusProducer->running();
	m_waitForMessage.waitForMessage();
	EXPECT_EQ(m_statusMessage.appID(), "test_admin_status");
	EXPECT_EQ(m_statusMessage.state(), offcenter::common::framework::admin::AdminStatusState::Running);

	m_statusProducer->stopping();
	m_waitForMessage.waitForMessage();
	EXPECT_EQ(m_statusMessage.appID(), "test_admin_status");
	EXPECT_EQ(m_statusMessage.state(), offcenter::common::framework::admin::AdminStatusState::Stopping);

	m_statusProducer->stopped();
	m_waitForMessage.waitForMessage();
	EXPECT_EQ(m_statusMessage.appID(), "test_admin_status");
	EXPECT_EQ(m_statusMessage.state(), offcenter::common::framework::admin::AdminStatusState::Stopped);

	m_statusProducer->pausing();
	m_waitForMessage.waitForMessage();
	EXPECT_EQ(m_statusMessage.appID(), "test_admin_status");
	EXPECT_EQ(m_statusMessage.state(), offcenter::common::framework::admin::AdminStatusState::Pausing);

	m_statusProducer->paused();
	m_waitForMessage.waitForMessage();
	EXPECT_EQ(m_statusMessage.appID(), "test_admin_status");
	EXPECT_EQ(m_statusMessage.state(), offcenter::common::framework::admin::AdminStatusState::Paused);

	m_statusProducer->resuming();
	m_waitForMessage.waitForMessage();
	EXPECT_EQ(m_statusMessage.appID(), "test_admin_status");
	EXPECT_EQ(m_statusMessage.state(), offcenter::common::framework::admin::AdminStatusState::Resuming);

	m_statusProducer->error();
	m_waitForMessage.waitForMessage();
	EXPECT_EQ(m_statusMessage.appID(), "test_admin_status");
	EXPECT_EQ(m_statusMessage.state(), offcenter::common::framework::admin::AdminStatusState::Error);

	m_statusProducer->unknown();
	m_waitForMessage.waitForMessage();
	EXPECT_EQ(m_statusMessage.appID(), "test_admin_status");
	EXPECT_EQ(m_statusMessage.state(), offcenter::common::framework::admin::AdminStatusState::Unknown);

}
