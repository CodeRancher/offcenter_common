/**
 * Copyright 2020 Scott Brauer
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
 * @file   date_time_interval_test.cpp
 * @author Scott Brauer
 * @date   11-07-2021
 */

#include <gtest/gtest.h>

#include "easylogging++.h"

#include "offcenter/common/DateTimeInterval.hpp"
#include "offcenter/common/DateTimeException.hpp"

TEST (DateTimeInterval, Parse)
{
		using namespace std::chrono;

	//offcenter::common::DateTimeIntervalConfig config;
	//offcenter::common::DateTimeInterval dti;

	//UTCDateTime dt = make_UTCDateTimeFromTimestamp("1623445135.000000000");
	//std::cout << UTCDateTimeToISO8601(dt);

	/*
		std::pair<std::string, std::string> parsed = parseTimestamp("0.1");
	EXPECT_EQ(parsed.first, "0");
	EXPECT_EQ(parsed.second, "1");

	parsed = parseTimestamp("2");
	EXPECT_EQ(parsed.first, "2");
	EXPECT_EQ(parsed.second, "");

	parsed = parseTimestamp("3.");
	EXPECT_EQ(parsed.first, "3");
	EXPECT_EQ(parsed.second, "");

	EXPECT_THROW(
		parsed = parseTimestamp("4k5"),
		offcenter::common::DateTimeException
	);

	EXPECT_THROW(
		parsed = parseTimestamp("6.0a"),
		offcenter::common::DateTimeException
	);

	parsed = parseTimestamp("0123456789.9876543210");
	EXPECT_EQ(parsed.first, "0123456789");
	EXPECT_EQ(parsed.second, "9876543210");
	*/
}

TEST (DateTimeInterval, UTCTime)
{
	/*
		using namespace std::chrono;

	EXPECT_EQ(UTCDateTimeToISO8601(make_UTCDateTimeFromTimestamp("1623445135.000000000")), "2021-06-11T20:58:55.000000000Z");
	EXPECT_EQ(UTCDateTimeToISO8601(make_UTCDateTimeFromTimestamp("1623445135")), "2021-06-11T20:58:55.000000000Z");
	EXPECT_THROW(
			EXPECT_EQ(UTCDateTimeToISO8601(make_UTCDateTimeFromTimestamp("1623445135k0.0000000")), "2021-06-11T20:58:55.000000000Z"),
			offcenter::common::DateTimeException
	);

	EXPECT_EQ(UTCDateTimeToISO8601(make_UTCDateTimeFromTimestamp("1623445135.000000000")), "2021-06-11T20:58:55.000000000Z");
	EXPECT_EQ(UTCDateTimeToISO8601(make_UTCDateTimeFromTimestamp("1623445140.000000000")), "2021-06-11T20:59:00.000000000Z");
	EXPECT_EQ(UTCDateTimeToISO8601(make_UTCDateTimeFromTimestamp("1623445150.000000000")), "2021-06-11T20:59:10.000000000Z");
	EXPECT_EQ(UTCDateTimeToISO8601(make_UTCDateTimeFromTimestamp("1623445170.000000000")), "2021-06-11T20:59:30.000000000Z");
	EXPECT_EQ(UTCDateTimeToISO8601(make_UTCDateTimeFromTimestamp("1623445175.000000000")), "2021-06-11T20:59:35.000000000Z");
	EXPECT_EQ(UTCDateTimeToISO8601(make_UTCDateTimeFromTimestamp("1623445190.000000000")), "2021-06-11T20:59:50.000000000Z");
	*/
}

TEST (DateTimeInterval, UTCEpoch)
{
	/*
		using namespace std::chrono;

	auto timePoint = make_UTCDateTimeFromTimestamp("1623445135.000000000");
	auto seconds =  UTCDateTimeSecondsFromEpoch(timePoint);
	//LOG(DEBUG) << "UTCEpoch: 1623445135.000000000:" << seconds;
	auto timePointRT = make_UTCDateTimeFromTimestamp(seconds);
	//LOG(DEBUG) << "UTCEpoch1: " << UTCDateTimeToISO8601(timePoint) << ":" << UTCDateTimeToISO8601(timePointRT);
	EXPECT_EQ(timePoint, timePointRT);
	*/
	/*
	EXPECT_EQ(UTCDateTimeToISO8601(make_UTCDateTimeFromTimestamp("1623445135.000000000")), "2021-06-11T20:58:55.000000000Z");
	EXPECT_EQ(UTCDateTimeToISO8601(make_UTCDateTimeFromTimestamp("1623445140.000000000")), "2021-06-11T20:59:00.000000000Z");
	EXPECT_EQ(UTCDateTimeToISO8601(make_UTCDateTimeFromTimestamp("1623445150.000000000")), "2021-06-11T20:59:10.000000000Z");
	EXPECT_EQ(UTCDateTimeToISO8601(make_UTCDateTimeFromTimestamp("1623445170.000000000")), "2021-06-11T20:59:30.000000000Z");
	EXPECT_EQ(UTCDateTimeToISO8601(make_UTCDateTimeFromTimestamp("1623445175.000000000")), "2021-06-11T20:59:35.000000000Z");
	EXPECT_EQ(UTCDateTimeToISO8601(make_UTCDateTimeFromTimestamp("1623445190.000000000")), "2021-06-11T20:59:50.000000000Z");
	*/
}

