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

template<typename OptionConfig>
class ProgramOptionsGroup: public IProgramOptionsGroup
{
public:
	using ConfigPtr = std::shared_ptr<OptionConfig>;

private:
	po::options_description m_optionsDescription;

	bool m_isCommandLineOption;
	bool m_isConfigFileOption;
	bool m_isVisibleInHelpOption;
	OptionConfig m_optionConfig;

protected:
	ConfigPtr m_optionConfigPtr;

public:
	/*
	ProgramOptionsGroup(std::string groupName, OptionConfig& optionConfig, bool isCommandLineOption = true,
			bool isConfigFileOption = true, bool isVisibleInHelpOption = true):
		m_optionsDescription(groupName),
		m_optionConfig(optionConfig),
		m_isCommandLineOption(isCommandLineOption),
		m_isConfigFileOption(isConfigFileOption),
		m_isVisibleInHelpOption(isVisibleInHelpOption),
		m_optionConfig2() {}
	*/
	ProgramOptionsGroup(
			std::string groupName,
			bool isCommandLineOption = true,
			bool isConfigFileOption = true,
			bool isVisibleInHelpOption = true):
		m_optionsDescription(groupName),
		m_isCommandLineOption(isCommandLineOption),
		m_isConfigFileOption(isConfigFileOption),
		m_isVisibleInHelpOption(isVisibleInHelpOption),
		m_optionConfig(),
		m_optionConfigPtr(std::make_shared<OptionConfig>())
		{}

	virtual ~ProgramOptionsGroup() = default;

	bool isCommandLineOption() override { return m_isCommandLineOption; }
	bool isConfigFileOption() override { return m_isConfigFileOption; }
	bool isVisibleInHelpOption() override { return m_isVisibleInHelpOption; }

	bool hasConfigFileName() override { return false; }
	std::string getConfigFileName() override { return ""; }
	void updateSharedData() { *m_optionConfigPtr = m_optionConfig; }

	virtual void processOptions(po::variables_map& vm) {}
	virtual void validateOptions(po::variables_map& vm) {}

	po::options_description& optionsDescription() override { return m_optionsDescription; }

	ConfigPtr optionConfigPtr() { return m_optionConfigPtr; }

protected:
	OptionConfig& optionConfig() { return m_optionConfig; }
	OptionConfig* optionConfigPointer() { return &m_optionConfig; }
};

} /* namespace program_options */
} /* namespace common */
} /* namespace offcenter */

#endif /* OFFCENTER_COMMON_PROGRAMOPTIONS_PROGRAMOPTIONSGROUP_HPP_ */
