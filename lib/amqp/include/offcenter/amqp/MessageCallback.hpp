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
 * @file   MessageCallback.hpp
 * @author Scott Brauer
 * @date   05-13-2021
 */

#ifndef OFFCENTER_AMQP_MESSAGECALLBACK_HPP_
#define OFFCENTER_AMQP_MESSAGECALLBACK_HPP_

#include <functional>
#include <memory>

#include <cms/Message.h>

#include "offcenter/amqp/Helper.hpp"
#include "offcenter/amqp/AMQPException.hpp"

namespace offcenter {
namespace amqp {

/**
 *
 */
template <typename TCMSMessageType, typename TAMQPMessageType>
class MessageCallback
{
public:
	struct ICallback {
		using Ptr = std::unique_ptr<ICallback>;

		virtual ~ICallback() = default;
		virtual void callback(const cms::Message* message) = 0;
	};

private:
	template <typename TCallback>
	struct InternalCallback: public ICallback {
		static typename ICallback::Ptr factory(TCallback&& callback) {
			return std::make_unique<InternalCallback<TCallback>>(std::forward<TCallback>(callback));
		}

		explicit InternalCallback(TCallback&& callback):
			ICallback(),
			m_callback(std::forward<TCallback>(callback))
		{}

		virtual ~InternalCallback() = default;

		void callback(const cms::Message* message) override {
			const TCMSMessageType* cmsMessage = dynamic_cast<const TCMSMessageType*>(message);
			if (cmsMessage == nullptr) {
				throw AMQPException("Invalid type conversion (MessageCallback)");
			} else {
				TAMQPMessageType amqpMessage;
				from_cmsMessage(cmsMessage, amqpMessage);
				m_callback(cmsMessage, amqpMessage);
			}
		}

	private:
		TCallback m_callback;
	};

public:
	template <typename TCallback>
	static typename ICallback::Ptr factory(TCallback&& callback) {
		return std::make_unique<InternalCallback<TCallback>>(std::forward<TCallback>(callback));
	}

public:
	MessageCallback(typename ICallback::Ptr&& callback):
		m_callback(std::forward<typename ICallback::Ptr>(callback)) {}

	virtual ~MessageCallback() = default;

	void callback(const cms::Message* cmsMessage) {
		m_callback->callback(cmsMessage);
	}

private:
	typename ICallback::Ptr m_callback;
};

} /* namespace amqp */
} /* namespace offcenter */

#endif /* OFFCENTER_AMQP_MESSAGECALLBACK_HPP_ */
