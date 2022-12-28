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
 * @file   TopicMessageFixture.hpp
 * @author Scott Brauer
 * @date   03-03-2018
 */

#ifndef LIB_AMQP_TEST_AMQPTOPICMESSAGEFIXTURE_HPP_
#define LIB_AMQP_TEST_AMQPTOPICMESSAGEFIXTURE_HPP_

#include <gtest/gtest.h>

#include "offcenter/common/ScopeGuard.hpp"
//#include "amqp/AMQPHelper.hpp"
#include "offcenter/common/amqp/Message.hpp"
#include "offcenter/common/amqp/Producer.hpp"
#include "offcenter/common/amqp/Consumer.hpp"
#include "offcenter/common/amqp/ConnectionOptions.hpp"
using namespace offcenter;

template <class element>
class TopicMessageFixture : public ::testing::Test {
public:
	using Producer = offcenter::common::amqp::Producer<element>;
	using Consumer = offcenter::common::amqp::Consumer<element>;
	typename Producer::Ptr producer;
	typename Consumer::ConsumerPtr consumer;

public:
	TopicMessageFixture() = default;
	virtual ~TopicMessageFixture() = default;

protected:
	void SetUp() override{
		amqp::ConnectionURIOptions options;
		amqp::URLSchemeHost tcpHost(amqp::URLSchemeHost::URLScheme::tcp, "rpiactivemq");
		options.protocol.setTCPProtocol(tcpHost);
		options.connection.sendTimeout = 100;
		options.failoverTransport.timeout = 100;

		// Create a ConnectionFactory
		amqp::ActiveMQConnectionFactoryPtr connectionFactory(amqp::helper::activeMQConnectionFactoryFactory(options.uri()));

		producer = Producer::factory(connectionFactory, [](amqp::MessageProducerPtr producer){});
		consumer = Consumer::consumerFactory(connectionFactory, [](amqp::MessageConsumerPtr consumer){});
	}

	void TearDown() override {}

	static void SetUpTestCase(){
		activemq::library::ActiveMQCPP::initializeLibrary();
	}

	static void TearDownTestCase(){
		activemq::library::ActiveMQCPP::shutdownLibrary();
	}

};



#endif /* LIB_AMQP_TEST_AMQPTOPICMESSAGEFIXTURE_HPP_ */
