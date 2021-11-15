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
 * @file   SessionProducer.hpp
 * @author Scott Brauer
 * @date   05-05-2021
 */

#ifndef OFFCENTER_AMQP_SESSIONPRODUCER_HPP_
#define OFFCENTER_AMQP_SESSIONPRODUCER_HPP_

#include <memory>

#include <cms/Session.h>

#include "MessageProducer.hpp"
#include "offcenter/amqp/Helper.hpp"
#include "offcenter/amqp/Session.hpp"

namespace offcenter {
namespace amqp {

/**
 *
 */
class SessionProducer : public Session
{
public:
	using Ptr = std::unique_ptr<SessionProducer>;

	static Ptr factory(ConnectionPtr connection, const ConnectionSettings& connectionSettings) {
		return std::make_unique<SessionProducer>(connection, connectionSettings);
	}

public:
	explicit SessionProducer(ConnectionPtr connection, const ConnectionSettings& connectionSettings);
	virtual ~SessionProducer();

	template <class TCMSMessageType, class TAMQPMessage>
	void send(const TAMQPMessage& message) {
		MessageProducer<TCMSMessageType, TAMQPMessage> messageHandler(sessionPtr(), producerPtr());
		messageHandler.send(message);
	}

	cms::Destination* destination() { return m_destination.get(); }
	cms::MessageProducer* producer() { return m_producer.get(); }
	MessageProducerPtr producerPtr() { return m_producer; }

private:
	DestinationUPtr m_destination;
	MessageProducerPtr m_producer;

};

} /* namespace amqp */
} /* namespace offcenter */

#endif /* OFFCENTER_AMQP_SESSIONPRODUCER_HPP_ */
