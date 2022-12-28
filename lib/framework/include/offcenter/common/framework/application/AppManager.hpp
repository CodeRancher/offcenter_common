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
 * @file   AppManager.hpp
 * @author Scott Brauer
 * @date   04-09-2021
 */

#ifndef OffcenterCommonFramework_APPLICATION_APPMANAGER_HPP_
#define OffcenterCommonFramework_APPLICATION_APPMANAGER_HPP_

//#include "IManagedApp.hpp"
#include "offcenter/common/program_options/ProgramOptionsManager.hpp"
#include "offcenter/common/framework/application/BasicAppConfig.hpp"
#include "offcenter/common/framework/program_options/ManagedAppProgramOptions.hpp"

namespace offcenter {
namespace common {
namespace framework {
namespace application {

template <class IAPP>
class AppManager
{
public:
	explicit AppManager():
		m_app(),
		m_optionsManager(),
		m_configPtr(),
		m_skipExecution(false)
	{}

	virtual ~AppManager() = default;

	/**
	 *  Allow the application to process the command line
	 *  /param argc number of parameters
	 *  /param argv	array of parameters
	 */


	/**
	 *  Begin execution of the application
	 */
	void start(int argc, char** argv)
	{
		try {
			m_configPtr = m_optionsManager.add<ManagedAppProgramOptions>();
			onInitProgramOptions(m_optionsManager);
			processCommandLine(argc, argv);
			if (!m_skipExecution) {
				try {
					onSetUp();
					onExecute();
				} catch (const std::runtime_error& e) {
					onTearDown();
					throw;
				}
				onTearDown();
			}
		} catch (std::runtime_error& e) {
			std::cout << "System Error: " << e.what() << std::endl;
		}
	}

	virtual void onInitProgramOptions(program_options::ProgramOptionsManager& optionsManager) {
		m_app.onInitProgramOptions(optionsManager);
	}

	virtual void onSetUp() { m_app.onSetUp(); }
	virtual void onExecute() { m_app.onExecute(); }
	virtual void onTearDown() { m_app.onTearDown(); }
	virtual void onHelp(const std::string& help) { m_app.onHelp(help); }
	virtual void onVersion() { m_app.onVersion(); }

private:
	void processCommandLine(int argc, char** argv)
	{
		try {
			m_optionsManager.processCommandLine(argc, argv);

			if (m_configPtr->help()) {
				onHelp(m_optionsManager.help());
				m_skipExecution = true;
			}

			if (m_configPtr->version()) {
				onVersion();
				m_skipExecution = true;
			}
		} catch(const boost::program_options::error& e) {
			std::cerr << "Error:" << std::endl << "\t" << e.what() << std::endl << std::endl;
			onHelp(m_optionsManager.help());
			m_skipExecution = true;
			std::cerr << "Exiting" << std::endl;
		}
	}


protected:
	IAPP m_app;
	bool m_skipExecution;

private:
	program_options::ProgramOptionsManager m_optionsManager;
	ManagedAppProgramOptions::ConfigPtr m_configPtr;

};

} /* namespace application */
} /* namespace framework */
} /* namespace common */
} /* namespace offcenter */

#endif /* OffcenterCommonFramework_APPLICATION_APPMANAGER_HPP_ */
