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
 * @file   ProducerMessageHandler.hpp
 * @author Scott Brauer
 * @date   04-20-2021
 */
#ifndef OFFCENTER_AMQP_PRODUCERMESSAGEHANDLER_HPP_
#define OFFCENTER_AMQP_PRODUCERMESSAGEHANDLER_HPP_

#include <cms/MessageProducer.h>

#include "easylogging++.h"

#include "MessageProducer.hpp"
#include "offcenter/amqp/Helper.hpp"
#include "offcenter/amqp/AMQPException.hpp"

namespace offcenter {
namespace amqp {

/**
 *
 */
class ProducerMessageHandler
{
public:
	explicit ProducerMessageHandler():
			m_producer()
	{
		LOG(DEBUG) << "Open empty producer";
	}

	explicit ProducerMessageHandler(SessionPtr session, DestinationPtr destination):
			m_session(session),
			m_destination(destination),
			m_producer(helper::messageProducerFactory(m_session->createProducer(m_destination.get())))
	{
		LOG(DEBUG) << "Open producer";
	}

	virtual ~ProducerMessageHandler() {
		LOG(DEBUG) << "Close producer";
		m_producer->close();
		m_producer.reset();
	}

	/**
	 *
	 */
	void setProducer(offcenter::amqp::SessionPtr session, DestinationPtr destination) {
		m_session = session;
		m_destination = destination;
		m_producer = helper::messageProducerFactory(m_session->createProducer(m_destination.get()));
	}

	template <class TAMQPMessage>
	void send(const TAMQPMessage& message) {
		MessageProducer<typename TAMQPMessage::MessageType, TAMQPMessage> messageHandler(m_session, m_producer);
		messageHandler.send(message);
	}

	offcenter::amqp::MessageProducerPtr operator()() { return m_producer; }

private:
	SessionPtr m_session;
	DestinationPtr m_destination;
	MessageProducerPtr m_producer;
};

} /* namespace amqp */
} /* namespace offcenter */

#endif /* OFFCENTER_AMQP_PRODUCERMESSAGEHANDLER_HPP_ */
