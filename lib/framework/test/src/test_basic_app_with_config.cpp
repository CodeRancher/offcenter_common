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
 * @file   test_basic_app_with_config.cpp
 * @author Scott Brauer
 * @date   04-27-2019
 */

#include <string>

#include <gtest/gtest.h>
#include <gmock/gmock.h>
using ::testing::HasSubstr;

#include "BasicAppWithConfigTest.hpp"
#include "offcenter/common/SimulatedCommandLine.hpp"

#define mkstr(s) #s

const std::string g_configFile_Empty(CONFIGFILE_EMPTY);

TEST_F (BasicAppWithConfigFixture, EmptyConfigFile)
{
	offcenter::common::SimulatedCommandLine commandLine("BasicAppWithConfigFixture", {"--config", g_configFile_Empty});

	//m_basicAppTest.processCommandLine(commandLine.argc(), commandLine.argv());
	m_basicAppTest.start(commandLine.argc(), commandLine.argv());

//	EXPECT_EQ(m_basicAppTest.config()->intVal(), 0);
//	EXPECT_EQ(m_basicAppTest.config()->stringVal(), "");
//	EXPECT_EQ(m_basicAppTest.config()->methodStringVal(), "Not Defined");
}

const std::string g_configFile_Basic(CONFIGFILE_BASIC);

TEST_F (BasicAppWithConfigFixture, HelpProgramOptions)
{
	offcenter::common::SimulatedCommandLine commandLine("BasicAppWithConfigFixture", {"--config", g_configFile_Basic});

	//m_basicAppTest.processCommandLine(commandLine.argc(), commandLine.argv());
	m_basicAppTest.start(commandLine.argc(), commandLine.argv());

//	EXPECT_EQ(m_basicAppTest.config()->intVal(), 100);
//	EXPECT_EQ(m_basicAppTest.config()->stringVal(), "This is it");
//	EXPECT_EQ(m_basicAppTest.config()->methodStringVal(), "Method string value");
}

TEST_F (BasicAppWithConfigFixture, InvalidConfigFileName)
{
	offcenter::common::SimulatedCommandLine commandLine("BasicAppWithConfigFixture", {"--config", "I_don't_exist"});

	//ASSERT_THROW(
			//m_basicAppTest.processCommandLine(commandLine.argc(), commandLine.argv()),
	//		offcenter::common::FileException
	//);
	m_basicAppTest.start(commandLine.argc(), commandLine.argv());

}
