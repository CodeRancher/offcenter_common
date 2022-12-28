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
 * @file   ImPlotLineExampleApp.cpp
 * @author Scott Brauer
 * @date   12-02-2021
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

#include "ImPlotLineExampleApp.hpp"



ImPlotLineExampleApp::ImPlotLineExampleApp():
IImGuiApp(),
m_clearColor(ImVec4(0.45f, 0.55f, 0.60f, 1.00f))
{

}

ImPlotLineExampleApp::~ImPlotLineExampleApp() {
	// TODO Auto-generated destructor stub
}

void ImPlotLineExampleApp::onInitProgramOptions(
		offcenter::common::program_options::ProgramOptionsManager &optionsManager)
{
	m_imguiOption = optionsManager.add<ImGuiExampleProgramOptions>();
}

void ImPlotLineExampleApp::onSetUp()
{
	ImPlot::CreateContext();
}

void ImPlotLineExampleApp::onExecute()
{

}
void ImPlotLineExampleApp::onExecute(GLFWwindow* window)
{
	static float xs1[1001], ys1[1001];
	for (int i = 0; i < 1001; ++i) {
		xs1[i] = i * 0.001f;
		ys1[i] = 0.5f + 0.5f * sinf(50 * (xs1[i] + (float)ImGui::GetTime() / 10));
	}

	int w, h;
	glfwGetWindowSize(window, &w, &h);
	ImGui::SetNextWindowSize(ImVec2(w, h));
	ImGui::SetNextWindowPos({0,0});

	ImGui::Begin("ImGraph",nullptr,ImGuiWindowFlags_NoCollapse|ImGuiWindowFlags_NoTitleBar|ImGuiWindowFlags_NoResize);

	ImGui::SameLine();
	ImGui::BulletText("Anti-aliasing can be enabled from the plot's context menu (see Help).");

	if (ImPlot::BeginPlot("##Plot", ImVec2(-1,-1))) {
		ImPlot::SetupAxes(0, 0, ImPlotAxisFlags_NoInitialFit, ImPlotAxisFlags_NoInitialFit);
		//ImPlot::SetupAxisLimits(ImAxis_X1, data.time[0], data.time.back());
		//ImPlot::SetupAxisFormat(ImAxis_Y1, "$%.0f");

	//if (ImPlot::BeginPlot("##Plot", 0, 0, ImVec2(-1,-1), 0, ImPlotAxisFlags_NoInitialFit, ImPlotAxisFlags_NoInitialFit)) {
		ImPlot::SetNextLineStyle(ImVec4(1,0.75f,0,1));
		ImPlot::PlotLine("sin(x)", xs1, ys1, 1001);
		ImPlot::EndPlot();
	}
	ImGui::End();
}


void ImPlotLineExampleApp::onTearDown()
{
	ImPlot::DestroyContext();
}

void ImPlotLineExampleApp::onHelp(const std::string &help)
{

}

void ImPlotLineExampleApp::onVersion()
{
}
