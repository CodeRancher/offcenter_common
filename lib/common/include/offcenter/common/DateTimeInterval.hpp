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
 * @file   DateTimeInterval.hpp
 * @author Scott Brauer
 * @date   11-07-2021
 */

#ifndef OFFCENTER_COMMON_DATETIMEINTERVAL_HPP_
#define OFFCENTER_COMMON_DATETIMEINTERVAL_HPP_

#include "offcenter/common/DateTime.hpp"

namespace offcenter {
namespace common {

/**
 *
 */
class DateTimeIntervalConfig
{
public:
	DateTimeIntervalConfig();
	virtual ~DateTimeIntervalConfig();
};

/**
 *
 */
template<typename DateTime>
class DateTimeInterval
{
public:
	DateTimeInterval();
	virtual ~DateTimeInterval();

private:
	DateTime m_dateTime;

};

/**
 *
 */
template<typename DateTimeInterval>
const DateTimeInterval DateTimeIntervalFactory() {

}


} /* namespace common */
} /* namespace offcenter */

#endif /* OFFCENTER_COMMON_DATETIMEINTERVAL_HPP_ */
