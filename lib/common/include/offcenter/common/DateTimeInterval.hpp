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
template<typename IntervalDuration>
class DateTimeInterval
{
public:
	DateTimeInterval() = delete;
	explicit DateTimeInterval(int startDuration, int widthDuration):
		m_startDuration(startDuration),
		m_widthDuration(widthDuration)
	{}

	virtual ~DateTimeInterval() = default;

	const UTCDateTime rangeStart(const UTCDateTime& timeTime) const {
	    offcenter::common::UTCDateTime timeRangeDiff = timeTime - m_startDuration;
	    offcenter::common::UTCDateTime timeDiffFloor = std::chrono::floor<std::chrono::minutes>(timeRangeDiff);
	    offcenter::common::UTCDateTime::duration timeDiff = timeRangeDiff - timeDiffFloor;
        int durCnt = timeDiff / m_widthDuration;
        return std::chrono::time_point_cast<offcenter::common::UTCDateTime::duration>(timeDiffFloor + m_startDuration + (durCnt * m_widthDuration));
	};

	IntervalDuration startDuration() const { return m_startDuration; }
	IntervalDuration widthDuration() const { return m_widthDuration; }

private:
	const IntervalDuration m_startDuration;
	const IntervalDuration m_widthDuration;
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
