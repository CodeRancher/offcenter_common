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
 * @file   BasicAppConfig.hpp
 * @author Scott Brauer
 * @date   04-27-2019
 */

#ifndef OffcenterCommonFramework_APPLICATION_BASICAPPCONFIG_HPP_
#define OffcenterCommonFramework_APPLICATION_BASICAPPCONFIG_HPP_

#include <string>

namespace offcenter {
namespace common {
namespace framework {
namespace application {

class BasicAppConfig
{
private:
	bool m_help;
	bool m_version;
	std::string m_configFile;
	/*
	bool* help_ptr() { return &m_help; }
	bool* version_ptr() { return &m_version; }
	std::string* configFile_ptr() { return &m_configFile; }
	*/

public:
	BasicAppConfig():
		m_help(false),
		m_version(false),
		m_configFile("")
	{}

	virtual ~BasicAppConfig() = default;

	bool help() const { return m_help; }
	bool version() const { return m_version; }
	std::string configFile() const { return m_configFile; }

	friend class BasicAppProgramOptions;

};

} /* namespace config */
} /* namespace framework */
} /* namespace common */
} /* namespace offcenter */

#endif /* OffcenterCommonFramework_APPLICATION_BASICAPPCONFIG_HPP_ */
