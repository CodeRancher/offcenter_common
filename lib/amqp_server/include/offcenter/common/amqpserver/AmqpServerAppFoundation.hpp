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
 * @file   AmqpServerAppFoundation.hpp
 * @author Scott Brauer
 * @date   04-15-2021
 */
#ifndef OffcenterCommon_AMQPSERVER_AMQPSERVERAPPFOUNDATION_HPP_
#define OffcenterCommon_AMQPSERVER_AMQPSERVERAPPFOUNDATION_HPP_

//#include <cpprest/http_msg.h>
//#include <cpprest/http_listener.h>
//#include <pplx/pplxtasks.h>

#include "offcenter/common/amqp/Helper.hpp"

#include "offcenter/common/framework/application/BasicAppFoundation.hpp"
using namespace offcenter::common;

namespace offcenter {
namespace common {
namespace amqpserver {

/**
 *
 */
class AmqpServerAppFoundation: public framework::application::BasicAppFoundation
{
public:
	AmqpServerAppFoundation();
	virtual ~AmqpServerAppFoundation();

};

} /* namespace amqpserver */
} /* namespace common */
} /* namespace offcenter */

#endif /* OffcenterCommon_AMQPSERVER_AMQPSERVERAPPFOUNDATION_HPP_ */
