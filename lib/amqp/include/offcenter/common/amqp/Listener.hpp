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
 * @file   Listener.hpp
 * @author Scott Brauer
 * @date   02-20-2020
 */

#ifndef OFFCENTER_AMQP_LISTENER_HPP_
#define OFFCENTER_AMQP_LISTENER_HPP_

#include <memory>

#include <cms/MessageListener.h>
#include <cms/Message.h>

#include "easylogging++.h"

#include "offcenter/common/amqp/Helper.hpp"

namespace offcenter {
namespace amqp {

/**
 * Base type for all listeners.
 *
 * Connects to a Consumer and will call the onMessage callback
 */
template <class MESSAGE, class MESSAGETYPE>
class Listener : public cms::MessageListener
{
public:
	using CallBack = std::function<void(const MESSAGETYPE* cmsMessage, const MESSAGE& amqpMessage)>;

	using Ptr = std::unique_ptr<Listener<MESSAGE, MESSAGETYPE> >;

	static Ptr factory(offcenter::amqp::MessageConsumerPtr consumer, CallBack callback) {
		return std::make_unique<Listener<MESSAGE, MESSAGETYPE> >(consumer, callback);
	}

public:
	/**
	 * Constructor for the base listener
	 *
	 * @param consumer Message Consumer to connect to
	 */
	explicit Listener(offcenter::amqp::MessageConsumerPtr consumer, CallBack callback):
			cms::MessageListener(),
			m_callback(callback)
	{
		if (consumer->getMessageListener()) {
			throw AMQPException("Attempt to assign a new message listener to a consumer");
		}

		consumer->setMessageListener(this);
	}

	/**
	 * Destructor
	 */
	virtual ~Listener() = default;

	/**
	 * Callback method with listener messages
	 *
	 * @param message CMS Message
	 */
	void onMessage(const cms::Message* message) override {
		try {
			const MESSAGETYPE* cmsMessage = dynamic_cast<const MESSAGETYPE*>(message);
			if (cmsMessage == nullptr) {
				LOG(ERROR) << "CMS Message is not the correct type";
			} else {
				MESSAGE amqpMessage;
				from_cmsMessage(cmsMessage, amqpMessage);
				m_callback(cmsMessage, amqpMessage);
			}
		} catch(std::runtime_error& e) {
			LOG(ERROR) << e.what();
		}
		/*
		MESSAGE amqpMessage;

		const MESSAGETYPE cmsMessage = messageFactory<MESSAGETYPE>(message);
		from_cmsMessage(*cmsMessage, amqpMessage);
		m_callback(cmsMessage, amqpMessage);
		*/
	}

private:
	CallBack m_callback;
};

} /* namespace amqp */
} /* namespace offcenter */

#endif /* OFFCENTER_AMQP_LISTENER_HPP_ */
