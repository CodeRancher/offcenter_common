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
 * @file   AdminStatusConsumer.hpp
 * @author Scott Brauer
 * @date   05-03-2021
 */

#ifndef OffcenterCommonFramework_ADMIN_ADMINSTATUSCONSUMER_HPP_
#define OffcenterCommonFramework_ADMIN_ADMINSTATUSCONSUMER_HPP_

#include <memory>

#include <cms/MessageListener.h>
#include <cms/Message.h>

#include "offcenter/common/amqp/SessionConsumer.hpp"
#include "offcenter/common/amqp/MessageCallback.hpp"
#include "offcenter/common/framework/admin/AdminStatusMessage.hpp"
#include "offcenter/common/amqp/Consumer.hpp"

namespace offcenter {
namespace common {
namespace framework {
namespace admin {

/**
 *
 */
class AdminStatusConsumer : public offcenter::common::amqp::Consumer<AdminStatusMessage::MessageType, AdminStatusMessage>
{
public:
	using Ptr = std::unique_ptr<AdminStatusConsumer>;
	using Parent = offcenter::common::amqp::Consumer<AdminStatusMessage::MessageType, AdminStatusMessage>;

	template <typename TCallback>
	static Ptr factory(offcenter::common::amqp::SessionConsumer::Ptr&& sessionConsumer, TCallback &&callback) {
		return std::make_unique<AdminStatusConsumer>(std::forward<offcenter::common::amqp::SessionConsumer::Ptr>(sessionConsumer), std::forward<TCallback>(callback));
	}

public:
	template <typename TCallback>
	explicit AdminStatusConsumer(offcenter::common::amqp::SessionConsumer::Ptr&& sessionConsumer, TCallback &&callback):
		Parent(std::forward<offcenter::common::amqp::SessionConsumer::Ptr>(sessionConsumer), std::forward<TCallback>(callback))
	{}

	virtual ~AdminStatusConsumer() = default;

};


//class AdminStatusConsumer : public cms::MessageListener
//{
//public:
//	using Ptr = std::unique_ptr<AdminStatusConsumer>;
//
//	template <typename TCallback>
//	static Ptr factory(offcenter::common::amqp::SessionConsumer::Ptr&& sessionConsumer, TCallback &&callback) {
//		return std::make_unique<AdminStatusConsumer>(std::forward<offcenter::common::amqp::SessionConsumer::Ptr>(sessionConsumer), std::forward<TCallback>(callback));
//	}
//private:
//	using MessageCallback = offcenter::common::amqp::MessageCallback<AdminStatusMessage::MessageType, AdminStatusMessage>;
//
//public:
//	template <typename TCallback>
//	explicit AdminStatusConsumer(offcenter::common::amqp::SessionConsumer::Ptr&& sessionConsumer, TCallback &&callback):
//		cms::MessageListener(),
//		m_callback(MessageCallback::factory(std::forward<TCallback>(callback))),
//		m_sessionConsumer(std::move(sessionConsumer))
//	{
//		m_sessionConsumer->consumer()->setMessageListener(this);
//	}
//
//	virtual ~AdminStatusConsumer() = default;
//private:
//	/**
//	 * Callback method with listener messages
//	 *
//	 * @param message CMS Message
//	 */
//	void onMessage(const cms::Message* message) override {
//		try {
//			m_callback.callback(message);
//		} catch(std::runtime_error& e) {
//			LOG(ERROR) << e.what();
//		}
//	}
//
//
//private:
//	offcenter::common::amqp::SessionConsumer::Ptr m_sessionConsumer;
//	MessageCallback m_callback;
//};

} /* namespace admin */
} /* namespace framework */
} /* namespace common */
} /* namespace offcenter */

#endif /* OffcenterCommonFramework_ADMIN_ADMINSTATUSCONSUMER_HPP_ */
