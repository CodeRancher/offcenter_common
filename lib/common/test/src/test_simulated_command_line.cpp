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
 * @file   test_simulated_command_line.cpp
 * @author Scott Brauer
 * @date   04-10-2019
 */

#include <gtest/gtest.h>

#include "offcenter/common/SimulatedCommandLine.hpp"

TEST(SimulatedCommandLine, NoOptions)
{
	std::string progName = "prog_name.exe";

	offcenter::common::SimulatedCommandLine simCL(progName);

	EXPECT_EQ(simCL.argc(), 1);
	EXPECT_EQ(std::string(simCL.argv()[0]), progName);
	EXPECT_EQ(simCL.argv()[1], nullptr);
}

TEST(SimulatedCommandLine, SingleOption)
{
	std::string progName = "prog_name.exe";
	std::string arg1 = "--arg_1";

	offcenter::common::SimulatedCommandLine simCL(progName);
	simCL.add(arg1);

	EXPECT_EQ(simCL.argc(), 2);
	EXPECT_EQ(std::string(simCL.argv()[0]), progName);
	EXPECT_EQ(std::string(simCL.argv()[1]), arg1);
	EXPECT_EQ(simCL.argv()[2], nullptr);
}

TEST(SimulatedCommandLine, OptionPair)
{
	std::string progName = "prog_name.exe";
	std::string arg1 = "--arg_1";
	std::string val1 = "val_1";

	offcenter::common::SimulatedCommandLine simCL(progName);
	simCL.add(arg1, val1);

	EXPECT_EQ(simCL.argc(), 3);
	EXPECT_EQ(std::string(simCL.argv()[0]), progName);
	EXPECT_EQ(std::string(simCL.argv()[1]), arg1);
	EXPECT_EQ(std::string(simCL.argv()[2]), val1);
	EXPECT_EQ(simCL.argv()[3], nullptr);
}

TEST(SimulatedCommandLine, OptionVector)
{
	std::string progName = "prog_name.exe";
	std::string arg1 = "--arg_1";
	std::string val1 = "val_1";

	offcenter::common::SimulatedCommandLine simCL(progName, {arg1, val1});

	EXPECT_EQ(simCL.argc(), 3);
	EXPECT_EQ(std::string(simCL.argv()[0]), progName);
	EXPECT_EQ(std::string(simCL.argv()[1]), arg1);
	EXPECT_EQ(std::string(simCL.argv()[2]), val1);
	EXPECT_EQ(simCL.argv()[3], nullptr);
}

TEST(SimulatedCommandLine, OptionVectorAdd)
{
	std::string progName = "prog_name.exe";
	std::string arg1 = "--arg_1";
	std::string val1 = "val_1";

	offcenter::common::SimulatedCommandLine simCL(progName);
	simCL.add({arg1, val1});

	EXPECT_EQ(simCL.argc(), 3);
	EXPECT_EQ(std::string(simCL.argv()[0]), progName);
	EXPECT_EQ(std::string(simCL.argv()[1]), arg1);
	EXPECT_EQ(std::string(simCL.argv()[2]), val1);
	EXPECT_EQ(simCL.argv()[3], nullptr);
}



