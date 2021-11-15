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
 * @file   double_option_group.cpp
 * @author Scott Brauer
 * @date   03-20-2021
 */

#include <iostream>

#include "offcenter/common/program_options/ProgramOptionsManager.hpp"
#include "offcenter/common/program_options/ProgramOptionsGroup.hpp"
using namespace offcenter::common;

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

class DoubleOptionOne: public program_options::ProgramOptionsGroup<DoubleOptionOneConfig> {
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

class DoubleOptionTwo: public program_options::ProgramOptionsGroup<DoubleOptionTwoConfig> {
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

int main(int argc, char **argv)
{
	// Declare the Program Options Manager
	program_options::ProgramOptionsManager optManager;

	// Add Program Options Groups to be processed
	DoubleOptionOne::ConfigPtr doubleOptionOneConfig = optManager.add<DoubleOptionOne>();
	DoubleOptionTwo::ConfigPtr doubleOptionTwoConfig = optManager.add<DoubleOptionTwo>();
	std::cout << "Before: " << std::endl
		 << "\td1arg1 (" << (doubleOptionOneConfig->d1arg1() ? "true" : "false") << ") "
		 << "d1arg2 (" << doubleOptionOneConfig->d1arg2() << ") "
		 << "d1arg3 (" << doubleOptionOneConfig->d1arg3() << ")" << std::endl
		 << "\td2arg1 (" << (doubleOptionTwoConfig->d2arg1() ? "true" : "false") << ") "
		 << "d2arg2 (" << doubleOptionTwoConfig->d2arg2() << ") "
		 << "d2arg3 (" << doubleOptionTwoConfig->d2arg3() << ")" << std::endl;

	// Process the command line
	optManager.processCommandLine(argc, argv);
	std::cout << "After:  " << std::endl
		 << "\td1arg1 (" << (doubleOptionOneConfig->d1arg1() ? "true" : "false") << ") "
		 << "d1arg2 (" << doubleOptionOneConfig->d1arg2() << ") "
		 << "d1arg3 (" << doubleOptionOneConfig->d1arg3() << ")" << std::endl
		 << "\td2arg1 (" << (doubleOptionTwoConfig->d2arg1() ? "true" : "false") << ") "
		 << "d2arg2 (" << doubleOptionTwoConfig->d2arg2() << ") "
		 << "d2arg3 (" << doubleOptionTwoConfig->d2arg3() << ")" << std::endl;
}
