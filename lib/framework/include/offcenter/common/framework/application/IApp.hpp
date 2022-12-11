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
 * @file IApp.hpp
 * @author Scott Brauer
 * @date 04-17-2019
 */

#ifndef OffcenterCommonFramework_APPLICATION_IAPP_HPP_
#define OffcenterCommonFramework_APPLICATION_IAPP_HPP_

#include <string>

#include "offcenter/common/program_options/ProgramOptionsManager.hpp"
using namespace offcenter::common;

namespace offcenter {
namespace common {
namespace framework {
namespace application {

class IApp
{
public:
	virtual ~IApp() = default;

	virtual void onInitProgramOptions(program_options::ProgramOptionsManager& optionsManager) {}
	virtual void onSetUp() {}
	virtual void onExecute() {}
	virtual void onTearDown() {}
	virtual void onHelp(const std::string& help) {}
	virtual void onVersion() {}
};

} /* namespace application */
} /* namespace framework */
} /* namespace common */
} /* namespace offcenter */

#endif /* OffcenterCommonFramework_APPLICATION_IAPP_HPP_ */
