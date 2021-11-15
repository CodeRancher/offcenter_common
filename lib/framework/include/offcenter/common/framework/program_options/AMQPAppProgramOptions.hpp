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
 * @file   AMQPAppProgramOptions.hpp
 * @author Scott Brauer
 * @date   06-09-2019
 */

#ifndef OFFCENTER_COMMON_FRAMEWORK_APPLICATION_AMQPAPPPROGRAMOPTIONS_HPP_
#define OFFCENTER_COMMON_FRAMEWORK_APPLICATION_AMQPAPPPROGRAMOPTIONS_HPP_

#include "offcenter/common/program_options/ProgramOptionsGroup.hpp"
#include "offcenter/common/framework/application/AMQPAppConfig.hpp"

namespace offcenter {
namespace common {
namespace framework {
namespace application {

class AMQPAppProgramOptions: public offcenter::common::program_options::ProgramOptionsGroup<AMQPAppConfig>
{
public:
	AMQPAppProgramOptions():
		ProgramOptionsGroup("AMQP Options")
	{
		optionsDescription().add_options()
				("amqpconfigfile", po::value<std::string>(&optionConfig().m_amqpConfigFile)->default_value(""), "Read amqp config values from a file")
				;
	}

	virtual ~AMQPAppProgramOptions() = default;
	void processOptions(po::variables_map& vm) override {}
	void validateOptions(po::variables_map& vm) override {}

	bool hasConfigFileName() override
	{
		return optionConfig().amqpConfigFile() != "";
	}

	std::string getConfigFileName() override
	{
		return optionConfig().amqpConfigFile();
	}
};

} /* namespace application */
} /* namespace framework */
} /* namespace common */
} /* namespace offcenter */

#endif /* OFFCENTER_COMMON_FRAMEWORK_APPLICATION_AMQPAPPPROGRAMOPTIONS_HPP_ */
