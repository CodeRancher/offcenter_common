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
 * @file   RestServerExampleOptions.hpp
 * @author Scott Brauer
 * @date   04-02-2021
 */
#ifndef OFFCENTER_TRADING_CREATETRADINGDB_RESTSERVEREXAMPLEOPTIONS_HPP_
#define OFFCENTER_TRADING_CREATETRADINGDB_RESTSERVEREXAMPLEOPTIONS_HPP_

#include <string>


namespace offcenter {
namespace trading {
namespace createtradingdb {

class CreateTradingDBOptions
{
public:
	explicit CreateTradingDBOptions():
	m_dropDB(false) {}

	virtual ~CreateTradingDBOptions() {}

	bool dropDB() const { return m_dropDB; }

	friend class CreateTradingDBProgramOptions;

private:
	bool m_dropDB;
};

} /* namespace createtradingdb */
} /* namespace trading */
} /* namespace offcenter */

#endif /* OFFCENTER_TRADING_CREATETRADINGDB_RESTSERVEREXAMPLEOPTIONS_HPP_ */
