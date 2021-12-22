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
 * @file   IImGuiApp.hpp
 * @author Scott Brauer
 * @date   12-01-2021
 */

#ifndef OFFCENTER_COMMON_IMGUI_IIMGUIAPP_HPP_
#define OFFCENTER_COMMON_IMGUI_IIMGUIAPP_HPP_

#include <GLFW/glfw3.h> // Will drag system OpenGL headers

#include "offcenter/common/framework/application/IApp.hpp"

namespace offcenter {
namespace common {
namespace imgui {

class IImGuiApp:
		public offcenter::common::framework::application::IApp
{
public:
	virtual ~IImGuiApp() = default;

	virtual std::string windowTitle() { return ""; }
	virtual void onExecute(GLFWwindow* window) {}
};

} /* namespace imgui */
} /* namespace common */
} /* namespace offcenter */

#endif /* OFFCENTER_COMMON_IMGUI_IIMGUIAPP_HPP_ */
