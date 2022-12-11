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
 * @file   MessageBase.hpp
 * @author Scott Brauer
 * @date   12-03-2018
 */

#ifndef LIB_OFFCENTER_AMQP_SRC_MESSAGEBASE_HPP_
#define LIB_OFFCENTER_AMQP_SRC_MESSAGEBASE_HPP_

namespace offcenter {
namespace amqp {

template <class messageType>
class MessageBase {
public:
	MessageBase() = default;
	virtual ~MessageBase() = default;

//	void internalRead() {
//		const TextMessage* textMessage =
//		                dynamic_cast< const TextMessage* >( message );
//	}
//
//	void internalWrite() {
//
//	}

	virtual void read(messageType *message) = 0;
	virtual void write(messageType *message) = 0;

};

} /* namespace amqp */
} /* namespace offcenter */

#endif /* LIB_OFFCENTER_AMQP_SRC_MESSAGEBASE_HPP_ */
