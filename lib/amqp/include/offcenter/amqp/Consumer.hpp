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
 * @file   Consumer.hpp
 * @author Scott Brauer
 * @date   11-23-2018
 */

#ifndef LIB_OFFCENTER_AMQP_SRC_CONSUMER_HPP_
#define LIB_OFFCENTER_AMQP_SRC_CONSUMER_HPP_

#include <type_traits>
#include <functional>
#include <memory>
#include <vector>

#include "offcenter/amqp/SessionConsumer.hpp"
#include "offcenter/amqp/MessageCallback.hpp"

namespace offcenter {
namespace amqp {

/**
 *
 */
template <typename TCMSMessageType, typename TAMQPMessageType>
class Consumer : public cms::MessageListener
{
public:
	using Ptr = std::unique_ptr<TAMQPMessageType>;

	template <typename TCallback>
	static Ptr factory(offcenter::amqp::SessionConsumer::Ptr&& sessionConsumer, TCallback &&callback) {
		return std::make_unique<TAMQPMessageType>(std::forward<offcenter::amqp::SessionConsumer::Ptr>(sessionConsumer), std::forward<TCallback>(callback));
	}

	template <typename TCallback>
	static Ptr factory(offcenter::amqp::SessionConsumer::Ptr&& sessionConsumer1, offcenter::amqp::SessionConsumer::Ptr&& sessionConsumer2, TCallback &&callback) {
		return std::make_unique<TAMQPMessageType>(
				std::forward<offcenter::amqp::SessionConsumer::Ptr>(sessionConsumer1),
				std::forward<offcenter::amqp::SessionConsumer::Ptr>(sessionConsumer2),
				std::forward<TCallback>(callback));
	}
private:
	using MessageCallback = offcenter::amqp::MessageCallback<TCMSMessageType, TAMQPMessageType>;

public:
	template <typename TCallback>
	explicit Consumer(offcenter::amqp::SessionConsumer::Ptr&& sessionConsumer, TCallback &&callback):
		cms::MessageListener(),
		m_callback(MessageCallback::factory(std::forward<TCallback>(callback)))
	{
		sessionConsumer->consumer()->setMessageListener(this);
		m_sessionConsumers.push_back(std::move(sessionConsumer));
	}

	template <typename TCallback>
	explicit Consumer(offcenter::amqp::SessionConsumer::Ptr&& sessionConsumer1, offcenter::amqp::SessionConsumer::Ptr&& sessionConsumer2, TCallback &&callback):
		cms::MessageListener(),
		m_callback(MessageCallback::factory(std::forward<TCallback>(callback)))
	{
		sessionConsumer1->consumer()->setMessageListener(this);
		m_sessionConsumers.push_back(std::move(sessionConsumer1));
		sessionConsumer2->consumer()->setMessageListener(this);
		m_sessionConsumers.push_back(std::move(sessionConsumer2));
	}

	virtual ~Consumer() = default;

private:
	/**
	 * Callback method with listener messages
	 *
	 * @param message CMS Message
	 */
	void onMessage(const cms::Message* message) override {
		try {
			m_callback.callback(message);
		} catch(std::runtime_error& e) {
			LOG(ERROR) << e.what();
		}
	}

private:
	std::vector<offcenter::amqp::SessionConsumer::Ptr> m_sessionConsumers;
	MessageCallback m_callback;
};

} /* namespace amqp */
} /* namespace offcenter */

#endif /* LIB_OFFCENTER_AMQP_SRC_CONSUMER_HPP_ */
