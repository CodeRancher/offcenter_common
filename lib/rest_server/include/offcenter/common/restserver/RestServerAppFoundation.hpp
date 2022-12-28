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
 * @file   RestServerAppFoundation.hpp
 * @author Scott Brauer
 * @date   04-09-2021
 */

#ifndef OffcenterCommon_RESTSERVER_RESTSERVERAPPFOUNDATION_HPP_
#define OffcenterCommon_RESTSERVER_RESTSERVERAPPFOUNDATION_HPP_

#include <cpprest/http_msg.h>
#include <cpprest/http_listener.h>
#include <pplx/pplxtasks.h>

#include "offcenter/common/framework/application/BasicAppFoundation.hpp"

namespace offcenter {
namespace common {
namespace restserver {

/**
 *
 */
class RestServerAppFoundation: public framework::application::BasicAppFoundation
{
public:
	RestServerAppFoundation();
	virtual ~RestServerAppFoundation();

};

} /* namespace restserver */
} /* namespace common */
} /* namespace offcenter */

#endif /* OffcenterCommon_RESTSERVER_RESTSERVERAPPFOUNDATION_HPP_ */
