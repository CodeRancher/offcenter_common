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
 * @file   test_admin_control.cpp
 * @author Scott Brauer
 * @date   04-27-2019
 */

#include <gtest/gtest.h>

#include "easylogging++.h"

#include "offcenter/common/framework/admin/AdminControlProducer.hpp"
#include "offcenter/common/framework/admin/AdminControlConsumer.hpp"
#include "offcenter/common/framework/admin/AdminControlMessage.hpp"
#include "offcenter/common/WaitForMessage.hpp"

//*****************************************************************************
class AdminControlFixture : public ::testing::Test {
public:
	explicit AdminControlFixture() {
		activemq::library::ActiveMQCPP::initializeLibrary();

		offcenter::amqp::ConnectionURIOptions options;
		offcenter::amqp::URLSchemeHost tcpHost(offcenter::amqp::URLSchemeHost::URLScheme::tcp, "rpiactivemq");
		options.protocol.setTCPProtocol(tcpHost);
		options.connection.sendTimeout = 1000;
		options.failoverTransport.timeout = 1000;

		// Connect to the AMQP server
		LOG(DEBUG) << "Open AdminControlFixture Connection Factory";
		offcenter::amqp::ActiveMQConnectionFactoryPtr connectionFactory(offcenter::amqp::helper::activeMQConnectionFactoryFactory(options.uri()));

	    // Create a Connection
		LOG(DEBUG) << "Open AdminControlFixture Connection";
		m_connection = offcenter::amqp::helper::connectionFactory(connectionFactory->createConnection());

		offcenter::amqp::ConnectionSettings connectionSettings(
				cms::Session::AcknowledgeMode::AUTO_ACKNOWLEDGE,
				offcenter::amqp::ConnectionSettings::QueueType::Topic,
				"offcenter.test.AdminControl.");

		m_controlProducer = offcenter::common::framework::admin::AdminControlProducer::factory(
				std::move(offcenter::amqp::SessionProducerDynamicDestination::factory(m_connection, connectionSettings)),
				"test_admin_control");

		offcenter::amqp::ConnectionSettings generalConnectionSettings(
				cms::Session::AcknowledgeMode::AUTO_ACKNOWLEDGE,
				offcenter::amqp::ConnectionSettings::QueueType::Topic,
				"offcenter.test.AdminControl.#all#");

		offcenter::amqp::ConnectionSettings specificConnectionSettings(
				cms::Session::AcknowledgeMode::AUTO_ACKNOWLEDGE,
				offcenter::amqp::ConnectionSettings::QueueType::Topic,
				"offcenter.test.AdminControl.app_id");

		m_controlConsumer = offcenter::common::framework::admin::AdminControlConsumer::factory(
				std::move(offcenter::amqp::SessionConsumer::factory(m_connection, generalConnectionSettings)),
				std::move(offcenter::amqp::SessionConsumer::factory(m_connection, specificConnectionSettings)),
				[this](const cms::Message* message, const offcenter::common::framework::admin::AdminControlMessage& controlMessage)
				{
					m_controlMessage = controlMessage;
					m_waitForMessage.messageReceived();
				});
	}

	virtual ~AdminControlFixture() {
		LOG(DEBUG) << "Close AdminControlFixture Destination";
		m_controlConsumer.reset();
		m_controlProducer.reset();

		LOG(DEBUG) << "Close AdminControlFixture Connection";
		m_connection->close();
		m_connection.reset();

		LOG(DEBUG) << "Shutdown AdminControlFixture ActiveMQCPP";
		activemq::library::ActiveMQCPP::shutdownLibrary();
	}

protected:
	void SetUp() override {
		m_connection->start();
	}

	void TearDown() override {
	}

protected:
	offcenter::common::framework::admin::AdminControlProducer::Ptr m_controlProducer;
	offcenter::common::framework::admin::AdminControlConsumer::Ptr m_controlConsumer;

	offcenter::common::framework::admin::AdminControlMessage m_controlMessage;

	offcenter::amqp::ConnectionPtr m_connection;

	offcenter::common::WaitForMessage m_waitForMessage;

};

TEST_F (AdminControlFixture, SimpleMessages)
{
	EXPECT_EQ(m_controlMessage.appID(), "");
	EXPECT_EQ(m_controlMessage.state(), offcenter::common::framework::admin::AdminControlState::Unknown);

	m_controlProducer->start();
	m_waitForMessage.waitForMessage();
	EXPECT_EQ(m_controlMessage.appID(), "#all#");
	EXPECT_EQ(m_controlMessage.state(), offcenter::common::framework::admin::AdminControlState::Start);

	m_controlProducer->start("app_id");
	m_waitForMessage.waitForMessage();
	EXPECT_EQ(m_controlMessage.appID(), "app_id");
	EXPECT_EQ(m_controlMessage.state(), offcenter::common::framework::admin::AdminControlState::Start);

	m_controlProducer->stop();
	m_waitForMessage.waitForMessage();
	EXPECT_EQ(m_controlMessage.appID(), "#all#");
	EXPECT_EQ(m_controlMessage.state(), offcenter::common::framework::admin::AdminControlState::Stop);

	m_controlProducer->stop("app_id");
	m_waitForMessage.waitForMessage();
	EXPECT_EQ(m_controlMessage.appID(), "app_id");
	EXPECT_EQ(m_controlMessage.state(), offcenter::common::framework::admin::AdminControlState::Stop);

	m_controlProducer->pause();
	m_waitForMessage.waitForMessage();
	EXPECT_EQ(m_controlMessage.appID(), "#all#");
	EXPECT_EQ(m_controlMessage.state(), offcenter::common::framework::admin::AdminControlState::Pause);

	m_controlProducer->pause("app_id");
	m_waitForMessage.waitForMessage();
	EXPECT_EQ(m_controlMessage.appID(), "app_id");
	EXPECT_EQ(m_controlMessage.state(), offcenter::common::framework::admin::AdminControlState::Pause);

	m_controlProducer->resume();
	m_waitForMessage.waitForMessage();
	EXPECT_EQ(m_controlMessage.appID(), "#all#");
	EXPECT_EQ(m_controlMessage.state(), offcenter::common::framework::admin::AdminControlState::Resume);

	m_controlProducer->resume("app_id");
	m_waitForMessage.waitForMessage();
	EXPECT_EQ(m_controlMessage.appID(), "app_id");
	EXPECT_EQ(m_controlMessage.state(), offcenter::common::framework::admin::AdminControlState::Resume);
}
