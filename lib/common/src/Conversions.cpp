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
 * @file   Conversions.cpp
 * @author Scott Brauer
 * @date   03-14-2022
 */

#include "offcenter/common/Conversions.hpp"

namespace offcenter {
namespace common {

template<>
void convertTo(const std::string& from, offcenter::common::UTCDateTime& to)
{
	to = make_UTCDateTimeFromISO8601(from);
}

template<>
void convertTo(const offcenter::common::UTCDateTime& from, std::string& to)
{
	to = UTCDateTimeToISO8601(from);
}

template<>
void convertTo(const std::string& from, double& to)
{
	to = std::stod(from);
}

template<>
void convertTo(const double& from, std::string& to)
{
	to = std::to_string(from);
}

template<>
void convertTo(const char* const & from, double& to)
{
	to = std::stod(from);
}

template<>
void convertTo(const std::string& from, MPF& to)
{
	MPF tmpTo(from);
	to = tmpTo;
}

template<>
void convertTo(const MPF& from, std::string& to)
{
	to = from.str(0);
}

template<>
void convertTo(const std::string& from, MPF_7& to)
{
	MPF_7 tmpTo(from);
	to = tmpTo;
}

template<>
void convertTo(const MPF_7& from, std::string& to)
{
	to = from.str(7);
}

template<>
void convertTo(const std::string& from, MPF_10& to)
{
	MPF_10 tmpTo(from);
	to = tmpTo;
}

template<>
void convertTo(const MPF_10& from, std::string& to)
{
	to = from.str(10);
}

template<>
void convertTo(const std::string& from, MPF_20& to)
{
	MPF_20 tmpTo(from);
	to = tmpTo;
}

template<>
void convertTo(const MPF_20& from, std::string& to)
{
	to = from.str(20);
}


} /* namespace common */
} /* namespace offcenter */
