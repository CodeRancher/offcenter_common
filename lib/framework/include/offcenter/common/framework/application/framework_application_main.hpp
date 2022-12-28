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
 * @file   framework_application_main.hpp
 * @author Scott Brauer
 * @date   01-17-2022
 */


#ifndef FRAMEWORK_APPLICATION_MAIN_HPP_
#define FRAMEWORK_APPLICATION_MAIN_HPP_

#include <iostream>

#include "easylogging++.h"

#include "offcenter/common/framework/application/AppManager.hpp"
#include "offcenter/common/framework/application/Utility.hpp"

template<typename App, typename AppManager = offcenter::common::framework::application::AppManager<App>>
void framework_application_main(int argc, char **argv, const std::string& appName, const std::string& logFileName)
{
	try {
		std::cout << appName << " App!" << std::endl;

		el::Loggers::reconfigureAllLoggers(el::ConfigurationType::ToFile, "true");
		el::Loggers::reconfigureAllLoggers(el::ConfigurationType::ToStandardOutput, "false");
		el::Loggers::reconfigureAllLoggers(el::ConfigurationType::Format, "%datetime:%thread [%level] %msg");
		el::Loggers::reconfigureAllLoggers(el::ConfigurationType::Filename, "./log/" + logFileName + ".log");

		LOG(INFO) << appName << " App!";

		using ManagedApp = AppManager;
		std::thread appThread = offcenter::common::framework::application::create_basic_app_in_thread<ManagedApp>(argc, argv);
		appThread.join();
	} catch (const std::runtime_error& e) {
		std::cout << "System Error: " << e.what() << std::endl;
	}
}

#endif /* FRAMEWORK_APPLICATION_MAIN_HPP_ */
