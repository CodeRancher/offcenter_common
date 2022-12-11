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
 * @file   AdminControlConsumer.hpp
 * @author Scott Brauer
 * @date   05-06-2021
 */

#ifndef OffcenterCommonFramework_ADMIN_ADMINCONTROLCONSUMER_HPP_
#define OffcenterCommonFramework_ADMIN_ADMINCONTROLCONSUMER_HPP_

#include <memory>

#include <cms/MessageListener.h>
#include <cms/Message.h>

#include "easylogging++.h"

#include "offcenter/common/amqp/SessionConsumer.hpp"
#include "offcenter/common/amqp/MessageCallback.hpp"
#include "offcenter/common/framework/admin/AdminControlMessage.hpp"
#include "offcenter/common/amqp/Consumer.hpp"

namespace offcenter {
namespace common {
namespace framework {
namespace admin {

/**
 *
 */
class AdminControlConsumer : public offcenter::amqp::Consumer<AdminControlMessage::MessageType, AdminControlMessage>
{
public:
	using Ptr = std::unique_ptr<AdminControlConsumer>;
	using Parent = offcenter::amqp::Consumer<AdminControlMessage::MessageType, AdminControlMessage>;

	template <typename TCallback>
	static Ptr factory(offcenter::amqp::SessionConsumer::Ptr&& generalSessionConsumer, offcenter::amqp::SessionConsumer::Ptr&& specificSessionConsumer, TCallback &&callback) {
		return std::make_unique<AdminControlConsumer>(
				std::forward<offcenter::amqp::SessionConsumer::Ptr>(generalSessionConsumer),
				std::forward<offcenter::amqp::SessionConsumer::Ptr>(specificSessionConsumer),
				std::forward<TCallback>(callback));
	}

public:
	template <typename TCallback>
	explicit AdminControlConsumer(offcenter::amqp::SessionConsumer::Ptr&& generalSessionConsumer, offcenter::amqp::SessionConsumer::Ptr&& specificSessionConsumer, TCallback &&callback):
			Parent(std::forward<offcenter::amqp::SessionConsumer::Ptr>(generalSessionConsumer), std::forward<offcenter::amqp::SessionConsumer::Ptr>(specificSessionConsumer), std::forward<TCallback>(callback))
	{}

	virtual ~AdminControlConsumer() = default;

};

} /* namespace admin */
} /* namespace framework */
} /* namespace common */
} /* namespace offcenter */

#endif /* OffcenterCommonFramework_ADMIN_ADMINCONTROLCONSUMER_HPP_ */
