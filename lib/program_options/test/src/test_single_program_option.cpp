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
 * @file   test_single_program_option.hpp
 * @author Scott Brauer
 * @date   04-04-2019
 */

#include <vector>

#include <gtest/gtest.h>

#include "offcenter/common/program_options/ProgramOptionsManager.hpp"
#include "offcenter/common/program_options/ProgramOptionsGroup.hpp"
#include "offcenter/common/SimulatedCommandLine.hpp"

class ISingleOptionConfigGet {
public:
	virtual ~ISingleOptionConfigGet() = default;
	virtual bool arg() = 0;
};

class ISingleOptionConfigSet {
public:
	virtual ~ISingleOptionConfigSet() = default;
	virtual bool* arg_ptr() = 0;
};

class SingleOptionConfig: public ISingleOptionConfigGet, public ISingleOptionConfigSet {
	private:
		bool m_arg;

	public:
		SingleOptionConfig():
			m_arg(false) {}
		virtual ~SingleOptionConfig() = default;

		// ISingleOptionConfigGet
		bool arg() override { return m_arg; }

		// ISingleOptionConfigSet
		bool* arg_ptr() override { return &m_arg; }

};

class SingleOption: public offcenter::common::program_options::ProgramOptionsGroup<SingleOptionConfig> {
public:
	explicit SingleOption():
		ProgramOptionsGroup("SingleOption")
	{
		optionsDescription().add_options()
				("arg", po::bool_switch(optionConfig().arg_ptr())->default_value(false), "Simple argument")
				;
	}
	virtual ~SingleOption() {}

	void processOptions(po::variables_map& vm) override {
		//std::cout << vm.count("arg") << "-" << (vm["arg"].as<bool>() ? "true" : "false") << std::endl;
		//std::cout << "ActVal: " << (optionConfig().arg() ? "true" : "false") << std::endl;
	}

	void validateOptions(po::variables_map& vm) override {

	}
};

TEST (SingleProgramOptionTest, SingleProgramOptionSet)
{
	offcenter::common::SimulatedCommandLine commandLine("SingleProgramOptionSet", {"--arg"});

	offcenter::common::program_options::ProgramOptionsManager optManager;
	SingleOptionConfig config;
	//std::cout << "ActVal1: " << (config.arg() ? "true" : "false") << std::endl;
	optManager.add<SingleOption>();
	optManager.processCommandLine(commandLine.argc(), commandLine.argv());
	//std::cout << "ActVal2: " << (config.arg() ? "true" : "false") << std::endl;

	//std::cout << optManager.help() << std::endl;

	EXPECT_EQ(config.arg(), true);
}

TEST (SingleProgramOptionTest, SingleProgramOptionNotSet)
{
	offcenter::common::SimulatedCommandLine commandLine("SingleProgramOptionNotSet");

	offcenter::common::program_options::ProgramOptionsManager optManager;
	SingleOptionConfig config;
	//std::cout << "ActVal1: " << (config.arg() ? "true" : "false") << std::endl;
	optManager.add<SingleOption>();
	optManager.processCommandLine(commandLine.argc(), commandLine.argv());
	//std::cout << "ActVal2: " << (config.arg() ? "true" : "false") << std::endl;

	EXPECT_EQ(config.arg(), false);
}
