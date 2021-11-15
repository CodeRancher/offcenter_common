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
 * @file   RestServerOptions.hpp
 * @author Scott Brauer
 * @date   05-18-2021
 */
#ifndef OFFCENTER_COMMON_RESTSERVER_RESTSERVEROPTIONS_HPP_
#define OFFCENTER_COMMON_RESTSERVER_RESTSERVEROPTIONS_HPP_

#include <string>

#include <cpprest/uri_builder.h>

#include <boost/algorithm/string.hpp>

namespace offcenter {
namespace common {
namespace restserver {

class RestServerOptions
{
public:
	explicit RestServerOptions():
		m_scheme(""),
		m_userInfo(""),
		m_host(""),
		m_port(""),
		m_path("")
	{}

	virtual ~RestServerOptions() {}

	std::string scheme() { return trim(m_scheme); }
	std::string userInfo() { return trim(m_userInfo); }
	std::string host() { return trim(m_host); }
	std::string port() { return trim(m_port); }
	std::string path() { return trim(m_path); }

	web::uri uri() {
		web::uri_builder uriBuilder;

		if (!scheme().empty()) { uriBuilder.set_scheme(m_scheme); }
		if (!userInfo().empty()) { uriBuilder.set_user_info(userInfo()); }
		if (!host().empty()) { uriBuilder.set_host(host()); }
		if (!port().empty()) { uriBuilder.set_port(port()); }
		if (!path().empty()) { uriBuilder.set_path(path()); }
		return uriBuilder.to_uri();
	}

	friend class RestServerProgramOptions;

private:
	std::string trim(std::string str) {
		boost::algorithm::trim(str);
		return str;
	}

private:
	std::string m_scheme;
	std::string m_userInfo;
	std::string m_host;
	std::string m_port;
	std::string m_path;

};

} /* namespace restserver */
} /* namespace common */
} /* namespace offcenter */

#endif /* OFFCENTER_COMMON_RESTSERVER_RESTSERVEROPTIONS_HPP_ */
