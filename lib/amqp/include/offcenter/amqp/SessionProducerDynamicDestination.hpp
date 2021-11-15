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
 * @file   SessionProducerDynamicDestination.hpp
 * @author Scott Brauer
 * @date   05-05-2021
 */

#ifndef OFFCENTER_AMQP_SESSIONPRODUCERDYNAMICDESTINATION_HPP_
#define OFFCENTER_AMQP_SESSIONPRODUCERDYNAMICDESTINATION_HPP_

#include <cms/Session.h>

#include "MessageProducer.hpp"
#include "offcenter/amqp/Helper.hpp"
#include "offcenter/amqp/Session.hpp"

namespace offcenter {
namespace amqp {

/**
 *
 */
class SessionProducerDynamicDestination : public Session
{
public:
	using Ptr = std::unique_ptr<SessionProducerDynamicDestination>;

	static Ptr factory(ConnectionPtr connection, const ConnectionSettings& connectionSettings) {
		return std::make_unique<SessionProducerDynamicDestination>(connection, connectionSettings);
	}

public:
	explicit SessionProducerDynamicDestination(ConnectionPtr connection, const ConnectionSettings& connectionSettings);
	virtual ~SessionProducerDynamicDestination();

	template <class TCMSMessageType, class TAMQPMessage>
	void send(const TAMQPMessage& message, const std::string qName) {
		// Create the destination (Topic or Queue)
		LOG(DEBUG) << "Open Destination";
		DestinationPtr destination = createDestination(qName);
		MessageProducerPtr producer = helper::messageProducerFactory(session()->createProducer(destination.get()));

		MessageProducer<TCMSMessageType, TAMQPMessage> messageHandler(sessionPtr(), producer);
		messageHandler.send(message);
	}

};

} /* namespace amqp */
} /* namespace offcenter */

#endif /* OFFCENTER_AMQP_SESSIONPRODUCERDYNAMICDESTINATION_HPP_ */
