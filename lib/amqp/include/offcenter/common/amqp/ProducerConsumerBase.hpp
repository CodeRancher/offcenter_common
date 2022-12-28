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

#ifndef LIB_OFFCENTER_AMQP_SRC_PRODUCERCONSUMERBASE_HPP_
#define LIB_OFFCENTER_AMQP_SRC_PRODUCERCONSUMERBASE_HPP_

#include "offcenter/common/amqp/Helper.hpp"

namespace offcenter {
namespace common {
namespace amqp {

template <class messageType>
class ProducerConsumerBase {
protected:
	offcenter::common::amqp::ConnectionPtr m_connection;
	offcenter::common::amqp::SessionPtr m_session;
	offcenter::common::amqp::DestinationPtr m_destination;

public:
	ProducerConsumerBase(offcenter::common::amqp::ActiveMQConnectionFactoryPtr connectionFactory) {
	    // Create a Connection
		//BOOST_LOG_TRIVIAL(trace) << "Create connection";
	    m_connection = offcenter::common::amqp::helper::connectionFactory(connectionFactory->createConnection());
	    //BOOST_LOG_TRIVIAL(trace) << "Start connection";
	    m_connection->start();

	    // Create a Session
	    //BOOST_LOG_TRIVIAL(trace) << "Create session";
	    m_session = offcenter::common::amqp::helper::sessionFactory(m_connection->createSession(cms::Session::AUTO_ACKNOWLEDGE));

	    // Create the destination (Topic or Queue)
	    //BOOST_LOG_TRIVIAL(trace) << "Create session topic";
	    m_destination = offcenter::common::amqp::helper::destinationFactory(m_session->createTopic("TEST.FOO"));
	}

	virtual ~ProducerConsumerBase() {
	    //BOOST_LOG_TRIVIAL(trace) << "~ProducerConsumerBase";

	    if (m_destination) { m_destination.reset(); }
	    if (m_session) { m_session.reset(); }
	    if (m_connection) { m_connection.reset(); }
	}

	offcenter::common::amqp::MessageProducerPtr getMessageProducer() const {
		//BOOST_LOG_TRIVIAL(trace) << "Create producer";
		return offcenter::common::amqp::helper::messageProducerFactory(
				m_session->createProducer(m_destination.get()));
	}

	offcenter::common::amqp::MessageConsumerPtr getMessageConsumer() const {
		//BOOST_LOG_TRIVIAL(trace) << "Create consumer";
		return offcenter::common::amqp::helper::messageConsumerFactory(
				m_session->createConsumer(m_destination.get()));
	}

};

} /* namespace amqp */
} /* namespace common */
} /* namespace offcenter */

#endif /* LIB_OFFCENTER_AMQP_SRC_PRODUCERCONSUMERBASE_HPP_ */
