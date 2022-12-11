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
 * @file   MessageProducer.hpp
 * @author Scott Brauer
 * @date   05-05-2021
 */

#ifndef OFFCENTER_AMQP_MESSAGEPRODUCER_HPP_
#define OFFCENTER_AMQP_MESSAGEPRODUCER_HPP_

#include <memory>

#include "offcenter/common/amqp/Helper.hpp"

namespace offcenter {
namespace amqp {


//
template <typename TCMSMessageType>
class MessageProducerBase {
};

//
template <>
class MessageProducerBase<cms::Message> {
public:
	explicit MessageProducerBase(SessionPtr session):
		m_cmsMessage(session->createMessage()) {}
	virtual ~MessageProducerBase() = default;
protected:
	MessagePtr m_cmsMessage;
};

//
template <>
class MessageProducerBase<cms::BytesMessage> {
public:
	explicit MessageProducerBase(SessionPtr session):
		m_cmsMessage(session->createBytesMessage()) {}
	virtual ~MessageProducerBase() = default;
protected:
	BytesMessagePtr m_cmsMessage;
};

//
template <>
class MessageProducerBase<cms::StreamMessage> {
public:
	explicit MessageProducerBase(SessionPtr session):
		m_cmsMessage(session->createStreamMessage()) {}
	virtual ~MessageProducerBase() = default;
protected:
	StreamMessagePtr m_cmsMessage;
};

//
template <>
class MessageProducerBase<cms::TextMessage> {
public:
	explicit MessageProducerBase(SessionPtr session):
		m_cmsMessage(session->createTextMessage()) {}
	virtual ~MessageProducerBase() = default;
protected:
	TextMessagePtr m_cmsMessage;
};

//
template <>
class MessageProducerBase<cms::MapMessage> {
public:
	explicit MessageProducerBase(SessionPtr session):
		m_cmsMessage(session->createMapMessage()) {}
	virtual ~MessageProducerBase() = default;
protected:
	MapMessagePtr m_cmsMessage;
};

//
template <class TCMSMessageType, class TAMQPMessageType>
class MessageProducer : public MessageProducerBase<TCMSMessageType> {
public:
	explicit MessageProducer(SessionPtr session, MessageProducerPtr producer):
		MessageProducerBase<TCMSMessageType>(session),
		m_producer(producer)
	{}

	void send(const TAMQPMessageType& message) {
		to_cmsMessage(MessageProducerBase<TCMSMessageType>::m_cmsMessage.get(), message);
		m_producer->send(MessageProducerBase<TCMSMessageType>::m_cmsMessage.get());
	}

private:
	MessageProducerPtr m_producer;

};

} /* namespace amqp */
} /* namespace offcenter */

#endif /* OFFCENTER_AMQP_MESSAGEPRODUCER_HPP_ */
