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
 * @file   Producer.hpp
 * @author Scott Brauer
 * @date   11-23-2018
 */

#ifndef LIB_OFFCENTER_AMQP_SRC_PRODUCER_H_
#define LIB_OFFCENTER_AMQP_SRC_PRODUCER_H_

#include <type_traits>
#include <thread>

#include "easylogging++.h"

#include <offcenter/amqp/Helper.hpp>
#include "offcenter/amqp/SessionProducer.hpp"
#include "offcenter/amqp/Message.hpp"

namespace offcenter {
namespace amqp {

template <typename TCMSMessageType, typename TAMQPMessageType>
class Producer
{
public:
	using Ptr = std::unique_ptr<Producer>;

	static Ptr factory(offcenter::amqp::SessionProducer::Ptr&& sessionProducer, const std::string& appID) {
		return std::make_unique<Producer>(std::forward<offcenter::amqp::SessionProducer::Ptr>(sessionProducer), appID);
	}

public:
	explicit Producer(offcenter::amqp::SessionProducer::Ptr&& sessionProducer, const std::string& appID):
			m_sessionProducer(std::move(sessionProducer)),
			m_appID(appID)
	{}

	virtual ~Producer() = default;

protected:
	void sendMessage(const TAMQPMessageType& message) {
		const std::lock_guard<std::mutex> lock(m_sendMutex);
		LOG(DEBUG) << "sendMessage Begin";
		m_sessionProducer->send<TCMSMessageType>(message);
		LOG(DEBUG) << "sendMessage After";
	}

private:
	offcenter::amqp::SessionProducer::Ptr m_sessionProducer;
	std::string m_appID;
	std::mutex m_sendMutex;

};

} /* namespace amqp */
} /* namespace offcenter */

#endif /* LIB_OFFCENTER_AMQP_SRC_PRODUCER_H_ */
