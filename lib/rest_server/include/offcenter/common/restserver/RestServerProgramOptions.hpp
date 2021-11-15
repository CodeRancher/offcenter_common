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
 * @file   RestServerProgramOptions.hpp
 * @author Scott Brauer
 * @date   05-18-2021
 */

#ifndef OFFCENTER_COMMON_RESTSERVER_RESTSERVERPROGRAMOPTIONS_HPP_
#define OFFCENTER_COMMON_RESTSERVER_RESTSERVERPROGRAMOPTIONS_HPP_

#include <functional>

#include <boost/bind/bind.hpp>

#include "offcenter/common/program_options/ProgramOptionsGroup.hpp"
#include "offcenter/common/restserver/RestServerOptions.hpp"
using namespace offcenter::common;

namespace offcenter {
namespace common {
namespace restserver {

class RestServerProgramOptions:
		public program_options::ProgramOptionsGroup<offcenter::common::restserver::RestServerOptions>
{
public:
	RestServerProgramOptions(const std::string& preOptionText = ""):
		ProgramOptionsGroup("Rest Server Options")
	{
		optionsDescription().add_options()
				("RestURI.scheme", po::value<std::string>(&optionConfig().m_scheme)->default_value("http"), "scheme of the URI [http]")
				("RestURI.userInfo", po::value<std::string>(&optionConfig().m_userInfo), "user info component of the URI")
				("RestURI.host", po::value<std::string>(&optionConfig().m_host)->default_value("host_auto_ip4"), "host component of the URI [host_auto_ip4]")
				("RestURI.port", po::value<std::string>(&optionConfig().m_port)->default_value("6503"), "port component of the URI [6503]")
				("RestURI.path", po::value<std::string>(&optionConfig().m_path)->default_value("/offcenter/trade"), "path component of the URI [/offcenter/trade]")
		;
	}

	virtual ~RestServerProgramOptions() = default;

private:
	std::string getName(const std::string& name) { return m_preOptionText + "." + name; }

private:
	static inline const std::string m_preOptionText = "RestURI";
};

} /* namespace restserver */
} /* namespace common */
} /* namespace offcenter */

#endif /* OFFCENTER_COMMON_RESTSERVER_RESTSERVERPROGRAMOPTIONS_HPP_ */
