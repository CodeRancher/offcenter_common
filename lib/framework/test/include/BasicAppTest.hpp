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
 * @file   BasicAppTest.hpp
 * @author Scott Brauer
 * @date   04-27-2019
 */

#ifndef BASICAPPTEST_HPP_
#define BASICAPPTEST_HPP_

#include <gtest/gtest.h>

#include "offcenter/common/framework/application/IApp.hpp"
#include "offcenter/common/framework/application/AppManager.hpp"
#include "offcenter/common/framework/application/ManagedAppConfig.hpp"

//*****************************************************************************
class BasicAppTest: public offcenter::common::framework::application::IApp {
public:
	bool m_onExecuteCalled;
	bool m_onVersionCalled;
	bool m_onHelpCalled;
	std::string m_helpText;


	BasicAppTest():
		IApp(),
		m_onExecuteCalled(false),
		m_onVersionCalled(false),
		m_onHelpCalled(false),
		m_helpText("")
	{}

	void onInitProgramOptions(offcenter::common::program_options::ProgramOptionsManager& optionsManager) {
	}

	void onSetUp() override {
	}

	void onExecute() override {
		m_onExecuteCalled = true;
	}

	void onTearDown() override {
	}

	void onHelp(const std::string& help) override {
		m_onHelpCalled = true;
		m_helpText = help;
	}

	void onVersion() override {
		m_onVersionCalled = true;
	}
};

//*****************************************************************************
class BasicAppFixture : public ::testing::Test {
public:
	virtual ~BasicAppFixture() {}

protected:
	void SetUp() override {
	}

	// void TearDown() override {}

	using App = offcenter::common::framework::application::AppManager<BasicAppTest>;
	App m_basicAppTest;
};

#endif /* BASICAPPTEST_HPP_ */
