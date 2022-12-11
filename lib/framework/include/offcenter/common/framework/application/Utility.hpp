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
 * @file   Utility.hpp
 * @author Scott Brauer
 * @date   03-23-2021
 */

#ifndef OffcenterCommonFramework_APPLICATION_UTILITY_HPP_
#define OffcenterCommonFramework_APPLICATION_UTILITY_HPP_

#include <thread>

namespace offcenter {
namespace common {
namespace framework {
namespace application {

/**
 * Instantiate
 */
template<class T>
void start_basic_app_in_thread(int argc, char** argv)
{
	T app;
	app.start(argc, argv);
}

/**
 * Create a managed application in it's own thread
 * @param argc	Allows for command line processing
 * @param argv	Allows for command line processing
 */
template<class T>
std::thread create_basic_app_in_thread(int argc, char **argv)
{
	std::thread appThread(start_basic_app_in_thread<T>, argc, argv);
	return appThread;
}



} /* namespace application */
} /* namespace framework */
} /* namespace common */
} /* namespace offcenter */

#endif /* OffcenterCommonFramework_APPLICATION_UTILITY_HPP_ */
