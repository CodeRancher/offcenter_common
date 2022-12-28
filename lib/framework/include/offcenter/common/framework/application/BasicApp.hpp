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
 * @file   BasicApp.hpp
 * @author Scott Brauer
 * @date   04-27-2019
 */

#ifndef OffcenterCommonFramework_APPLICATION_BASICAPP_HPP_
#define OffcenterCommonFramework_APPLICATION_BASICAPP_HPP_

///#include "offcenter/common/framework/application/BasicAppFoundation.hpp"
///#include "offcenter/common/program_options/ProgramOptionsManager.hpp"
///#include "offcenter/common/framework/application/BasicAppConfig.hpp"
///#include "offcenter/common/framework/program_options/BasicAppProgramOptions.hpp"

//#include "offcenter/common/framework/application/IBasicApp.hpp"
///
namespace offcenter {
namespace common {
namespace framework {
namespace application {

/*
template <class IBASICAPP>
class BasicApp : public BasicAppFoundation
{
public:
	explicit BasicApp():
		BasicAppFoundation(),
		m_app()
	{}
	virtual ~BasicApp() = default;

protected:
	// Children
	void internalOnInitProgramOptions(program_options::ProgramOptionsManager& optionsManager) {
		m_app.onInitProgramOptions(optionsManager);
	}
	void internalOnSetUp() override { m_app.onSetUp(); }
	void internalOnExecute() override { m_app.onExecute(); }
	void internalOnTearDown() override { m_app.onTearDown(); }
	void internalOnHelp(const std::string& help) override { m_app.onHelp(help); }
	void internalOnVersion() override { m_app.onVersion(); }

private:
	IBASICAPP m_app;

};
*/

} /* namespace application */
} /* namespace framework */
} /* namespace common */
} /* namespace offcenter */

#endif /* OffcenterCommonFramework_APPLICATION_BASICAPP_HPP_ */
