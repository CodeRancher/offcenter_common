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
 * @file   IRestServerApp.hpp
 * @author Scott Brauer
 * @date   04-12-2021
 */

#ifndef OFFCENTER_COMMON_RESTSERVER_IRESTSERVERAPP_HPP_
#define OFFCENTER_COMMON_RESTSERVER_IRESTSERVERAPP_HPP_

#include <string>

#include <cpprest/http_msg.h>
#include <cpprest/http_listener.h>
#include <cpprest/base_uri.h>

#include "offcenter/common/program_options/ProgramOptionsManager.hpp"
#include "offcenter/common/framework/application/IApp.hpp"
#include "offcenter/common/restserver/AutoMethodHandler.hpp"
using namespace offcenter::common;

namespace offcenter {
namespace common {
namespace restserver {

/**
 *
 */
class IRestServerApp: public framework::application::IApp
{
public:
	virtual ~IRestServerApp() = default;

	virtual void onInitMethodHandlers(restserver::AutoMethodHandler& methodHandler) {}
	virtual void onInitEndpoint(web::uri& uri) {}
};

} /* namespace restserver */
} /* namespace common */
} /* namespace offcenter */

#endif /* OFFCENTER_COMMON_RESTSERVER_IRESTSERVERAPP_HPP_ */
