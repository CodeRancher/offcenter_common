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
 * @file   test_basic_app.cpp
 * @author Scott Brauer
 * @date   04-27-2019
 */

#include <string>

#include <gtest/gtest.h>
#include <gmock/gmock.h>
using ::testing::HasSubstr;

#include "BasicAppTest.hpp"
#include "offcenter/common/SimulatedCommandLine.hpp"

TEST_F (BasicAppFixture, EmptyProgramOptions)
{
	offcenter::common::SimulatedCommandLine commandLine("BasicAppTest");

	//m_basicAppTest.processCommandLine(commandLine.argc(), commandLine.argv());
	m_basicAppTest.start(commandLine.argc(), commandLine.argv());

//	EXPECT_EQ(m_basicAppTest.m_onExecuteCalled, true);
//	EXPECT_EQ(m_basicAppTest.config()->help(), false);

	//EXPECT_EQ(m_basicApp.basicConfig().help(), false);

/*
	std::string group1Arg2 = "group1Arg2_value";
	std::string group2Arg2 = "group2Arg2_value";
	offcenter::common::SimulatedCommandLine commandLine("DoubleProgramOptionSet", {"--group1Arg1", "--group1Arg2", group1Arg2, "--group2Arg1", "--group2Arg2", group2Arg2});

	offcenter::common::program_options::ProgramOptionsManager optManager;
	DoubleOptionGroupConfig config;
	optManager.add<DoubleOptionGroup1>(config);
	optManager.add<DoubleOptionGroup2>(config);
	optManager.processCommandLine(commandLine.argc(), commandLine.argv());

	EXPECT_EQ(config.group1Arg1(), true);
	EXPECT_EQ(config.group1Arg2(), group1Arg2);
	EXPECT_EQ(config.group2Arg1(), true);
	EXPECT_EQ(config.group2Arg2(), group2Arg2);
	*/
}

TEST_F (BasicAppFixture, HelpProgramOptions)
{
	offcenter::common::SimulatedCommandLine commandLine("BasicAppTest", {"--help"});

	//m_basicAppTest.processCommandLine(commandLine.argc(), commandLine.argv());
	m_basicAppTest.start(commandLine.argc(), commandLine.argv());

//	EXPECT_EQ(m_basicAppTest.m_onExecuteCalled, true);
//	EXPECT_EQ(m_basicAppTest.config()->help(), true);
//	EXPECT_EQ(m_basicAppTest.m_onHelpCalled, true);
//	EXPECT_TRUE(m_basicAppTest.m_helpText.find("--help") != std::string::npos);

	//EXPECT_EQ(m_basicApp.basicConfig().help(), false);

/*
	std::string group1Arg2 = "group1Arg2_value";
	std::string group2Arg2 = "group2Arg2_value";
	offcenter::common::SimulatedCommandLine commandLine("DoubleProgramOptionSet", {"--group1Arg1", "--group1Arg2", group1Arg2, "--group2Arg1", "--group2Arg2", group2Arg2});

	offcenter::common::program_options::ProgramOptionsManager optManager;
	DoubleOptionGroupConfig config;
	optManager.add<DoubleOptionGroup1>(config);
	optManager.add<DoubleOptionGroup2>(config);
	optManager.processCommandLine(commandLine.argc(), commandLine.argv());

	EXPECT_EQ(config.group1Arg1(), true);
	EXPECT_EQ(config.group1Arg2(), group1Arg2);
	EXPECT_EQ(config.group2Arg1(), true);
	EXPECT_EQ(config.group2Arg2(), group2Arg2);
	*/
}

TEST_F (BasicAppFixture, HelpVersionProgramOptions)
{
	offcenter::common::SimulatedCommandLine commandLine("BasicAppTest", {"--help", "--version"});

	//m_basicAppTest.processCommandLine(commandLine.argc(), commandLine.argv());
	m_basicAppTest.start(commandLine.argc(), commandLine.argv());

//	EXPECT_EQ(m_basicAppTest.m_onExecuteCalled, true);
//	EXPECT_EQ(m_basicAppTest.config()->help(), true);
//	EXPECT_EQ(m_basicAppTest.m_onHelpCalled, true);
//	EXPECT_TRUE(m_basicAppTest.m_helpText.find("--help") != std::string::npos);

	//EXPECT_EQ(m_basicApp.basicConfig().help(), false);

/*
	std::string group1Arg2 = "group1Arg2_value";
	std::string group2Arg2 = "group2Arg2_value";
	offcenter::common::SimulatedCommandLine commandLine("DoubleProgramOptionSet", {"--group1Arg1", "--group1Arg2", group1Arg2, "--group2Arg1", "--group2Arg2", group2Arg2});

	offcenter::common::program_options::ProgramOptionsManager optManager;
	DoubleOptionGroupConfig config;
	optManager.add<DoubleOptionGroup1>(config);
	optManager.add<DoubleOptionGroup2>(config);
	optManager.processCommandLine(commandLine.argc(), commandLine.argv());

	EXPECT_EQ(config.group1Arg1(), true);
	EXPECT_EQ(config.group1Arg2(), group1Arg2);
	EXPECT_EQ(config.group2Arg1(), true);
	EXPECT_EQ(config.group2Arg2(), group2Arg2);
	*/
}
