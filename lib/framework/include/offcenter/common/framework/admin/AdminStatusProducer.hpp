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
 * @file   AdminStatusProvider.hpp
 * @author Scott Brauer
 * @date   05-03-2021
 */

#ifndef OFFCENTER_COMMON_FRAMEWORK_ADMIN_ADMINSTATUSPROVIDER_HPP_
#define OFFCENTER_COMMON_FRAMEWORK_ADMIN_ADMINSTATUSPROVIDER_HPP_

#include <memory>
#include <mutex>

#include "offcenter/amqp/SessionProducer.hpp"
#include "offcenter/amqp/Producer.hpp"
#include "offcenter/common/framework/admin/AdminStatusMessage.hpp"

namespace offcenter {
namespace common {
namespace framework {
namespace admin {

/**
 *
 */
class AdminStatusProducer: public offcenter::amqp::Producer<AdminStatusMessage::MessageType, AdminStatusMessage>
{
public:
	using Ptr = std::unique_ptr<AdminStatusProducer>;
	using Parent = offcenter::amqp::Producer<AdminStatusMessage::MessageType, AdminStatusMessage>;

	static Ptr factory(offcenter::amqp::SessionProducer::Ptr&& sessionProducer, const std::string& appID) {
		return std::make_unique<AdminStatusProducer>(std::forward<offcenter::amqp::SessionProducer::Ptr>(sessionProducer), appID);
	}

public:
	explicit AdminStatusProducer(offcenter::amqp::SessionProducer::Ptr&& sessionProducer, const std::string& appID);
	virtual ~AdminStatusProducer();

	void ready();
	void starting();
	void running();
	void stopping();
	void stopped();
	void pausing();
	void paused();
	void resuming();
	void error();
	void unknown();

private:
	void sendMessage(const AdminStatusState adminStatusState);

private:
	AdminStatusMessage m_lastMessage;

};

} /* namespace admin */
} /* namespace framework */
} /* namespace common */
} /* namespace offcenter */

#endif /* OFFCENTER_COMMON_FRAMEWORK_ADMIN_ADMINSTATUSPROVIDER_HPP_ */
