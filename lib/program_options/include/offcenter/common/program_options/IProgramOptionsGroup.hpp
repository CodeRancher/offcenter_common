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
 * @file   IProgramOptionsGroup.hpp
 * @author Scott Brauer
 * @date   04-14-2019
 */

#ifndef OFFCENTER_COMMON_PROGRAMOPTIONS_IPROGRAMOPTIONSGROUP_HPP_
#define OFFCENTER_COMMON_PROGRAMOPTIONS_IPROGRAMOPTIONSGROUP_HPP_

#include <memory>

namespace offcenter {
namespace common {
namespace program_options {

/**
 * @interface IProgramOptionsGroup
 * @brief
 */
class IProgramOptionsGroup
{
public:
	using Ptr = std::shared_ptr<IProgramOptionsGroup>;

public:
	virtual ~IProgramOptionsGroup() = default;

	virtual void processOptions(po::variables_map& vm) = 0;
	virtual void validateOptions(po::variables_map& vm) = 0;


	virtual bool isCommandLineOption() = 0;
	virtual bool isConfigFileOption() = 0;
	virtual bool isVisibleInHelpOption() = 0;

	virtual bool hasConfigFileName() = 0;
	virtual std::string getConfigFileName() = 0;
	virtual void updateSharedData() = 0;


	virtual po::options_description& optionsDescription() = 0;

};

} /* namespace program_options */
} /* namespace common */
} /* namespace offcenter */

#endif /* OFFCENTER_COMMON_PROGRAMOPTIONS_IPROGRAMOPTIONSGROUP_HPP_ */
