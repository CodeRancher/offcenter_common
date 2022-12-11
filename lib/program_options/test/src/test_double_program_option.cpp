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
 * @file   test_double_program_option.cpp
 * @author Scott Brauer
 * @date   04-04-2019
 */

#include <vector>

#include <gtest/gtest.h>

#include "offcenter/common/program_options/ProgramOptionsManager.hpp"
#include "offcenter/common/program_options/ProgramOptionsGroup.hpp"
#include "offcenter/common/SimulatedCommandLine.hpp"

class IDoubleOptionConfigGet {
public:
	virtual ~IDoubleOptionConfigGet() = default;
	virtual std::string arg() = 0;
};

class IDoubleOptionConfigSet {
public:
	virtual ~IDoubleOptionConfigSet() = default;
	virtual std::string* arg_ptr() = 0;
};

class DoubleOptionConfig: public IDoubleOptionConfigGet, public IDoubleOptionConfigSet {
	private:
		std::string m_arg;

	public:
		DoubleOptionConfig():
			m_arg("............") {}
		virtual ~DoubleOptionConfig() = default;

		// IDoubleOptionConfigGet
		std::string arg() override { return m_arg; }

		// IDoubleOptionConfigSet
		std::string* arg_ptr() override { return &m_arg; }


};

class DoubleOption: public offcenter::common::program_options::ProgramOptionsGroup<DoubleOptionConfig> {
public:
	explicit DoubleOption():
		ProgramOptionsGroup("DoubleOption")
	{
		optionsDescription().add_options()
				("arg", po::value<std::string>(&optionConfigPtr().m_arg)->default_value("XXXXXXXXX"), "Double argument")
				;
	}
	virtual ~DoubleOption() {}

	void processOptions(po::variables_map& vm) override {

	}

	void validateOptions(po::variables_map& vm) override {

	}
};

TEST (DoubleProgramOptionTest, DoubleProgramOptionSet)
{
	std::string value = "value";
	offcenter::common::SimulatedCommandLine commandLine("DoubleProgramOptionSet", {"--arg", value});

	offcenter::common::program_options::ProgramOptionsManager optManager;
	DoubleOptionConfig config;
	optManager.add<DoubleOption>(config);
	optManager.processCommandLine(commandLine.argc(), commandLine.argv());

	EXPECT_EQ(config.arg(), value);
}

TEST (DoubleProgramOptionTest, DoubleProgramOptionNotSet)
{
	offcenter::common::SimulatedCommandLine commandLine("DoubleProgramOptionNotSet");

	offcenter::common::program_options::ProgramOptionsManager optManager;
	DoubleOptionConfig config;
	optManager.add<DoubleOption>(config);
	optManager.processCommandLine(commandLine.argc(), commandLine.argv());

	EXPECT_EQ(config.arg(), "XXXXXXXXX");
}

//*****************************************************************************
//*****************************************************************************
//*****************************************************************************
/*
class IDoubleOptionConfigGet {
	virtual ~IDoubleOptionConfigGet() = 0;
	virtual std::string value() = 0;
};

class IDoubleOptionConfigSet {

};

class DoubleOptionConfig: public IDoubleOptionConfigGet, public IDoubleOptionConfigSet {
	private:
		std::string m_value;

	public:
		DoubleOptionConfig():
			m_value("") {}
		virtual ~DoubleOptionConfig() = default;
		bool value() override { return m_value; }

};

class DoubleOption {

};

using OptManager = offcenter::common::program_options::ProgramOptionsManager<DoubleOptionConfig>;

TEST (DoubleProgramOptionTest, DoubleProgramOptionSet)
{
	std::string second = "second";
	offcenter::common::SimulatedCommandLine commandLine("DoubleProgramOptionSet", {"--arg", "--value", second});

	DoubleOptionConfig config;
	OptManager optManager(config);
	optManager.add<DoubleOption>();
	optManager.add<DoubleOption>();
	optManager.processCommandLine(commandLine.argc(), commandLine.argv());

	EXPECT_EQ(config.arg(), true);
	EXPECT_EQ(config.value(), second);
}

TEST (DoubleProgramOptionTest, DoubleProgramOptionNotSet)
{
	offcenter::common::SimulatedCommandLine commandLine("DoubleProgramOptionNotSet");

	DoubleOptionConfig config;
	OptManager optManager(config);
	optManager.add<DoubleOption>();
	optManager.add<DoubleOption>();
	optManager.processCommandLine(commandLine.argc(), commandLine.argv());

	EXPECT_EQ(config.arg(), false);
	EXPECT_EQ(config.arg(), "");
}
*/
