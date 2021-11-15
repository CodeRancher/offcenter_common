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
 * @file   ProducerConsumerBase.hpp
 * @author Scott Brauer
 * @date   12-03-2018
 */

/*
 * AMQPTopicProducerFixture.hpp
 *
 *  Created on: Nov 26, 2018
 *      Author: sbrauer
 */

#ifndef LIB_AMQP_TEST_AMQPTOPICPRODUCERFIXTURE_HPP_
#define LIB_AMQP_TEST_AMQPTOPICPRODUCERFIXTURE_HPP_

#include <memory>

#include <gtest/gtest.h>

#include "offcenter/common/ScopeGuard.hpp"
#include "offcenter/amqp/Helper.hpp"

class TopicProducerFixture : public ::testing::Test {
public:
	TopicProducerFixture();
	virtual ~TopicProducerFixture();

protected:
	void SetUp() override;
	void TearDown() override;
	static void SetUpTestCase();
	static void TearDownTestCase();

public:
	offcenter::amqp::ConnectionPtr connection;
	offcenter::amqp::SessionPtr session;
	offcenter::amqp::DestinationPtr destination;
	offcenter::amqp::MessageProducerPtr producer;
	offcenter::amqp::MessageConsumerPtr consumer;

};

#endif /* LIB_AMQP_TEST_AMQPTOPICPRODUCERFIXTURE_HPP_ */
