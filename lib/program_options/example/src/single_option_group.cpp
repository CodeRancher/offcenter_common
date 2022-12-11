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
 * @file   single_option_group.cpp
 * @author Scott Brauer
 * @date   03-19-2021
 */

#include <iostream>

#include "offcenter/common/program_options/ProgramOptionsManager.hpp"
#include "offcenter/common/program_options/ProgramOptionsGroup.hpp"
using namespace offcenter::common;

class SingleOptionConfig {
	private:
		bool m_arg1;
		int m_arg2;
		std::string m_arg3;

	public:
		SingleOptionConfig():
			m_arg1(false),
			m_arg2(-1),
			m_arg3("") {}
		virtual ~SingleOptionConfig() = default;

		bool arg1() { return m_arg1; }
		int arg2() { return m_arg2; }
		std::string arg3() { return m_arg3; }

		friend class SingleOption;
};

class SingleOption: public program_options::ProgramOptionsGroup<SingleOptionConfig> {
public:
	explicit SingleOption():
		ProgramOptionsGroup("SingleOption")
	{
		optionsDescription().add_options()
				("arg1", po::bool_switch(&optionConfig().m_arg1)->default_value(false), "Simple argument 1")
				("arg2", po::value<int>(&optionConfig().m_arg2)->default_value(0), "Simple argument 2")
				("arg3", po::value<std::string>(&optionConfig().m_arg3)->default_value("Not Set"), "Simple argument 3")
				;
	}
	virtual ~SingleOption() = default;
};


int main(int argc, char **argv)
{
	// Declare the Program Options Manager
	program_options::ProgramOptionsManager optManager;

	// Add a Program Options Group to be processed
	SingleOption::ConfigPtr singleOptionConfig = optManager.add<SingleOption>();
	std::cout << "Before: "
		 << "arg1 (" << (singleOptionConfig->arg1() ? "true" : "false") << ") "
		 << "arg2 (" << singleOptionConfig->arg2() << ") "
		 << "arg3 (" << singleOptionConfig->arg3() << ")" << std::endl;

	// Process the command line
	optManager.processCommandLine(argc, argv);
	std::cout << "After:  "
		 << "arg1 (" << (singleOptionConfig->arg1() ? "true" : "false") << ") "
		 << "arg2 (" << singleOptionConfig->arg2() << ") "
		 << "arg3 (" << singleOptionConfig->arg3() << ")" << std::endl;
}
