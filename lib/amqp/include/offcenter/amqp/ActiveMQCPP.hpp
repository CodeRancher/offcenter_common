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
 * @file   ActiveMQCPP.hpp
 * @author Scott Brauer
 * @date   10-18-2021
 */

#ifndef OFFCENTER_AMQP_ACTIVEMQCPP_HPP_
#define OFFCENTER_AMQP_ACTIVEMQCPP_HPP_

#include <activemq/library/ActiveMQCPP.h>

namespace offcenter {
namespace amqp {

/**
 *
 */
class ActiveMQCPP
{
public:
	explicit ActiveMQCPP() {
		activemq::library::ActiveMQCPP::initializeLibrary();
	}

	virtual ~ActiveMQCPP() {
		activemq::library::ActiveMQCPP::shutdownLibrary();
	}
};

} /* namespace amqp */
} /* namespace offcenter */

#endif /* OFFCENTER_AMQP_ACTIVEMQCPP_HPP_ */
