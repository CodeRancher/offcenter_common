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
 * @file   test_positional_option_group.cpp
 * @author Scott Brauer
 * @date   01-20-2022
 */

#include <string>

#include <gtest/gtest.h>

#include "offcenter/common/program_options/ProgramOptionsManager.hpp"
#include "offcenter/common/program_options/ProgramOptionsGroup.hpp"
#include "offcenter/common/SimulatedCommandLine.hpp"

/*
 * Configuration options for handling one positional option.
 *
 * Note: Notice that there is nothing stating that these options are positional. Defining
 * 		 that an option is positional is handled with the add_options and add of the related
 * 		 PostionalOptionOne class.
 */
class PositionalOptionOneConfig {
	public:
		PositionalOptionOneConfig():
			m_position1() {}
		virtual ~PositionalOptionOneConfig() = default;

		std::string position1() { return m_position1; }

		friend class PositionalOptionOne;

	private:
		std::string m_position1;
};

/*
 * Defines how the command line is parsed into the PositionalOptionOneConfig class.
 */
class PositionalOptionOne:
		public offcenter::common::program_options::ProgramOptionsGroup<PositionalOptionOneConfig> {
public:
	explicit PositionalOptionOne():
		ProgramOptionsGroup("PositionalOption")
	{
		optionsDescription().add_options()
				("position1", po::value<std::string>(&optionConfig().m_position1)->default_value(""), "Positional 1")
				;

		positionalOptionsDescription().add("position1", 1);
	}
	virtual ~PositionalOptionOne() = default;
};

/**
 * @test Verify that positional parameters of the \c ProgramOptionsManager will
 * 		 correctly handle one positional parameter.
 */
TEST (PositionalOptionGroupTest, SinglePositionalOption)
{
	std::string position1{"PositionalOption"};
	offcenter::common::SimulatedCommandLine commandLine("PositionalOptionSet", {
			position1});

	offcenter::common::program_options::ProgramOptionsManager optManager;
	PositionalOptionOne::ConfigPtr config = optManager.add<PositionalOptionOne>();

	optManager.processCommandLine(commandLine.argc(), commandLine.argv());

	EXPECT_EQ(config->position1(), position1);
}

/*
 * Configuration options for handling two positional option.
 *
 * Note: Notice that there is nothing stating that these options are positional. Defining
 * 		 that an option is positional is handled with the add_options and add of the related
 * 		 PositionalOptionTwo class.
 */
class PositionalOptionTwoConfig {
	public:
		PositionalOptionTwoConfig():
			m_position1(),
			m_position2() {}
		virtual ~PositionalOptionTwoConfig() = default;

		std::string position1() { return m_position1; }
		std::string position2() { return m_position2; }

		friend class PositionalOptionTwo;

	private:
	std::string m_position1;
	std::string m_position2;
};

/*
 * Defines how the command line is parsed into the PositionalOptionTwoConfig class.
 */
class PositionalOptionTwo:
		public offcenter::common::program_options::ProgramOptionsGroup<PositionalOptionTwoConfig> {
public:
	explicit PositionalOptionTwo():
		ProgramOptionsGroup("PositionalOption")
	{
		optionsDescription().add_options()
				("position1", po::value<std::string>(&optionConfig().m_position1)->default_value(""), "Positional 1")
				("position2", po::value<std::string>(&optionConfig().m_position2)->default_value(""), "Positional 2")
				;

		positionalOptionsDescription().add("position1", 1);
		positionalOptionsDescription().add("position2", 1);
	}
	virtual ~PositionalOptionTwo() = default;
};

/**
 * @test Verify that positional parameters of the \c ProgramOptionsManager will
 * 		 correctly handle two positional parameters.
 */
TEST (PositionalOptionGroupTest, DoublePositionalOption)
{
	std::string position1{"PositionalOption1"};
	std::string position2{"PositionalOption2"};
	offcenter::common::SimulatedCommandLine commandLine("PositionalOptionSet", {
			position1,
			position2
	});

	offcenter::common::program_options::ProgramOptionsManager optManager;
	PositionalOptionTwo::ConfigPtr config = optManager.add<PositionalOptionTwo>();

	optManager.processCommandLine(commandLine.argc(), commandLine.argv());

	EXPECT_EQ(config->position1(), position1);
	EXPECT_EQ(config->position2(), position2);
}

/**
 * @test Verify that positional parameters of the \c ProgramOptionsManager will
 * 		 correctly handle the error condition of multiple \c ProgramOptionsGroup
 * 		 containing positional parameters. Only one \c ProgramOptionsGroup can have
 * 		 a positional option.
 */
TEST (PositionalOptionGroupTest, MultiplePositionalOptionError)
{
	std::string position1{"PositionalOption1"};
	std::string position2{"PositionalOption2"};
	offcenter::common::SimulatedCommandLine commandLine("PositionalOptionSet", {
			position1,
			position2
	});

	offcenter::common::program_options::ProgramOptionsManager optManager;
	PositionalOptionOne::ConfigPtr config1 = optManager.add<PositionalOptionOne>();
	PositionalOptionTwo::ConfigPtr config2 = optManager.add<PositionalOptionTwo>();

	EXPECT_THROW(
			optManager.processCommandLine(commandLine.argc(), commandLine.argv()),
			offcenter::common::RuntimeException
	);
}
