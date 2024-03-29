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
 * @file   test_double_program_option_group.cpp
 * @author Scott Brauer
 * @date   04-04-2019
 */

#include <string>

#include <gtest/gtest.h>

#include "offcenter/common/program_options/ProgramOptionsManager.hpp"
#include "offcenter/common/program_options/ProgramOptionsGroup.hpp"
#include "offcenter/common/SimulatedCommandLine.hpp"

class DoubleOptionOneConfig {
	private:
		bool m_d1arg1;
		int m_d1arg2;
		std::string m_d1arg3;

	public:
		DoubleOptionOneConfig():
			m_d1arg1(false),
			m_d1arg2(-1),
			m_d1arg3("") {}
		virtual ~DoubleOptionOneConfig() = default;

		bool d1arg1() { return m_d1arg1; }
		int d1arg2() { return m_d1arg2; }
		std::string d1arg3() { return m_d1arg3; }

		friend class DoubleOptionOne;
};

class DoubleOptionOne: public offcenter::common::program_options::ProgramOptionsGroup<DoubleOptionOneConfig> {
public:
	explicit DoubleOptionOne():
		ProgramOptionsGroup("DoubleOption")
	{
		optionsDescription().add_options()
				("d1arg1", po::bool_switch(&optionConfig().m_d1arg1)->default_value(false), "Simple argument 1")
				("d1arg2", po::value<int>(&optionConfig().m_d1arg2)->default_value(0), "Simple argument 2")
				("d1arg3", po::value<std::string>(&optionConfig().m_d1arg3)->default_value("Not Set"), "Simple argument 3")
				;
	}
	virtual ~DoubleOptionOne() = default;
};

class DoubleOptionTwoConfig {
	private:
		bool m_d2arg1;
		int m_d2arg2;
		std::string m_d2arg3;

	public:
		DoubleOptionTwoConfig():
			m_d2arg1(false),
			m_d2arg2(-1),
			m_d2arg3("") {}
		virtual ~DoubleOptionTwoConfig() = default;

		bool d2arg1() { return m_d2arg1; }
		int d2arg2() { return m_d2arg2; }
		std::string d2arg3() { return m_d2arg3; }

		friend class DoubleOptionTwo;
};

class DoubleOptionTwo: public offcenter::common::program_options::ProgramOptionsGroup<DoubleOptionTwoConfig> {
public:
	explicit DoubleOptionTwo():
		ProgramOptionsGroup("DoubleOption")
	{
		optionsDescription().add_options()
				("d2arg1", po::bool_switch(&optionConfig().m_d2arg1)->default_value(false), "Simple argument 1")
				("d2arg2", po::value<int>(&optionConfig().m_d2arg2)->default_value(0), "Simple argument 2")
				("d2arg3", po::value<std::string>(&optionConfig().m_d2arg3)->default_value("Not Set"), "Simple argument 3")
				;
	}
	virtual ~DoubleOptionTwo() = default;
};

TEST (DoubleProgramOptionGroupTest, DoubleOptionGroupSet)
{
	std::string group1Arg2 = "1001";
	std::string group1Arg3 = "group1Arg3_value";
	std::string group2Arg2 = "2002";
	std::string group2Arg3 = "group2Arg3_value";
	offcenter::common::SimulatedCommandLine commandLine("DoubleProgramOptionSet", {
			"--d1arg1",
			"--d1arg2", group1Arg2,
			"--d1arg3", group1Arg3,
			"--d2arg1",
			"--d2arg2", group2Arg2,
			"--d2arg3", group2Arg3});

	offcenter::common::program_options::ProgramOptionsManager optManager;
	DoubleOptionOne::ConfigPtr oneConfig = optManager.add<DoubleOptionOne>();
	DoubleOptionTwo::ConfigPtr twoConfig = optManager.add<DoubleOptionTwo>();

	EXPECT_EQ(oneConfig->d1arg1(), false);
	EXPECT_EQ(oneConfig->d1arg2(), -1);
	EXPECT_EQ(oneConfig->d1arg3(), "");
	EXPECT_EQ(twoConfig->d2arg1(), false);
	EXPECT_EQ(twoConfig->d2arg2(), -1);
	EXPECT_EQ(twoConfig->d2arg3(), "");

	optManager.processCommandLine(commandLine.argc(), commandLine.argv());

	EXPECT_EQ(oneConfig->d1arg1(), true);
	EXPECT_EQ(oneConfig->d1arg2(), std::stoi(group1Arg2));
	EXPECT_EQ(oneConfig->d1arg3(), group1Arg3);
	EXPECT_EQ(twoConfig->d2arg1(), true);
	EXPECT_EQ(twoConfig->d2arg2(), std::stoi(group2Arg2));
	EXPECT_EQ(twoConfig->d2arg3(), group2Arg3);
}

TEST (DoubleProgramOptionGroupTest, EmptyDoubleOptionGroupSet)
{
	offcenter::common::SimulatedCommandLine commandLine("DoubleProgramOptionSet");

	offcenter::common::program_options::ProgramOptionsManager optManager;
	DoubleOptionOne::ConfigPtr oneConfig = optManager.add<DoubleOptionOne>();
	DoubleOptionTwo::ConfigPtr twoConfig = optManager.add<DoubleOptionTwo>();

	optManager.processCommandLine(commandLine.argc(), commandLine.argv());

	EXPECT_EQ(oneConfig->d1arg1(), false);
	EXPECT_EQ(oneConfig->d1arg2(), 0);
	EXPECT_EQ(oneConfig->d1arg3(), "Not Set");
	EXPECT_EQ(twoConfig->d2arg1(), false);
	EXPECT_EQ(twoConfig->d2arg2(), 0);
	EXPECT_EQ(twoConfig->d2arg3(), "Not Set");
}
