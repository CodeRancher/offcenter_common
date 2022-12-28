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
 * @file   AdminControlProducer.hpp
 * @author Scott Brauer
 * @date   05-03-2021
 */

#ifndef OffcenterCommonFramework_ADMIN_ADMINCONTROLPRODUCER_HPP_
#define OffcenterCommonFramework_ADMIN_ADMINCONTROLPRODUCER_HPP_

#include <memory>
#include <mutex>

#include "offcenter/common/amqp/SessionProducerDynamicDestination.hpp"
#include "offcenter/common/framework/admin/AdminControlMessage.hpp"

namespace offcenter {
namespace common {
namespace framework {
namespace admin {

/**
 *
 */
class AdminControlProducer
{
public:
	using Ptr = std::unique_ptr<AdminControlProducer>;

	static Ptr factory(offcenter::common::amqp::SessionProducerDynamicDestination::Ptr sessionProducer, const std::string& appID) {
		return std::make_unique<AdminControlProducer>(std::move(sessionProducer), appID);
	}

public:
	explicit AdminControlProducer(offcenter::common::amqp::SessionProducerDynamicDestination::Ptr sessionProducer, const std::string& appID);
	virtual ~AdminControlProducer();

	void start();
	void start(const std::string& appID);
	void stop();
	void stop(const std::string& appID);
	void pause();
	void pause(const std::string& appID);
	void resume();
	void resume(const std::string& appID);

private:
	void sendMessage(const std::string& appID, const AdminControlState adminControlState);

private:
	offcenter::common::amqp::SessionProducerDynamicDestination::Ptr m_sessionProducer;
	AdminControlMessage m_lastMessage;
	std::mutex m_sendMutex;

};

} /* namespace admin */
} /* namespace framework */
} /* namespace common */
} /* namespace offcenter */

#endif /* OffcenterCommonFramework_ADMIN_ADMINCONTROLPRODUCER_HPP_ */
