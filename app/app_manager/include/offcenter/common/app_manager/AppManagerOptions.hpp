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
 * @file   AppManagerOptions.hpp
 * @author Scott Brauer
 * @date   01-23-2022
 */

#ifndef OFFCENTER_COMMON_APPMANAGER_APPMANAGEROPTIONS__H_
#define OFFCENTER_COMMON_APPMANAGER_APPMANAGEROPTIONS__H_

#include <string>
#include <vector>

namespace offcenter {
namespace common {
namespace appmanager {

/**
 *
 */
class AppManagerOptions
{
public:
	explicit AppManagerOptions():
		m_processFile()
	{}

	virtual ~AppManagerOptions() {}

	std::string processFile() { return m_processFile; }

	friend class AppManagerProgramOptions;

private:
	std::string m_processFile;

};

} /* namespace appmanager */
} /* namespace common */
} /* namespace offcenter */

#endif /* OFFCENTER_COMMON_APPMANAGER_APPMANAGEROPTIONS__H_ */
