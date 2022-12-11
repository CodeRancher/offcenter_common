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
 * @file   AppManagerApp.hpp
 * @author Scott Brauer
 * @date   01-23-2022
 */

#ifndef OffcenterCommon_APPMANAGER_APPMANAGERAPP__H_
#define OffcenterCommon_APPMANAGER_APPMANAGERAPP__H_

#include "offcenter/common/framework/application/IApp.hpp"

#include "offcenter/common/app_manager/AppManagerProgramOptions.hpp"

namespace offcenter {
namespace common {
namespace appmanager {

/**
 *
 */
class AppManagerApp
		: public offcenter::common::framework::application::IApp {
public:
	explicit AppManagerApp();
	virtual ~AppManagerApp();

	void onInitProgramOptions(program_options::ProgramOptionsManager& optionsManager) override;
	void onSetUp() override;
	void onExecute() override;
	void onTearDown() override;
	void onHelp(const std::string& help) override;
	void onVersion() override;

protected:
	offcenter::common::appmanager::AppManagerProgramOptions::ConfigPtr m_appManagerOptions;
};

} /* namespace appmanager */
} /* namespace common */
} /* namespace offcenter */

#endif /* OffcenterCommon_APPMANAGER_APPMANAGERAPP__H_ */
