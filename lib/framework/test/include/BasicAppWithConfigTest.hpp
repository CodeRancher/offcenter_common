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
 * @file   BasicAppWithConfigTest.hpp
 * @author Scott Brauer
 * @date   04-27-2019
 */

#ifndef BASICAPPWITHCONFIGTEST_HPP_
#define BASICAPPWITHCONFIGTEST_HPP_

#include <functional>

#include <boost/bind/bind.hpp>

#include <gtest/gtest.h>

#include "offcenter/common/framework/application/IApp.hpp"
#include "offcenter/common/framework/application/AppManager.hpp"
#include "offcenter/common/framework/application/ManagedAppConfig.hpp"
#include "offcenter/common/program_options/ProgramOptionsGroup.hpp"
using namespace offcenter::common;

//*****************************************************************************
class BasicAppWithConfigConfig
{
private:
	int m_intVal;
	std::string m_stringVal;
	std::string m_methodStringVal;

public:
	BasicAppWithConfigConfig():
		m_intVal(0),
		m_stringVal("")
	{}

	virtual ~BasicAppWithConfigConfig() = default;

	int intVal() const { return m_intVal; }
	std::string stringVal() const { return m_stringVal; }
	std::string methodStringVal() const { return m_methodStringVal; }

	friend class BasicAppConfigFileOptions;

};

//*****************************************************************************
class BasicAppConfigFileOptions:
		public program_options::ProgramOptionsGroup<BasicAppWithConfigConfig>
{
public:
	BasicAppConfigFileOptions():
		ProgramOptionsGroup("Config File Options")
	{
		optionsDescription().add_options()
				("int,i", po::value<int>(&optionConfig().m_intVal)->default_value(0), "Integer")
				("string,s", po::value<std::string>(&optionConfig().m_stringVal)->default_value(""), "String")
				("method_string,m", po::value<std::string>()->default_value("Not Defined")
						->notifier(boost::bind(&BasicAppConfigFileOptions::setMethodString, this, boost::placeholders::_1)), "Method String")
				;
	}

	virtual ~BasicAppConfigFileOptions() = default;
private:
	void setMethodString(const std::string& value) { optionConfig().m_methodStringVal = value; }
};

//*****************************************************************************
class BasicAppWithConfigTest: public framework::application::IApp {
public:
	bool m_onExecuteCalled;
	bool m_onVersionCalled;
	bool m_onHelpCalled;
	std::string m_helpText;
	BasicAppConfigFileOptions::ConfigPtr m_configFileOption;


	BasicAppWithConfigTest():
		IApp(),
		m_onExecuteCalled(false),
		m_onVersionCalled(false),
		m_onHelpCalled(false),
		m_helpText("")
	{
	}
	const BasicAppConfigFileOptions::ConfigPtr& config() const { return m_configFileOption; }

	void onInitProgramOptions(program_options::ProgramOptionsManager& optionsManager) {
		m_configFileOption = optionsManager.add<BasicAppConfigFileOptions>();
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
class BasicAppWithConfigFixture : public ::testing::Test {
public:
	explicit BasicAppWithConfigFixture():
		m_basicAppTest() {}

	virtual ~BasicAppWithConfigFixture() = default;

protected:
	void SetUp() override {}

	// void TearDown() override {}

	using App = framework::application::AppManager<BasicAppWithConfigTest>;
	App m_basicAppTest;
};

#endif /* BASICAPPWITHCONFIGTEST_HPP_ */
