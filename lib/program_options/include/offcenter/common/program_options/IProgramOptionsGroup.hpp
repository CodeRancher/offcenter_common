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
 * @file   IProgramOptionsGroup.hpp
 * @author Scott Brauer
 * @date   04-14-2019
 */

#ifndef OffcenterCommon_PROGRAMOPTIONS_IPROGRAMOPTIONSGROUP_HPP_
#define OffcenterCommon_PROGRAMOPTIONS_IPROGRAMOPTIONSGROUP_HPP_

#include <memory>

namespace offcenter {
namespace common {
namespace program_options {

/**
 * @interface IProgramOptionsGroup
 * @brief
 */
class IProgramOptionsGroup
{
public:
	/// Helper type for a shared pointer to \c IProgramOptionsGroup.
	using Ptr = std::shared_ptr<IProgramOptionsGroup>;

public:
	virtual ~IProgramOptionsGroup() = default;

	/**
	 * Allows for processing of the options after the command line has been parsed.
	 *
	 * @param vm The Boost variables_map containing the parsed parameters.
	 */
	virtual void processOptions(po::variables_map& vm) = 0;

	/**
	 * Allows for validation of the options after the command line has been parsed.
	 *
	 * @param vm The Boost variables_map containing the parsed parameters.
	 */
	virtual void validateOptions(po::variables_map& vm) = 0;

	/**
	 * Are the options in this group available from the command line?
	 *
	 * @return True if command line options.
	 */
	virtual bool isCommandLineOption() = 0;

	/**
	 * Are the options in this group available from the config file?
	 *
	 * @return True if config file options.
	 */
	virtual bool isConfigFileOption() = 0;

	/**
	 * Are the options in this group displayed in help?
	 *
	 * @return True if options displayed in help.
	 */
	virtual bool isVisibleInHelpOption() = 0;

	/**
	 * Does this group contain a config file name?
	 *
	 * @return True if it has a config file name.
	 */
	virtual bool hasConfigFileName() = 0;

	/**
	 * Return the path of the config file.
	 *
	 * @return Path of the config file.
	 */
	virtual std::string getConfigFileName() = 0;

	/**
	 * Update the shared configuration data from the internal copy.
	 */
	virtual void updateSharedData() = 0;

	/**
	 * Access the internal options_description element. Typically used in the constructor
	 * to build the options lists.
	 *
	 * @return Returns a reference to the internal options_description.
	 */
	virtual po::options_description& optionsDescription() = 0;

	/**
	 * Access the internal positional_options_description element. Typically used in the
	 * constructor to build the positional options lists.
	 *
	 * @return Returns a reference to the internal positional_options_description.
	 */
	virtual po::positional_options_description& positionalOptionsDescription() = 0;

};

} /* namespace program_options */
} /* namespace common */
} /* namespace offcenter */

#endif /* OffcenterCommon_PROGRAMOPTIONS_IPROGRAMOPTIONSGROUP_HPP_ */
