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
 * @file   BasicAppFoundation.cpp
 * @author Scott Brauer
 * @date   04-09-2021
 */

#include <iostream>
#include <exception>

#include "offcenter/common/framework/program_options/BasicAppProgramOptions.hpp"
#include "offcenter/common/framework/application/BasicApp.hpp"
using namespace offcenter::common;

namespace offcenter {
namespace common {
namespace framework {
namespace application {

BasicAppFoundation::BasicAppFoundation():
		IManagedApp(),
		m_optionsManager(),
		m_helpDisplayed(false)
{
	m_basicConfigPtr = m_optionsManager.add<BasicAppProgramOptions>();
}

BasicAppFoundation::~BasicAppFoundation()
{
	// TODO Auto-generated destructor stub
}

/**
 * Convert all command line options into configuration classes
 *
 * @param argc count of command line options
 * @param argv array of command line options
 */
void BasicAppFoundation::processCommandLine(int argc, char** argv)
{
	m_optionsManager.processCommandLine(argc, argv);

	if (m_basicConfigPtr->help()) {
		foundationOnHelp(m_optionsManager.help());
		m_helpDisplayed = true;
	}

	if (m_basicConfigPtr->version()) {
		foundationOnVersion();
	}
}

void BasicAppFoundation::start()
{
	try {
		if (!m_helpDisplayed) {
			foundationOnInitProgramOptions(m_optionsManager);
			try {
				foundationOnSetUp();
				foundationOnExecute();
			} catch (const std::runtime_error& e) {
				foundationOnTearDown();
				throw;
			}
			foundationOnTearDown();
		}
	} catch (std::runtime_error& e) {
		std::cout << "System Error: " << e.what() << std::endl;
	}
}

} /* namespace application */
} /* namespace framework */
} /* namespace common */
} /* namespace offcenter */
