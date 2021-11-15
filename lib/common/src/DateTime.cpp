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
 * @file   DateTime.cpp
 * @author Scott Brauer
 * @date   06-12-2021
 */

#include "easylogging++.h"

#include "offcenter/common/DateTime.hpp"
#include "offcenter/common/DateTimeException.hpp"

namespace offcenter {
namespace common {

/**
 * Parse a timestamp into whole number side and fractional side
 *
 * @param timestamp String representation of timestamp (0000.0000
 * @return pair<string,string> that contains the whole and fractional parts of the timestamp.
 */
std::pair<std::string, std::string> parseTimestamp(const std::string& timestamp)
{
    std::regex regex("^(\\d*)(?:\\.(\\d*))?$"); // ddd.ddd
    std::smatch match;
    if (!std::regex_match(timestamp, match, regex)) {
    	throw DateTimeException("Error parsing timestamp: " + timestamp);
    }

    switch (match.size()) {
    	case 2: return std::make_pair(match[1], "");
    	case 3: return std::make_pair(match[1], match[2]);
    	default: throw DateTimeException("Invalid results when parsing timestamp: " + timestamp);
    }
}

/**
 * Make a UTCDateTime based on a timestamp as a string.
 *
 * @param dtAsString Timestamp defined as a string
 * @return A UTCDateTime time_point based on the string
 */const UTCDateTime make_UTCDateTimeFromTimestamp(const std::string &dtAsString)
{
	return make_CustomDateTimeFromTimestamp<UTCDateTime>(dtAsString);
}

 /**
  * Make a UTCDateTime based on a timestamp.
  *
  * @param dtAsULL Timestamp defined as seconds from epoch
  * @return A UTCDateTime time_point based on the string
  */const UTCDateTime make_UTCDateTimeFromTimestamp(const unsigned long long& dtAsULL)
{
	return make_CustomDateTimeFromTimestamp<UTCDateTime>(dtAsULL);
}

/**
 * Make a UTCDateTime time_point one second past epoch.
 *
 * @return A UTCDateTime time_point
 */
const UTCDateTime make_UTCDateTimeSmallest()
{
	return make_CustomDateTimeSmallest<UTCDateTime>();
}

/**
 * Make a UTCDateTime time_point based on an ISO8601 string
 *
 * @param dtAsString ISO8601 string
 * @return A UTCDateTime time_point based on the string
 */
const UTCDateTime make_UTCDateTimeFromISO8601(const std::string &dtAsString)
{
	return make_CustomDateTimeFromISO8601<UTCDateTime>(dtAsString);
}

/**
 * Convert a UTCDateTime to an ISO8601 string
 *
 * @param dt UTCDateTime to convert to a string
 * @return A string of the converted UTCDateTime
 */
const std::string UTCDateTimeToISO8601(const UTCDateTime &dt)
{
	return CustomDateTimeToISO8601<UTCDateTime>(dt);
}

/**
 * Calculate number of seconds between a UTCDateTime and the epoch
 *
 * @param dt UTCDateTime to calculate seconds from epoch
 * @return Number of seconds since epoch
 */
const unsigned long long UTCDateTimeSecondsFromEpoch(const UTCDateTime& dt)
{
	return CustomDateTimeSecondsFromEpoch<UTCDateTime>(dt);
}

} /* namespace common */
} /* namespace offcenter */
