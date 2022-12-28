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
 * @file   framework_example.cpp
 * @author Scott Brauer
 * @date   01-17-2022
 *
 * An example application demonstrating how to use the application framework.
 */

#include <string>
#include <iostream>

#include "easylogging++.h"

INITIALIZE_EASYLOGGINGPP

#include "offcenter/common/Utility.hpp"
#include "offcenter/common/framework/application/Utility.hpp"
#include "offcenter/common/framework/application/IApp.hpp"
#include "offcenter/common/framework/application/framework_application_main.hpp"
#include "offcenter/common/program_options/ProgramOptionsGroup.hpp"

/*
 * Configuration options
 */
class FrameworkExampleOptions
{
public:
	explicit FrameworkExampleOptions():
		m_path()
	{}

	virtual ~FrameworkExampleOptions() = default;

	const std::string path() const { return m_path; }

	friend class FrameworkExampleProgramOptions;

private:
	std::string m_path;

};

/*
 * Program options
 */
class FrameworkExampleProgramOptions:
		public offcenter::common::program_options::ProgramOptionsGroup<FrameworkExampleOptions>
{
public:
	FrameworkExampleProgramOptions():
		ProgramOptionsGroup("Framework Example Options")
	{
		// Add options
		optionsDescription().add_options()
				("path,p", po::value<std::string>(&optionConfig().m_path)->default_value("."), "Path to file or directory")
				;

		// Add positional options
		positionalOptionsDescription().add("path", 1);
	}

	virtual ~FrameworkExampleProgramOptions() = default;
};

/*
 * The main application class.
 *
 * Perform the application code in the onExecute method.
 */
class FrameworkExampleApp:
		public offcenter::common::framework::application::IApp
{
public:
	/*
	 * Initialize the program options for the application
	 */
	void onInitProgramOptions(offcenter::common::program_options::ProgramOptionsManager& optionsManager) override {
		m_programConfig = optionsManager.add<FrameworkExampleProgramOptions>();
	}

	// Perform setup for application
	void onSetUp() override {}

	/*
	 * Application execution
	 *
	 * Display stat information about the path
	 */
	void onExecute() override {
		std::cout << std::endl;
		std::cout << m_programConfig->path() << std::endl;

		struct stat fileInfo;

		if (stat(m_programConfig->path().c_str(), &fileInfo) == 0) {
			// Print file or directory info
			std::cout << "Type:         : ";
			if ((fileInfo.st_mode & S_IFMT) == S_IFDIR) {
				std::cout << "Directory";
			} else {
				std::cout << "File";
			}
			std::cout << std::endl;

			std::cout << "Size          : " << fileInfo.st_size << std::endl;
			std::cout << "Device        : " << (char)(fileInfo.st_dev + 'A') << std::endl;
			std::cout << "Created       : " << std::ctime(&fileInfo.st_ctime);
			std::cout << "Modified      : " << std::ctime(&fileInfo.st_mtime);
		} else {
			std::cerr << "Unable to examine file or directory: " << m_programConfig->path()
					<< " Error(" << strerror(errno) << ")" << std::endl;
		}
	}

	// Perform teardown for application
	void onTearDown() override {}

	/*
	 * Display help
	 */
	void onHelp(const std::string& help) override {
		std::cout << std::endl;
		std::cout << "Example program showing how to use the basic application framework 'IApp'" << std::endl;
		std::cout << std::endl;
		std::cout << "Usage: " << DefToString(EXE_NAME) << " [options] path" << std::endl;
		std::cout << std::endl;
		std::cout << help << std::endl;
	}

	/*
	 * Display version
	 */
	void onVersion() override {
		std::cout << std::endl;
		std::cout << "Example program showing how to use the basic application framework 'IApp'" << std::endl;
		std::cout << std::endl;
		std::cout << "Version: " << DefToString(EXE_VERSION) << std::endl;
		std::cout << std::endl;
	}

private:
	FrameworkExampleProgramOptions::ConfigPtr m_programConfig; // Program configuration

};

/*
 * Main application
 *
 * The main application is handled in the framework_application_main method.
 */
int main(int argc, char **argv)
{
	START_EASYLOGGINGPP(argc, argv);

	framework_application_main<FrameworkExampleApp>(argc, argv, "Framework Example", "FrameworkExampleApp");
}
