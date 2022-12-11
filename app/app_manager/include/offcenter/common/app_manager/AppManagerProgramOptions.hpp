/**
 * Copyright 2022 Scott Brauer
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
 * @file   AppManagerProgramOptions.hpp
 * @author Scott Brauer
 * @date   01-23-2022
 */
#ifndef OffcenterCommon_APPMANAGER_APPMANAGERPROGRAMOPTIONS__H_
#define OffcenterCommon_APPMANAGER_APPMANAGERPROGRAMOPTIONS__H_

#include <functional>
#include <iostream>
#include <sstream>

#include <boost/bind/bind.hpp>

#include "offcenter/common/program_options/ProgramOptionsGroup.hpp"
#include "offcenter/common/app_manager/AppManagerOptions.hpp"

namespace offcenter {
namespace common {
namespace appmanager {

class AppManagerProgramOptions:
		public offcenter::common::program_options::ProgramOptionsGroup<offcenter::common::appmanager::AppManagerOptions>
{
public:
	AppManagerProgramOptions():
		ProgramOptionsGroup("Generate Sine Candlestick Options")
	{
		optionsDescription().add_options()
				("procfile", po::value<std::string>(&optionConfig().m_processFile)->required(), "Process file")
				;
	}

	virtual ~AppManagerProgramOptions() = default;

	virtual void validateOptions(po::variables_map& vm) {

	}
};

} /* namespace app_manager */
} /* namespace common */
} /* namespace offcenter */

#endif /* OffcenterCommon_APPMANAGER_APPMANAGERPROGRAMOPTIONS__H_ */
