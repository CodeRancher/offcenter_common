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
 * @file   AMQPAppConfig.hpp
 * @author Scott Brauer
 * @date   06-09-2019
 */

#ifndef OFFCENTER_COMMON_FRAMEWORK_CONFIG_AMQPAPPCONFIG_HPP_
#define OFFCENTER_COMMON_FRAMEWORK_CONFIG_AMQPAPPCONFIG_HPP_

namespace offcenter {
namespace common {
namespace framework {
namespace application {

#include <string>

class AMQPAppConfig
{
private:
	std::string m_amqpConfigFile;

	//std::string* amqpConfigFile_ptr() { return &m_amqpConfigFile; }

public:
	AMQPAppConfig():
		m_amqpConfigFile("")
	{}

	virtual ~AMQPAppConfig() = default;

	std::string amqpConfigFile() const { return m_amqpConfigFile; }

	friend class AMQPAppProgramOptions;

};

} /* namespace config */
} /* namespace framework */
} /* namespace common */
} /* namespace offcenter */

#endif /* OFFCENTER_COMMON_FRAMEWORK_CONFIG_AMQPAPPCONFIG_HPP_ */
