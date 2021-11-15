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
 * @file   BasicAppProgramOptions.hpp
 * @author Scott Brauer
 * @date   04-27-2019
 */

#ifndef OFFCENTER_COMMON_FRAMEWORK_PROGRAMOPTIONS_BASICAPPPROGRAMOPTIONS_HPP_
#define OFFCENTER_COMMON_FRAMEWORK_PROGRAMOPTIONS_BASICAPPPROGRAMOPTIONS_HPP_

#include "offcenter/common/program_options/ProgramOptionsGroup.hpp"
#include "offcenter/common/framework/application/BasicAppConfig.hpp"
using namespace offcenter::common;

namespace offcenter {
namespace common {
namespace framework {
namespace application {

class BasicAppProgramOptions: public program_options::ProgramOptionsGroup<BasicAppConfig>
{
public:
	BasicAppProgramOptions():
		program_options::ProgramOptionsGroup<BasicAppConfig>(std::string("Basic Options"))
	{
		optionsDescription().add_options()
				("help,h", po::bool_switch(&optionConfig().m_help)->default_value(false), "Display this help")
				("version,v", po::bool_switch(&optionConfig().m_version)->default_value(false), "Display the application version")
				("configfile", po::value<std::string>(&optionConfig().m_configFile)->default_value(""), "Read config values from a file")
				;
	}

	virtual ~BasicAppProgramOptions() = default;
	void processOptions(po::variables_map& vm) override {}
	void validateOptions(po::variables_map& vm) override {}

	bool hasConfigFileName() override
	{
		return optionConfig().configFile() != "";
	}

	std::string getConfigFileName() override
	{
		return optionConfig().configFile();
	}
};

} /* namespace application */
} /* namespace framework */
} /* namespace common */
} /* namespace offcenter */

#endif /* OFFCENTER_COMMON_FRAMEWORK_PROGRAMOPTIONS_BASICAPPPROGRAMOPTIONS_HPP_ */
