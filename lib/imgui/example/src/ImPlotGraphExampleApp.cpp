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
 * @file   AmqpConsumerExampleApp.cpp
 * @author Scott Brauer
 * @date   04-15-2021
 */

#include <iostream>
#include <regex>

#include "imgui.h"
#include "implot.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#if defined(IMGUI_IMPL_OPENGL_ES2)
	#include <GLES2/gl2.h>
#endif
#include <GLFW/glfw3.h> // Will drag system OpenGL headers

#if defined(_MSC_VER) && (_MSC_VER >= 1900) && !defined(IMGUI_DISABLE_WIN32_FUNCTIONS)
	#pragma comment(lib, "legacy_stdio_definitions")
#endif

#include "easylogging++.h"

#include "ImPlotGraphExampleApp.hpp"



ImPlotGraphExampleApp::ImPlotGraphExampleApp():
	IImGuiApp(),
	m_clearColor(ImVec4(0.45f, 0.55f, 0.60f, 1.00f))
{

}

ImPlotGraphExampleApp::~ImPlotGraphExampleApp() {
	// TODO Auto-generated destructor stub
}

void ImPlotGraphExampleApp::onInitProgramOptions(
		program_options::ProgramOptionsManager &optionsManager)
{
	m_imguiOption = optionsManager.add<ImGuiExampleProgramOptions>();
}

void ImPlotGraphExampleApp::onSetUp()
{
    ImPlot::CreateContext();
}

void ImPlotGraphExampleApp::onExecute()
{

}
void ImPlotGraphExampleApp::onExecute(GLFWwindow* window)
{
	ImPlot::ShowDemoWindow();
}


void ImPlotGraphExampleApp::onTearDown()
{
    ImPlot::DestroyContext();
}

void ImPlotGraphExampleApp::onHelp(const std::string &help)
{

}

void ImPlotGraphExampleApp::onVersion()
{
}
