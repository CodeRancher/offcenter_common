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
 * @file   AutoMethodHandler.hpp
 * @author Scott Brauer
 * @date   04-14-2021
 */

#ifndef OffcenterCommon_RESTSERVER_AUTOMETHODHANDLER_HPP_
#define OffcenterCommon_RESTSERVER_AUTOMETHODHANDLER_HPP_

#include <vector>
#include <map>

#include "easylogging++.h"

#include "offcenter/common/restserver/AutoMethodPath.hpp"

namespace offcenter {
namespace common {
namespace restserver {

/**
 *
 */
class AutoMethodHandler
{
public:
	using AutoMethodPaths = std::vector<IAutoMethodPath::Ptr>;
	using AutoMethodPathsMap = std::map<web::http::method, AutoMethodPaths>;

public:
	explicit AutoMethodHandler();
	virtual ~AutoMethodHandler();

	template<typename ACTION>
	void addHandler(const web::http::method& method, const std::string& path, const std::string& description, ACTION&& action) {
		LOG(DEBUG) << "addHandler method(" << method << ") path(" << path << ") description(" << description << ")";
		m_paths[method].push_back(offcenter::common::restserver::autoMethodPathFactory(path, description, std::move(action)));
	}

	int findAndExecute(web::http::http_request& request);

private:
	AutoMethodPathsMap m_paths;

};

} /* namespace restserver */
} /* namespace common */
} /* namespace offcenter */

#endif /* OffcenterCommon_RESTSERVER_AUTOMETHODHANDLER_HPP_ */
