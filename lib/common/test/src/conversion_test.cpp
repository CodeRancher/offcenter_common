/**
 * Copyright 2022 Scott Brauer
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
 * @file   conversion_test.cpp
 * @author Scott Brauer
 * @date   03-14-2022
 */

#include <gtest/gtest.h>
#include <boost/multiprecision/gmp.hpp>
#include <boost/multiprecision/mpfr.hpp>
#include <boost/multiprecision/cpp_dec_float.hpp>

#include "easylogging++.h"

#include "offcenter/common/DateTime.hpp"
#include "offcenter/common/DateTimeException.hpp"
#include "offcenter/common/Conversions.hpp"

template<typename From, typename To>
void testConversion(const From& from, const To& expected) {
	To to;
	offcenter::common::convertTo(from, to);
	EXPECT_EQ(to, expected);
}

TEST (Conversion, Time)
{
	const std::string timeString{"2000-01-01T00:00:00.000000000Z"};
	const offcenter::common::UTCDateTime timePoint{offcenter::common::make_UTCDateTimeFromISO8601(timeString)};

	using namespace offcenter::common;
	testConversion<std::string, UTCDateTime>(timeString, timePoint);
	testConversion<UTCDateTime, std::string>(timePoint, timeString);
}

TEST (Conversion, Double)
{
	const std::string strDouble{"1.234560"};
	const char* charPDouble = "1.23456";
	const double dblDouble{std::stod(strDouble)};

	testConversion<std::string, double>(strDouble, dblDouble);
	testConversion<const char* const, double>(charPDouble, dblDouble);
	testConversion<double, std::string>(dblDouble, strDouble);
}

TEST (Conversion, MPFVal)
{
	const std::string strMPF{"1.1234567"};
	const offcenter::common::MPF mpf(strMPF.c_str());

	using namespace offcenter::common;
	testConversion<std::string, MPF>(strMPF, mpf);
	testConversion<MPF, std::string>(mpf, "1.1234567");
}

TEST (Conversion, MPF_7Val)
{
	const std::string strMPF{"1.1234567"};
	const offcenter::common::MPF_7 mpf(strMPF.c_str());

	using namespace offcenter::common;
	testConversion<std::string, MPF_7>(strMPF, mpf);
	testConversion<MPF_7, std::string>(mpf, "1.123457");
}

TEST (Conversion, MPF_10Val)
{
	const std::string strMPF{"1.1234567890"};
	const offcenter::common::MPF_10 mpf(strMPF);

	using namespace offcenter::common;
	testConversion<std::string, MPF_10>(strMPF, mpf);
	testConversion<MPF_10, std::string>(mpf, "1.123456789");
}

TEST (Conversion, MPF_20Val)
{
	const std::string strMPF{"1.12345678901234567890"};
	const offcenter::common::MPF_20 mpf(strMPF);

	using namespace offcenter::common;
	testConversion<std::string, MPF_20>(strMPF, mpf);
	testConversion<MPF_20, std::string>(mpf, "1.1234567890123456789");
}

