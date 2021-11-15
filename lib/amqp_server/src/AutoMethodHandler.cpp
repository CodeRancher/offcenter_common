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
 * @file   AutoMethodHandler.cpp
 * @author Scott Brauer
 * @date   04-14-2021
 */
#include "offcenter/common/amqpserver/AutoMethodHandler.hpp"

namespace offcenter {
namespace common {
namespace restserver {

AutoMethodHandler::AutoMethodHandler()
{
	// TODO Auto-generated constructor stub

}

AutoMethodHandler::~AutoMethodHandler()
{
	// TODO Auto-generated destructor stub
}

int AutoMethodHandler::findAndExecute(web::http::http_request& request) {
	int pathMatchCount = 0;
	auto relativePath = web::uri::uri::decode(request.relative_uri().path());
	for (IAutoMethodPath::Ptr& path : m_paths[request.method()]) {
		std::smatch smatch;
		if (std::regex_match(relativePath, smatch, path->regex())) {
			path->action(request, smatch);
			pathMatchCount++;
		}
	}

	return pathMatchCount;
}

} /* namespace restserver */
} /* namespace common */
} /* namespace offcenter */
