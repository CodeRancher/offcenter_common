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
 * @file   ImGuiException.hpp
 * @author Scott Brauer
 * @date   12-01-2021
 */

#ifndef OFFCENTER_COMMON_IMGUI_IMGUIEXCEPTION_HPP_
#define OFFCENTER_COMMON_IMGUI_IMGUIEXCEPTION_HPP_

#include "offcenter/common/RuntimeException.hpp"

namespace offcenter {
namespace common {
namespace imgui {

class ImGuiException:
		public RuntimeException
{
public:
	explicit ImGuiException(const std::string& what_arg):
		RuntimeException(what_arg)
	{}

	explicit ImGuiException(const char* what_arg):
		RuntimeException(what_arg)
	{}

	virtual ~ImGuiException()
	{}
};

} /* namespace imgui */
} /* namespace common */
} /* namespace offcenter */

#endif /* OFFCENTER_COMMON_IMGUI_IMGUIEXCEPTION_HPP_ */
