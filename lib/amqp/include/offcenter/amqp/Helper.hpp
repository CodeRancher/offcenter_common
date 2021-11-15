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
 * @file   Helper.hpp
 * @author Scott Brauer
 * @date   11-28-2018
 */

#ifndef OFFCENTER_AMQP_HELPER_HPP_
#define OFFCENTER_AMQP_HELPER_HPP_

#include <memory>
#include <functional>

#include <decaf/lang/Thread.h>
#include <decaf/lang/Runnable.h>
//#include <decaf/util/concurrent/CountDownLatch.h>
#include <activemq/core/ActiveMQConnectionFactory.h>
#include <activemq/core/ActiveMQConnection.h>
#include <activemq/transport/DefaultTransportListener.h>
#include <activemq/library/ActiveMQCPP.h>
#include <decaf/lang/Integer.h>
#include <activemq/util/Config.h>
#include <decaf/util/Date.h>
#include <cms/ConnectionFactory.h>
#include <cms/Connection.h>
#include <cms/Session.h>
#include <cms/Destination.h>
#include <cms/MessageProducer.h>
#include <cms/MessageConsumer.h>
#include <cms/ExceptionListener.h>
#include <cms/MessageListener.h>

#include "offcenter/amqp/ConnectionOptions.hpp"

namespace offcenter {
namespace amqp {

using ActiveMQConnectionFactoryPtr = std::shared_ptr<activemq::core::ActiveMQConnectionFactory>;
using ConnectionPtr = std::shared_ptr<cms::Connection>;
using ConnectionUPtr = std::unique_ptr<cms::Connection, std::function<void(cms::Connection*)>>;
using SessionPtr = std::shared_ptr<cms::Session>;
using SessionUPtr = std::unique_ptr<cms::Session, std::function<void(cms::Session*)>>;
using DestinationPtr = std::shared_ptr<cms::Destination>;
using DestinationUPtr = std::unique_ptr<cms::Destination>;
using MessageProducerPtr = std::shared_ptr<cms::MessageProducer>;
using MessageProducerUPtr = std::unique_ptr<cms::MessageProducer, std::function<void(cms::MessageProducer*)>>;
using MessageConsumerPtr = std::shared_ptr<cms::MessageConsumer>;
using MessageConsumerUPtr = std::unique_ptr<cms::MessageConsumer, std::function<void(cms::MessageConsumer*)>>;
//using TextMessagePtr = std::shared_ptr<cms::TextMessage>;
//using TextMessageUPtr = std::unique_ptr<cms::TextMessage>;

//*****************************************************************************
//* CMS Message Types
//using MessageCPtr = std::shared_ptr<const cms::Message>;
using MessageCUPtr = std::unique_ptr<const cms::Message>;
using MessagePtr = std::shared_ptr<cms::Message>;
using MessageUPtr = std::unique_ptr<cms::Message>;
//
//using BytesMessageCPtr = std::shared_ptr<const cms::BytesMessage>;
//using BytesMessageCUPtr = std::unique_ptr<const cms::BytesMessage>;
using BytesMessagePtr = std::shared_ptr<cms::BytesMessage>;
//using BytesMessageUPtr = std::unique_ptr<cms::BytesMessage>;
//
//using StreamMessageCPtr = std::shared_ptr<const cms::StreamMessage>;
//using StreamMessageCUPtr = std::unique_ptr<const cms::StreamMessage>;
using StreamMessagePtr = std::shared_ptr<cms::StreamMessage>;
//using StreamMessageUPtr = std::unique_ptr<cms::StreamMessage>;
//
//using TextMessageCPtr = std::shared_ptr<const cms::TextMessage>;
//using TextMessageCUPtr = std::unique_ptr<const cms::TextMessage>;
using TextMessagePtr = std::shared_ptr<cms::TextMessage>;
using TextMessageUPtr = std::unique_ptr<cms::TextMessage>;
//
//using MapMessageCPtr = std::shared_ptr<const cms::MapMessage>;
//using MapMessageCUPtr = std::unique_ptr<const cms::MapMessage>;
using MapMessagePtr = std::shared_ptr<cms::MapMessage>;
//using MapMessageUPtr = std::unique_ptr<cms::MapMessage>;

//class ActiveMQCPP {
//	explicit ActiveMQCPP();
//	virtual ~ActiveMQCPP();
//};

namespace helper {

ActiveMQConnectionFactoryPtr activeMQConnectionFactoryFactory(const std::string &brokerURI, const std::string &username="", const std::string &password="");
ActiveMQConnectionFactoryPtr activeMQConnectionFactoryFactory(const ConnectionURIOptions &brokerConnectionOptions, const std::string &username="", const std::string &password="");
ConnectionPtr connectionFactory(cms::Connection* connection);
SessionPtr sessionFactory(cms::Session* session);
SessionUPtr sessionUFactory(cms::Session* session);
DestinationPtr destinationFactory(cms::Destination* destination);
DestinationUPtr destinationUFactory(cms::Destination* destination);
MessageProducerPtr messageProducerFactory(cms::MessageProducer* messageProducer);
MessageProducerUPtr messageProducerUFactory(cms::MessageProducer* messageProducer);
MessageConsumerPtr messageConsumerFactory(cms::MessageConsumer* messageConsumer);
MessageConsumerUPtr messageConsumerUFactory(cms::MessageConsumer* messageConsumer);

/*
template <typename MESSAGEPTR>
inline MESSAGEPTR cmsCMessageFactory(const cms::Message* message) { return MESSAGEPTR(message); }

template <typename MESSAGEPTR>
MESSAGEPTR cmsMessageFactory(cms::Message* message) { return MESSAGEPTR(message); }

//*****************************************************************************
template <>
inline offcenter::amqp::MessageCPtr cmsCMessageFactory<offcenter::amqp::MessageCPtr>(const cms::Message* message) {
	return offcenter::amqp::MessageCPtr(message);
}

template <>
offcenter::amqp::MessageCUPtr cmsCMessageFactory<offcenter::amqp::MessageCUPtr>(const cms::Message* message) {
	return offcenter::amqp::MessageCUPtr(message);
}

template <>
offcenter::amqp::MessagePtr cmsMessageFactory<offcenter::amqp::MessagePtr>(cms::Message* message) {
	return offcenter::amqp::MessagePtr(message);
}

template <>
offcenter::amqp::MessageUPtr cmsMessageFactory<offcenter::amqp::MessageUPtr>(cms::Message* message) {
	return offcenter::amqp::MessageUPtr(message);
}

//*****************************************************************************
template <>
offcenter::amqp::BytesMessageCPtr cmsCMessageFactory<offcenter::amqp::BytesMessageCPtr>(const cms::Message* message) {
	return offcenter::amqp::BytesMessageCPtr(dynamic_cast<const cms::BytesMessage*>(message));
}

template <>
offcenter::amqp::BytesMessageCUPtr cmsCMessageFactory<offcenter::amqp::BytesMessageCUPtr>(const cms::Message* message) {
	return offcenter::amqp::BytesMessageCUPtr(dynamic_cast<const cms::BytesMessage*>(message));
}

template <>
offcenter::amqp::BytesMessagePtr cmsMessageFactory<offcenter::amqp::BytesMessagePtr>(cms::Message* message) {
	return offcenter::amqp::BytesMessagePtr(dynamic_cast<cms::BytesMessage*>(message));
}

template <>
offcenter::amqp::BytesMessageUPtr cmsMessageFactory<offcenter::amqp::BytesMessageUPtr>(cms::Message* message) {
	return offcenter::amqp::BytesMessageUPtr(dynamic_cast<cms::BytesMessage*>(message));
}

//*****************************************************************************
template <>
offcenter::amqp::StreamMessageCPtr cmsCMessageFactory<offcenter::amqp::StreamMessageCPtr>(const cms::Message* message) {
	return offcenter::amqp::StreamMessageCPtr(dynamic_cast<const cms::StreamMessage*>(message));
}

template <>
offcenter::amqp::StreamMessageCUPtr cmsCMessageFactory<offcenter::amqp::StreamMessageCUPtr>(const cms::Message* message) {
	return offcenter::amqp::StreamMessageCUPtr(dynamic_cast<const cms::StreamMessage*>(message));
}

template <>
offcenter::amqp::StreamMessagePtr cmsMessageFactory<offcenter::amqp::StreamMessagePtr>(cms::Message* message) {
	return offcenter::amqp::StreamMessagePtr(dynamic_cast<cms::StreamMessage*>(message));
}

template <>
offcenter::amqp::StreamMessageUPtr cmsMessageFactory<offcenter::amqp::StreamMessageUPtr>(cms::Message* message) {
	return offcenter::amqp::StreamMessageUPtr(dynamic_cast<cms::StreamMessage*>(message));
}

//*****************************************************************************
template <>
offcenter::amqp::TextMessageCPtr cmsCMessageFactory<offcenter::amqp::TextMessageCPtr>(const cms::Message* message) {
	return offcenter::amqp::TextMessageCPtr(dynamic_cast<const cms::TextMessage*>(message));
}

template <>
offcenter::amqp::TextMessageCUPtr cmsCMessageFactory<offcenter::amqp::TextMessageCUPtr>(const cms::Message* message) {
	return offcenter::amqp::TextMessageCUPtr(dynamic_cast<const cms::TextMessage*>(message));
}

template <>
offcenter::amqp::TextMessagePtr cmsMessageFactory<offcenter::amqp::TextMessagePtr>(cms::Message* message) {
	return offcenter::amqp::TextMessagePtr(dynamic_cast<cms::TextMessage*>(message));
}

template <>
offcenter::amqp::TextMessageUPtr cmsMessageFactory<offcenter::amqp::TextMessageUPtr>(cms::Message* message) {
	return offcenter::amqp::TextMessageUPtr(dynamic_cast<cms::TextMessage*>(message));
}

//*****************************************************************************
template <>
offcenter::amqp::MapMessageCPtr cmsCMessageFactory<offcenter::amqp::MapMessageCPtr>(const cms::Message* message) {
	return offcenter::amqp::MapMessageCPtr(dynamic_cast<const cms::MapMessage*>(message));
}

template <>
offcenter::amqp::MapMessageCUPtr cmsCMessageFactory<offcenter::amqp::MapMessageCUPtr>(const cms::Message* message) {
	return offcenter::amqp::MapMessageCUPtr(dynamic_cast<const cms::MapMessage*>(message));
}

template <>
offcenter::amqp::MapMessagePtr cmsMessageFactory<offcenter::amqp::MapMessagePtr>(cms::Message* message) {
	return offcenter::amqp::MapMessagePtr(dynamic_cast<cms::MapMessage*>(message));
}

template <>
offcenter::amqp::MapMessageUPtr cmsMessageFactory<offcenter::amqp::MapMessageUPtr>(cms::Message* message) {
	return offcenter::amqp::MapMessageUPtr(dynamic_cast<cms::MapMessage*>(message));
}
*/
} /* namespace Helper */
} /* namespace amqp */
} /* namespace offcenter */

#endif /* OFFCENTER_AMQP_HELPER_HPP_ */
