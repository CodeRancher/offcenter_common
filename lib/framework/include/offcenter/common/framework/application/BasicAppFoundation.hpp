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
 * @file   BasicAppFoundation.hpp
 * @author Scott Brauer
 * @date   04-09-2021
 */

#ifndef OffcenterCommonFramework_APPLICATION_BASICAPPFOUNDATION_HPP_
#define OffcenterCommonFramework_APPLICATION_BASICAPPFOUNDATION_HPP_

#include "IManagedApp.hpp"
#include "offcenter/common/program_options/ProgramOptionsManager.hpp"
#include "offcenter/common/framework/application/BasicAppConfig.hpp"
#include "offcenter/common/framework/program_options/BasicAppProgramOptions.hpp"
using namespace offcenter::common;

namespace offcenter {
namespace common {
namespace framework {
namespace application {

class BasicAppFoundation: public IManagedApp
{
public:
	explicit BasicAppFoundation();
	virtual ~BasicAppFoundation();

	/**
	 *  Allow the application to process the command line
	 *  /param argc number of parameters
	 *  /param argv	array of parameters
	 */
	void processCommandLine(int argc, char** argv);

	/**
	 *  Begin execution of the application
	 */
	void start();

protected:
	// Children
	virtual void internalOnInitProgramOptions(program_options::ProgramOptionsManager& optionsManager) = 0;
	virtual void internalOnSetUp() = 0;
	virtual void internalOnExecute() = 0;
	virtual void internalOnTearDown() = 0;
	virtual void internalOnHelp(const std::string& help) = 0;
	virtual void internalOnVersion() = 0;

private:
	program_options::ProgramOptionsManager m_optionsManager;
	BasicAppProgramOptions::ConfigPtr m_basicConfigPtr;
	bool m_helpDisplayed;

};

} /* namespace application */
} /* namespace framework */
} /* namespace common */
} /* namespace offcenter */

#endif /* OffcenterCommonFramework_APPLICATION_BASICAPPFOUNDATION_HPP_ */
