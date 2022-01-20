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
 * @file   ProgramOptionsGroup.hpp
 * @author Scott Brauer
 * @date   04-04-2019
 */

#ifndef OFFCENTER_COMMON_PROGRAMOPTIONS_PROGRAMOPTIONSGROUP_HPP_
#define OFFCENTER_COMMON_PROGRAMOPTIONS_PROGRAMOPTIONSGROUP_HPP_

#include <boost/program_options.hpp>
namespace po = boost::program_options;

#include "IProgramOptionsGroup.hpp"

namespace offcenter {
namespace common {
namespace program_options {

/**
 * A group of command line/config file options for an application.
 *
 * @tparam OptionConfig The related configuration options that will be filled
 *		   with the parsed values from the command line/config file.
 */
template<typename OptionConfig>
class ProgramOptionsGroup: public IProgramOptionsGroup
{
public:
	using ConfigPtr = std::shared_ptr<OptionConfig>;

public:
	/**
	 * Create a \c ProgramOptionsGroup
	 *
	 * The \c ProgramOptionsGroup is a set of options that can be set via the command line
	 * and/or a configuration file.
	 *
	 * @param groupName				A name describing this group. Displayed in help.
	 * @param isCommandLineOption	Are the elements of this group command line options? Default = true
	 * @param isConfigFileOption	Are the elements of this group config file options? Default = true
	 * @param isVisibleInHelpOption	Should the group be displayed in the help? Default = true
	 */
	ProgramOptionsGroup(
			std::string groupName,
			bool isCommandLineOption = true,
			bool isConfigFileOption = true,
			bool isVisibleInHelpOption = true):
		m_optionsDescription(groupName),
		m_positionalOptionsDescription(),
		m_isCommandLineOption(isCommandLineOption),
		m_isConfigFileOption(isConfigFileOption),
		m_isVisibleInHelpOption(isVisibleInHelpOption),
		m_optionConfig(),
		m_optionConfigPtr(std::make_shared<OptionConfig>())
		{}

	virtual ~ProgramOptionsGroup() = default;

	/// @copydoc IProgramOptionsGroup::processOptions(po::variables_map& vm)
	virtual void processOptions(po::variables_map& vm) {}
	/// @copydoc IProgramOptionsGroup::validateOptions(po::variables_map& vm)
	virtual void validateOptions(po::variables_map& vm) {}

	/// @copydoc IProgramOptionsGroup::isCommandLineOption()
	bool isCommandLineOption() override { return m_isCommandLineOption; }
	/// @copydoc IProgramOptionsGroup::isConfigFileOption()
	bool isConfigFileOption() override { return m_isConfigFileOption; }
	/// @copydoc IProgramOptionsGroup::isVisibleInHelpOption()
	bool isVisibleInHelpOption() override { return m_isVisibleInHelpOption; }

	/// @copydoc IProgramOptionsGroup::hasConfigFileName()
	bool hasConfigFileName() override { return false; }
	/// @copydoc IProgramOptionsGroup::getConfigFileName()
	std::string getConfigFileName() override { return ""; }
	/// @copydoc IProgramOptionsGroup::updateSharedData()
	void updateSharedData() { *m_optionConfigPtr = m_optionConfig; }

	/// @copydoc IProgramOptionsGroup::optionsDescription()
	po::options_description& optionsDescription() override { return m_optionsDescription; }
	/// @copydoc IProgramOptionsGroup::positionalOptionsDescription()
	po::positional_options_description& positionalOptionsDescription() override { return m_positionalOptionsDescription; }

	ConfigPtr optionConfigPtr() { return m_optionConfigPtr; }

private:
	po::options_description m_optionsDescription;
	po::positional_options_description m_positionalOptionsDescription;

	bool m_isCommandLineOption;
	bool m_isConfigFileOption;
	bool m_isVisibleInHelpOption;
	OptionConfig m_optionConfig;

protected:
	ConfigPtr m_optionConfigPtr;
	OptionConfig& optionConfig() { return m_optionConfig; }
	OptionConfig* optionConfigPointer() { return &m_optionConfig; }
};

} /* namespace program_options */
} /* namespace common */
} /* namespace offcenter */

#endif /* OFFCENTER_COMMON_PROGRAMOPTIONS_PROGRAMOPTIONSGROUP_HPP_ */
