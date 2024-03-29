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
 * @file   ProgramOptionsManager.hpp
 * @author Scott Brauer
 * @date   04-04-2019
 */

#ifndef OffcenterCommon_PROGRAMOPTIONS_PROGRAMOPTIONSMANAGER_HPP_
#define OffcenterCommon_PROGRAMOPTIONS_PROGRAMOPTIONSMANAGER_HPP_

#include <memory>
#include <vector>
#include <fstream>

#include <boost/program_options.hpp>
namespace po = boost::program_options;

#include "IProgramOptionsGroup.hpp"
#include "offcenter/common/FileException.hpp"
#include "offcenter/common/RuntimeException.hpp"

namespace offcenter {
namespace common {
namespace program_options {

/**
 * Centralized manager for program option handling.
 */
class ProgramOptionsManager
{
private:
	std::vector<IProgramOptionsGroup::Ptr> m_programOptionsGroups;

	po::options_description m_cmdlineOptions;
	po::positional_options_description m_cmdlinePositionalOptions;
	po::options_description m_configFileOptions;
	po::options_description m_visibleInHelpOptions;
	po::variables_map m_vm;


public:
	/// Default constructor
	ProgramOptionsManager():
		m_visibleInHelpOptions("Program options")
	{}

	/// Default destructor
	virtual ~ProgramOptionsManager() = default;

	/**
	 * Parse the command line parameters and set the related configuration options
	 * 
	 * @param argc Number of command line arguments
	 * @param argv Character pointers listing all arguments
	 */
	void processCommandLine(int argc, char** argv)
	{

		for (IProgramOptionsGroup::Ptr group: m_programOptionsGroups) {
			if (group->isCommandLineOption()) {
				m_cmdlineOptions.add(group->optionsDescription());
				if (group->positionalOptionsDescription().max_total_count() > 0) {
					if (m_cmdlinePositionalOptions.max_total_count() > 0) {
						throw offcenter::common::RuntimeException("Multiple command line groups contain positional options. Only one allowed.");
					}
					m_cmdlinePositionalOptions = group->positionalOptionsDescription();
				}
			}

			if (group->isConfigFileOption()) {
				m_configFileOptions.add(group->optionsDescription());
			}

			if (group->isVisibleInHelpOption()) {
				m_visibleInHelpOptions.add(group->optionsDescription());
			}
		}

		if (m_cmdlinePositionalOptions.max_total_count() > 0) {
			store(po::command_line_parser(argc, argv).options(m_cmdlineOptions).positional(m_cmdlinePositionalOptions).run(), m_vm);
		} else {
			store(po::command_line_parser(argc, argv).options(m_cmdlineOptions).run(), m_vm);
		}
		notify(m_vm);

		for (IProgramOptionsGroup::Ptr group: m_programOptionsGroups) {
			group->processOptions(m_vm);
			group->validateOptions(m_vm);
		}

		for (IProgramOptionsGroup::Ptr group: m_programOptionsGroups) {
			if (group->hasConfigFileName()) {
				std::ifstream ifs(group->getConfigFileName().c_str());
				if (ifs) {
					store(po::parse_config_file(ifs, m_configFileOptions), m_vm);
					notify(m_vm);
				} else {
					throw offcenter::common::FileException("Unable to open config file: " + group->getConfigFileName());
				}
			}
		}

		// Update shared config data
		for (IProgramOptionsGroup::Ptr group: m_programOptionsGroups) {
			group->updateSharedData();
		}
	}

	/**
	 * Add an option group to the program options group and return the configuration options shared pointer.
	 * 
	 * @return Configuration prointer for the added option group.
	 */
	template<class OptionGroup>
	typename OptionGroup::ConfigPtr add() {
		std::shared_ptr<OptionGroup> optGroup = std::make_shared<OptionGroup>();
		m_programOptionsGroups.push_back(optGroup);
		return optGroup->optionConfigPtr();
	}

	/**
	 * Generate the help text.
	 * 
	 * @return String containing the help text
	 */
	std::string help() {
		std::stringstream buffer;
		buffer << m_visibleInHelpOptions;
		return buffer.str();
	}
};

} /* namespace program_options */
} /* namespace common */
} /* namespace offcenter */

#endif /* OffcenterCommon_PROGRAMOPTIONS_PROGRAMOPTIONSMANAGER_HPP_\ */
