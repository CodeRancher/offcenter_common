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
 * @file   Types.hpp
 * @author Scott Brauer
 * @date   03-15-2022
 */

#ifndef OFFCENTER_COMMON_TYPES_HPP_
#define OFFCENTER_COMMON_TYPES_HPP_

namespace offcenter {
namespace common {

#include <boost/multiprecision/mpfr.hpp>

using MPF = boost::multiprecision::number<boost::multiprecision::mpfr_float_backend<0> >;
using MPF_7 = boost::multiprecision::number<boost::multiprecision::mpfr_float_backend<7> >;
using MPF_10 = boost::multiprecision::number<boost::multiprecision::mpfr_float_backend<10> >;
using MPF_20 = boost::multiprecision::number<boost::multiprecision::mpfr_float_backend<20> >;


} /* namespace common */
} /* namespace offcenter */

#endif /* OFFCENTER_COMMON_TYPES_HPP_ */
