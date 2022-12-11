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
 * @file   SessionConsumer.hpp
 * @author Scott Brauer
 * @date   05-06-2021
 */
#ifndef OFFCENTER_AMQP_SESSIONCONSUMER_HPP_
#define OFFCENTER_AMQP_SESSIONCONSUMER_HPP_

#include <memory>

#include <cms/Session.h>

#include "MessageProducer.hpp"
#include "offcenter/common/amqp/Helper.hpp"
#include "offcenter/common/amqp/Session.hpp"

namespace offcenter {
namespace amqp {

/**
 *
 */
class SessionConsumer : public Session
{
public:
	using Ptr = std::unique_ptr<SessionConsumer>;

	static Ptr factory(ConnectionPtr connection, const ConnectionSettings& connectionSettings) {
		return std::make_unique<SessionConsumer>(connection, connectionSettings);
	}

public:
	explicit SessionConsumer(ConnectionPtr connection, const ConnectionSettings& connectionSettings);
	virtual ~SessionConsumer();

	cms::Destination* destination() { return m_destination.get(); }
	cms::MessageConsumer* consumer() { return m_consumer.get(); }

private:
	DestinationUPtr m_destination;
	MessageConsumerUPtr m_consumer;

};

} /* namespace amqp */
} /* namespace offcenter */

#endif /* OFFCENTER_AMQP_SESSIONCONSUMER_HPP_ */
