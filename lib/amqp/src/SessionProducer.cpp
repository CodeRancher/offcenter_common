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
 * @file   SessionProducer.cpp
 * @author Scott Brauer
 * @date   05-05-2021
 */

#include "easylogging++.h"

#include "offcenter/common/amqp/Helper.hpp"
#include "offcenter/common/amqp/AMQPException.hpp"
#include "offcenter/common/amqp/SessionProducer.hpp"

namespace offcenter {
namespace common {
namespace amqp {

SessionProducer::SessionProducer(ConnectionPtr connection, const ConnectionSettings& connectionSettings):
		Session(connection, connectionSettings)
{
	// Create the destination (Topic or Queue)
	LOG(DEBUG) << "Open Destination";
	m_destination = std::move(createDestination());

	// Create the destination (Topic or Queue)
	LOG(DEBUG) << "Open Producer";
	m_producer = helper::messageProducerFactory(session()->createProducer(m_destination.get()));
}

SessionProducer::~SessionProducer()
{
}

} /* namespace amqp */
} /* namespace common */
} /* namespace offcenter */
