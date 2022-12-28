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
 * @file   Message.hpp
 * @author Scott Brauer
 * @date   12-03-2018
 */

#ifndef LIB_OFFCENTER_AMQP_SRC_MESSAGE_HPP_
#define LIB_OFFCENTER_AMQP_SRC_MESSAGE_HPP_

#include <cassert>

#include <cms/Message.h>
#include <cms/BytesMessage.h>
#include <cms/StreamMessage.h>
#include <cms/TextMessage.h>
#include <cms/MapMessage.h>

namespace offcenter {
namespace common {
namespace amqp {

template <class CMSMessageType>
class MessageBase {
public:
	using MessageType = offcenter::common::amqp::MessageBase<CMSMessageType>;
	using MessagePtr = std::shared_ptr<MessageType>;
	static MessagePtr factory() {
		return std::make_shared<MessageType>();
	}

	using MessageUPtr = std::unique_ptr<MessageType>;
	static MessageUPtr uFactory() {
		return std::make_unique<MessageType>();
	}

public:
	MessageBase() = default;
	virtual ~MessageBase() = default;

	void readFromCMSMessage(const cms::Message *message) {
		assert(message != nullptr);
		readFromMessage(dynamic_cast<const CMSMessageType*>(message));
	}
	virtual void readFromMessage(const CMSMessageType *message) = 0;

	void writeToCMSMessage(cms::Message *message) {
		assert(message != nullptr);
		writeToMessage(dynamic_cast<CMSMessageType*>(message));
	}
	virtual void writeToMessage(CMSMessageType *message) const = 0;

};

using Message = MessageBase<cms::Message>;
using BytesMessage = MessageBase<cms::BytesMessage>;
using StreamMessage = MessageBase<cms::StreamMessage>;
using TextMessage = MessageBase<cms::TextMessage>;
using MapMessage = MessageBase<cms::MapMessage>;

} /* namespace amqp */
} /* namespace common */
} /* namespace offcenter */

#endif /* LIB_OFFCENTER_AMQP_SRC_MESSAGE_HPP_ */
