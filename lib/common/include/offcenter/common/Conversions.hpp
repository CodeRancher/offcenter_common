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
 * @file   Conversions.hpp
 * @author Scott Brauer
 * @date   03-14-2022
 */

#ifndef OffcenterCommon_CONVERSIONS_HPP_
#define OffcenterCommon_CONVERSIONS_HPP_

#include <boost/multiprecision/mpfr.hpp>

#include "offcenter/common/DateTime.hpp"
#include "offcenter/common/Types.hpp"

namespace offcenter {
namespace common {

template<typename From, typename To>
void convertTo(const From& from, To& to) {
	to = from;
}

template<>
void convertTo(const std::string& from, offcenter::common::UTCDateTime& to);

template<>
void convertTo(const offcenter::common::UTCDateTime& from, std::string& to);

template<>
void convertTo(const std::string& from, double& to);

template<>
void convertTo(const double& from, std::string& to);

template<>
void convertTo(const char* const & from, double& to);

template<>
void convertTo(const std::string& from, MPF& to);

template<>
void convertTo(const MPF& from, std::string& to);

template<>
void convertTo(const std::string& from, MPF_7& to);

template<>
void convertTo(const MPF_7& from, std::string& to);

template<>
void convertTo(const std::string& from, MPF_10& to);

template<>
void convertTo(const MPF_10& from, std::string& to);

template<>
void convertTo(const std::string& from, MPF_20& to);

template<>
void convertTo(const MPF_20& from, std::string& to);

} /* namespace common */
} /* namespace offcenter */

#endif /* OffcenterCommon_CONVERSIONS_HPP_ */
