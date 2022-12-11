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
 * @file   ConsumerMessageHandler.hpp
 * @author Scott Brauer
 * @date   04-20-2021
 */

#ifndef OFFCENTER_AMQP_CONSUMERMESSAGEHANDLER_HPP_
#define OFFCENTER_AMQP_CONSUMERMESSAGEHANDLER_HPP_

#include <cms/MessageConsumer.h>

#include "offcenter/common/amqp/Helper.hpp"
#include "offcenter/common/amqp/AMQPException.hpp"

namespace offcenter {
namespace amqp {

/**
 *
 */
class ConsumerMessageHandler
{
private:
	//
	template <class MESSAGE, class MESSAGETYPE>
	struct MessageHandler {

	};

	//
	template <class MESSAGE>
	class MessageHandler<MESSAGE, cms::Message> {
	public:
		explicit MessageHandler(SessionPtr session, MessageProducerPtr producer):
			m_cmsMessage(session->createMessage()),
			m_producer(producer) {}
		void send(const MESSAGE& message) {
			to_cmsMessage(*m_cmsMessage.get(), message);
			m_producer->send(m_cmsMessage.get());
		}
	private:
		std::unique_ptr<cms::Message> m_cmsMessage;
		MessageProducerPtr m_producer;
	};

	//
	template <class MESSAGE>
	struct MessageHandler<MESSAGE, cms::BytesMessage> {
	public:
		explicit MessageHandler(SessionPtr session, MessageProducerPtr producer):
			m_cmsMessage(session->createBytesMessage()),
			m_producer(producer) {}
		void send(const MESSAGE& message) {
			to_cmsMessage(*m_cmsMessage.get(), message);
			m_producer->send(m_cmsMessage.get());
		}
	private:
		std::unique_ptr<cms::BytesMessage> m_cmsMessage;
		MessageProducerPtr m_producer;
	};

	//
	template <class MESSAGE>
	struct MessageHandler<MESSAGE, cms::StreamMessage> {
	public:
		explicit MessageHandler(SessionPtr session, MessageProducerPtr producer):
			m_cmsMessage(session->createStreamMessage()),
			m_producer(producer) {}
		void send(const MESSAGE& message) {
			to_cmsMessage(*m_cmsMessage.get(), message);
			m_producer->send(m_cmsMessage.get());
		}
	private:
		std::unique_ptr<cms::StreamMessage> m_cmsMessage;
		MessageProducerPtr m_producer;
	};

	//
	template <class MESSAGE>
	struct MessageHandler<MESSAGE, cms::TextMessage> {
	public:
		explicit MessageHandler(SessionPtr session, MessageProducerPtr producer):
			m_cmsMessage(session->createTextMessage()),
			m_producer(producer) {}
		void send(const MESSAGE& message) {
			to_cmsMessage(*m_cmsMessage.get(), message);
			m_producer->send(m_cmsMessage.get());
		}
	private:
		std::unique_ptr<cms::TextMessage> m_cmsMessage;
		MessageProducerPtr m_producer;
	};

	//
	template <class MESSAGE>
	struct MessageHandler<MESSAGE, cms::MapMessage> {
	public:
		explicit MessageHandler(SessionPtr session, MessageProducerPtr producer):
			m_cmsMessage(session->createMapMessage()),
			m_producer(producer) {}
		void send(const MESSAGE& message) {
			to_cmsMessage(*m_cmsMessage.get(), message);
			m_producer->send(m_cmsMessage.get());
		}
	private:
		std::unique_ptr<cms::MapMessage> m_cmsMessage;
		MessageProducerPtr m_producer;
	};

public:
	explicit ConsumerMessageHandler():
	m_consumer()
	{}
	explicit ConsumerMessageHandler(SessionPtr session, DestinationPtr destination):
			m_session(session),
			m_destination(destination),
			m_consumer(helper::messageProducerFactory(m_session->createProducer(m_destination.get())))
	{}

	virtual ~ConsumerMessageHandler() {
		m_consumer->close();
		m_consumer.reset();
	}

	/**
	 *
	 */
	void setProducer(offcenter::amqp::SessionPtr session, DestinationPtr destination) {
		m_session = session;
		m_destination = destination;
		m_consumer = helper::messageProducerFactory(m_session->createProducer(m_destination.get()));
	}

	template <class MESSAGE>
	void send(const MESSAGE& message) {
		MessageHandler<MESSAGE, typename MESSAGE::MessageType> messageHandler(m_session, m_producer);
		messageHandler.send(message);
	}

	offcenter::amqp::MessageConsumerPtr operator()() { return m_consumer; }

private:
	SessionPtr m_session;
	DestinationPtr m_destination;
	MessageConsumerPtr m_consumer;
};

} /* namespace amqp */
} /* namespace offcenter */

#endif /* OFFCENTER_AMQP_CONSUMERMESSAGEHANDLER_HPP_ */
