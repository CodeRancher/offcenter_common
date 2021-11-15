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
 * @file   FileException.hpp
 * @author Scott Brauer
 * @date   05-25-2019
 */

#ifndef OFFCENTER_COMMON_FILEEXCEPTION_HPP_
#define OFFCENTER_COMMON_FILEEXCEPTION_HPP_

#include "RuntimeException.hpp"

namespace offcenter {
namespace common {

class FileException:
		public RuntimeException
{
public:
	explicit FileException(const std::string& what_arg):
	RuntimeException(what_arg)
	{

	}

	explicit FileException(const char* what_arg):
		RuntimeException(what_arg)
	{

	}

	virtual ~FileException()
	{

	}
};

} /* namespace common */
} /* namespace offcenter */

#endif /* OFFCENTER_COMMON_FILEEXCEPTION_HPP_ */
