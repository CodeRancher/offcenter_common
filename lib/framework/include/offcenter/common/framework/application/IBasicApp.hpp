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
 * @file IBasicApp.hpp
 * @author Scott Brauer
 * @date 02-27-2019
 */

#ifndef OffcenterCommonFramework_APPLICATION_IBASICAPP_HPP_
#define OffcenterCommonFramework_APPLICATION_IBASICAPP_HPP_

#include <string>

#include "offcenter/common/program_options/ProgramOptionsManager.hpp"

namespace offcenter {
namespace common {
namespace framework {
namespace application {

class IBasicApp
{
public:
	virtual ~IBasicApp() = default;

	virtual void onInitProgramOptions(program_options::ProgramOptionsManager& optionsManager) = 0;
	virtual void onSetUp() = 0;
	virtual void onExecute() = 0;
	virtual void onTearDown() = 0;
	virtual void onHelp(const std::string& help) = 0;
	virtual void onVersion() = 0;
};

} /* namespace application */
} /* namespace framework */
} /* namespace common */
} /* namespace offcenter */

#endif /* OffcenterCommonFramework_APPLICATION_IBASICAPP_HPP_ */
