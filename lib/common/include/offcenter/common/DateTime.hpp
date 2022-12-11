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
 * @file   DateTime.hpp
 * @author Scott Brauer
 * @date   06-12-2021
 */

#ifndef OffcenterCommon_DATETIME_HPP_
#define OffcenterCommon_DATETIME_HPP_

#include <ios>
#include <chrono>
#include <utility>
#include <regex>

#include "date/date.h"

namespace offcenter {
namespace common {

//using days = std::chrono::duration
//    <int, std::ratio_multiply<std::ratio<24>, std::chrono::hours::period>>;

/**
 * A time_point based on UTC that can have a defined number of seconds for it's duration.
 */
template<class Rep, class Period = std::ratio<1>>
using CustomDateTime = std::chrono::time_point<std::chrono::system_clock, std::chrono::duration<Rep, Period>>;

/**
 * A time_point based on UTC with a one second duration.
 */
using UTCDateTime = std::chrono::system_clock::time_point; //CustomDateTime<int, std::ratio_multiply<std::ratio<1>, std::chrono::seconds::period>>;

const UTCDateTime make_UTCDateTimeFromTimestamp(const std::string& dtAsString);
const UTCDateTime make_UTCDateTimeFromTimestamp(const unsigned long long& dtAsULL);
const UTCDateTime make_UTCDateTimeSmallest();
const UTCDateTime make_UTCDateTimeFromISO8601(const std::string &dtAsString);
const std::string UTCDateTimeToISO8601(const UTCDateTime& dt);
const unsigned long long UTCDateTimeSecondsFromEpoch(const UTCDateTime& dt);

// Parse a timestamp into whole number side and fractional side
std::pair<std::string, std::string> parseTimestamp(const std::string& ts);

/**
 * Make a custom time_point based on a timestamp.
 *
 * @tparam DateTime CustomDateTime based type
 * @param dtAsULL Timestamp defined as seconds from epoch
 * @return A DateTime time_point based on the string
 */
template<typename DateTime>
const DateTime make_CustomDateTimeFromTimestamp(const unsigned long long& dtAsULL) {
	return std::chrono::time_point_cast<typename DateTime::duration>(
		date::sys_time<std::chrono::seconds>{std::chrono::seconds{dtAsULL}});
}

/**
 * Make a custom time_point based on a timestamp as a string.
 *
 * @tparam DateTime CustomDateTime based type
 * @param dtAsString Timestamp defined as a string
 * @return A DateTime time_point based on the string
 */
template<typename DateTime>
const DateTime make_CustomDateTimeFromTimestamp(const std::string& dtAsString) {
	std::pair<std::string, std::string> parsedTS = parseTimestamp(dtAsString);
	std::istringstream in{parsedTS.first};
	unsigned long long seconds;
	in >> seconds;
	return make_CustomDateTimeFromTimestamp<DateTime>(seconds);
}

/**
 * Make a custom time_point one second past epoch.
 *
 * @tparam DateTime CustomDateTime based type
 * @return A DateTime time_point
 */
template<typename DateTime>
const DateTime make_CustomDateTimeSmallest() {
	return make_CustomDateTimeFromTimestamp<DateTime>(1ull);
}

/**
 * Make a custom time_point based on an ISO8601 string
 *
 * @tparam DateTime CustomDateTime based type
 * @param dtAsString ISO8601 string
 * @return A DateTime time_point based on the string
 */
template<typename DateTime>
const DateTime make_CustomDateTimeFromISO8601(const std::string &dtAsString) {
	std::istringstream in{dtAsString};
	date::sys_time<std::chrono::milliseconds> tp;
	in >> date::parse("%FT%TZ", tp);
	if (in.fail())
	{
		in.clear();
		in.exceptions(std::ios::failbit);
		in.str(dtAsString);
		in >> date::parse("%FT%T%Ez", tp);
	}
	return std::chrono::time_point_cast<typename DateTime::duration>(tp);
}

/**
 * Convert a time_point to an ISO8601 string
 *
 * @tparam DateTime CustomDateTime based type
 * @param dt DateTime to convert to a string
 * @return A string of the converted DateTime
 */
template<typename DateTime>
const std::string CustomDateTimeToISO8601(const DateTime& dt) {
	return date::format("%FT%TZ", dt);
}

//template<>
//const std::string CustomDateTimeToISO8601<UTCDateTime_W>(const UTCDateTime_W& dt);

/**
 * Calculate number of seconds between a DateTime and the epoch
 *
 * @tparam DateTime CustomDateTime based type
 * @param dt DateTime to calculate seconds from epoch
 * @return Number of seconds since epoch
 */
template<typename DateTime>
const unsigned long long CustomDateTimeSecondsFromEpoch(const DateTime& dt) {
	return std::chrono::duration_cast<std::chrono::seconds>(dt.time_since_epoch()).count();
}

} /* namespace common */
} /* namespace offcenter */

#endif /* OffcenterCommon_DATETIME_HPP_ */
