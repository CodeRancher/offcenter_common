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
 * @file   RuntimeException.hpp
 * @author Scott Brauer
 * @date   11-04-2021
 */

#ifndef OffcenterCommon_DATETIMEEXCEPTION_HPP_
#define OffcenterCommon_DATETIMEEXCEPTION_HPP_

#include "offcenter/common/RuntimeException.hpp"

namespace offcenter {
namespace common {

class DateTimeException:
		public RuntimeException
{
public:
	explicit DateTimeException(const std::string& what_arg):
		RuntimeException(what_arg)
	{

	}

	explicit DateTimeException(const char* what_arg):
		RuntimeException(what_arg)
	{

	}

	virtual ~DateTimeException()
	{

	}
};

} /* namespace common */
} /* namespace offcenter */

#endif /* OffcenterCommon_DATETIMEEXCEPTION_HPP_ */
