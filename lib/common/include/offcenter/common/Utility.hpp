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
 * @file   Utility.hpp
 * @author Scott Brauer
 * @date   05-04-2020
 */

#ifndef OFFCENTER_COMMON_UTILITY_HPP_
#define OFFCENTER_COMMON_UTILITY_HPP_

#include <string>
#include <initializer_list>
#include <sstream>

namespace offcenter {
namespace common {

/**
 * Join a list of strings
 *
 * @param elements A list of strings
 * @param sep An optional separator
 * @return all elements joined together separated by sep
 */
template<class Container>
std::string join(const Container& elements, const std::string sep = "")
{
	std::ostringstream ss;
	bool firstElement = true;
	for (auto element : elements) {
		ss << (!firstElement ? sep : "") << element;
		firstElement = false;
	}
	return ss.str();
}

/**
 * Case insensitive string compare
 *
 * @param str1 first string to compare
 * @param str2 second string to compare
 * @return true is strings are equal, false otherwise
 */
bool stringCompareI(const std::string& str1, const std::string& str2);

/**
 * Convert string to upper case
 *
 * @param str string to upper case
 * @return copy of string converted to upper case
 */
std::string toUpper(const std::string& str);

/**
 * Convert string to lower case
 *
 * @param str string to lower case
 * @return copy of string converted to lower case
 */
std::string toLower(const std::string& str);

/**
 * Convert string to bool
 *
 * @param str string to convert to bool
 * @return bool conversion of string
 */
bool stringToBool(const std::string& str);

} /* namespace common */
} /* namespace offcenter */



#endif /* OFFCENTER_COMMON_UTILITY_HPP_ */
