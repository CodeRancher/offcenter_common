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
 * @file   AppWaitforSigintApp.hpp
 * @author Scott Brauer
 * @date   01-25-2022
 */

#ifndef OffcenterCommon_WAITFORSIGINT_WAITFORSIGINTAPP__H_
#define OffcenterCommon_WAITFORSIGINT_WAITFORSIGINTAPP__H_

#include "offcenter/common/framework/application/IApp.hpp"
#include "offcenter/common/threading/RunningThread.hpp"

namespace offcenter {
namespace common {
namespace waitforsigint {

class Counter:
		public offcenter::common::threading::RunningThread
{
public:
	Counter(int millisecondsSleep = 100);
	virtual ~Counter() = default;

protected:
	void task() override;
	void stopped() override;

private:
	int m_counter;
	int m_millisecondsSleep;
};

/**
 *
 */
class WaitforSigintApp
		: public offcenter::common::framework::application::IApp {
public:
	explicit WaitforSigintApp();
	virtual ~WaitforSigintApp();

	void onInitProgramOptions(program_options::ProgramOptionsManager& optionsManager) override;
	void onSetUp() override;
	void onExecute() override;
	void onTearDown() override;
	void onHelp(const std::string& help) override;
	void onVersion() override;

private:
	Counter m_counter;

};

} /* namespace waitforsigint */
} /* namespace common */
} /* namespace offcenter */

#endif /* OffcenterCommon_WAITFORSIGINT_WAITFORSIGINTAPP__H_ */
