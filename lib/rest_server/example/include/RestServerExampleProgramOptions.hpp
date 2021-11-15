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
 * @file   RestServerExampleProgramOptions.hpp
 * @author Scott Brauer
 * @date   04-02-2021
 */

#ifndef OFFCENTER_TRADING_CREATETRADINGDB_RESTSERVEREXAMPLEPROGRAMOPTIONS_HPP_
#define OFFCENTER_TRADING_CREATETRADINGDB_RESTSERVEREXAMPLEPROGRAMOPTIONS_HPP_

#include <functional>

#include <boost/bind/bind.hpp>

#include "offcenter/common/program_options/ProgramOptionsGroup.hpp"
#include "offcenter/trading/createtradingdb/CreateTradingDBOptions.hpp"
using namespace offcenter::common;

namespace offcenter {
namespace trading {
namespace createtradingdb {

class CreateTradingDBProgramOptions:
		public program_options::ProgramOptionsGroup<offcenter::trading::createtradingdb::CreateTradingDBOptions>
{
public:
	CreateTradingDBProgramOptions():
		ProgramOptionsGroup("Create Trading DB Options")
	{
		optionsDescription().add_options()
				("dropdb", po::bool_switch(&optionConfig().m_dropDB)->default_value(false), "Drop database if it exists")
				;
	}

	virtual ~CreateTradingDBProgramOptions() = default;
};

} /* namespace createtradingdb */
} /* namespace trading */
} /* namespace offcenter */

#endif /* OFFCENTER_TRADING_CREATETRADINGDB_RESTSERVEREXAMPLEPROGRAMOPTIONS_HPP_ */
