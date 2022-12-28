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

#include "offcenter/common/amqp/ConnectionOptions.hpp"

namespace offcenter {
namespace common {
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
inline offcenter::common::amqp::MessageCPtr cmsCMessageFactory<offcenter::common::amqp::MessageCPtr>(const cms::Message* message) {
	return offcenter::common::amqp::MessageCPtr(message);
}

template <>
offcenter::common::amqp::MessageCUPtr cmsCMessageFactory<offcenter::common::amqp::MessageCUPtr>(const cms::Message* message) {
	return offcenter::common::amqp::MessageCUPtr(message);
}

template <>
offcenter::common::amqp::MessagePtr cmsMessageFactory<offcenter::common::amqp::MessagePtr>(cms::Message* message) {
	return offcenter::common::amqp::MessagePtr(message);
}

template <>
offcenter::common::amqp::MessageUPtr cmsMessageFactory<offcenter::common::amqp::MessageUPtr>(cms::Message* message) {
	return offcenter::common::amqp::MessageUPtr(message);
}

//*****************************************************************************
template <>
offcenter::common::amqp::BytesMessageCPtr cmsCMessageFactory<offcenter::common::amqp::BytesMessageCPtr>(const cms::Message* message) {
	return offcenter::common::amqp::BytesMessageCPtr(dynamic_cast<const cms::BytesMessage*>(message));
}

template <>
offcenter::common::amqp::BytesMessageCUPtr cmsCMessageFactory<offcenter::common::amqp::BytesMessageCUPtr>(const cms::Message* message) {
	return offcenter::common::amqp::BytesMessageCUPtr(dynamic_cast<const cms::BytesMessage*>(message));
}

template <>
offcenter::common::amqp::BytesMessagePtr cmsMessageFactory<offcenter::common::amqp::BytesMessagePtr>(cms::Message* message) {
	return offcenter::common::amqp::BytesMessagePtr(dynamic_cast<cms::BytesMessage*>(message));
}

template <>
offcenter::common::amqp::BytesMessageUPtr cmsMessageFactory<offcenter::common::amqp::BytesMessageUPtr>(cms::Message* message) {
	return offcenter::common::amqp::BytesMessageUPtr(dynamic_cast<cms::BytesMessage*>(message));
}

//*****************************************************************************
template <>
offcenter::common::amqp::StreamMessageCPtr cmsCMessageFactory<offcenter::common::amqp::StreamMessageCPtr>(const cms::Message* message) {
	return offcenter::common::amqp::StreamMessageCPtr(dynamic_cast<const cms::StreamMessage*>(message));
}

template <>
offcenter::common::amqp::StreamMessageCUPtr cmsCMessageFactory<offcenter::common::amqp::StreamMessageCUPtr>(const cms::Message* message) {
	return offcenter::common::amqp::StreamMessageCUPtr(dynamic_cast<const cms::StreamMessage*>(message));
}

template <>
offcenter::common::amqp::StreamMessagePtr cmsMessageFactory<offcenter::common::amqp::StreamMessagePtr>(cms::Message* message) {
	return offcenter::common::amqp::StreamMessagePtr(dynamic_cast<cms::StreamMessage*>(message));
}

template <>
offcenter::common::amqp::StreamMessageUPtr cmsMessageFactory<offcenter::common::amqp::StreamMessageUPtr>(cms::Message* message) {
	return offcenter::common::amqp::StreamMessageUPtr(dynamic_cast<cms::StreamMessage*>(message));
}

//*****************************************************************************
template <>
offcenter::common::amqp::TextMessageCPtr cmsCMessageFactory<offcenter::common::amqp::TextMessageCPtr>(const cms::Message* message) {
	return offcenter::common::amqp::TextMessageCPtr(dynamic_cast<const cms::TextMessage*>(message));
}

template <>
offcenter::common::amqp::TextMessageCUPtr cmsCMessageFactory<offcenter::common::amqp::TextMessageCUPtr>(const cms::Message* message) {
	return offcenter::common::amqp::TextMessageCUPtr(dynamic_cast<const cms::TextMessage*>(message));
}

template <>
offcenter::common::amqp::TextMessagePtr cmsMessageFactory<offcenter::common::amqp::TextMessagePtr>(cms::Message* message) {
	return offcenter::common::amqp::TextMessagePtr(dynamic_cast<cms::TextMessage*>(message));
}

template <>
offcenter::common::amqp::TextMessageUPtr cmsMessageFactory<offcenter::common::amqp::TextMessageUPtr>(cms::Message* message) {
	return offcenter::common::amqp::TextMessageUPtr(dynamic_cast<cms::TextMessage*>(message));
}

//*****************************************************************************
template <>
offcenter::common::amqp::MapMessageCPtr cmsCMessageFactory<offcenter::common::amqp::MapMessageCPtr>(const cms::Message* message) {
	return offcenter::common::amqp::MapMessageCPtr(dynamic_cast<const cms::MapMessage*>(message));
}

template <>
offcenter::common::amqp::MapMessageCUPtr cmsCMessageFactory<offcenter::common::amqp::MapMessageCUPtr>(const cms::Message* message) {
	return offcenter::common::amqp::MapMessageCUPtr(dynamic_cast<const cms::MapMessage*>(message));
}

template <>
offcenter::common::amqp::MapMessagePtr cmsMessageFactory<offcenter::common::amqp::MapMessagePtr>(cms::Message* message) {
	return offcenter::common::amqp::MapMessagePtr(dynamic_cast<cms::MapMessage*>(message));
}

template <>
offcenter::common::amqp::MapMessageUPtr cmsMessageFactory<offcenter::common::amqp::MapMessageUPtr>(cms::Message* message) {
	return offcenter::common::amqp::MapMessageUPtr(dynamic_cast<cms::MapMessage*>(message));
}
*/
} /* namespace Helper */
} /* namespace amqp */
} /* namespace common */
} /* namespace offcenter */

#endif /* OFFCENTER_AMQP_HELPER_HPP_ */
