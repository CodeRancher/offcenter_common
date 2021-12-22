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

#include "ImGuiExampleApp.hpp"



ImGuiExampleApp::ImGuiExampleApp():
	IImGuiApp(),
    m_showDemoWindow(),
    m_showAnotherWindow(),
	m_clearColor(ImVec4(0.45f, 0.55f, 0.60f, 1.00f))
{

}

ImGuiExampleApp::~ImGuiExampleApp() {
	// TODO Auto-generated destructor stub
}

void ImGuiExampleApp::onInitProgramOptions(
		program_options::ProgramOptionsManager &optionsManager)
{
	m_imguiOption = optionsManager.add<ImGuiExampleProgramOptions>();
}

void ImGuiExampleApp::onSetUp()
{
}

void ImGuiExampleApp::onExecute()
{

}
void ImGuiExampleApp::onExecute(GLFWwindow* window)
{
     // 1. Show the big demo window (Most of the sample code is in ImGui::ShowDemoWindow()! You can browse its code to learn more about Dear ImGui!).
     if (m_showDemoWindow) {
         ImGui::ShowDemoWindow(&m_showDemoWindow);
     }

     // 2. Show a simple window that we create ourselves. We use a Begin/End pair to created a named window.
     {
         static float f = 0.0f;
         static int counter = 0;

         ImGui::Begin("Hello, world!");                          // Create a window called "Hello, world!" and append into it.

         ImGui::Text("This is some useful text.");               // Display some text (you can use a format strings too)
         ImGui::Checkbox("Demo Window", &m_showDemoWindow);      // Edit bools storing our window open/close state
         ImGui::Checkbox("Another Window", &m_showAnotherWindow);

         ImGui::SliderFloat("float", &f, 0.0f, 1.0f);            // Edit 1 float using a slider from 0.0f to 1.0f
         ImGui::ColorEdit3("clear color", (float*)&m_clearColor); // Edit 3 floats representing a color

         if (ImGui::Button("Button"))                            // Buttons return true when clicked (most widgets return true when edited/activated)
             counter++;
         ImGui::SameLine();
         ImGui::Text("counter = %d", counter);

         ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
         ImGui::End();
     }

     // 3. Show another simple window.
     if (m_showAnotherWindow)
     {
         ImGui::Begin("Another Window", &m_showAnotherWindow);   // Pass a pointer to our bool variable (the window will have a closing button that will clear the bool when clicked)
         ImGui::Text("Hello from another window!");
         if (ImGui::Button("Close Me"))
        	 m_showAnotherWindow = false;
         ImGui::End();
     }
}


void ImGuiExampleApp::onTearDown()
{
}

void ImGuiExampleApp::onHelp(const std::string &help)
{

}

void ImGuiExampleApp::onVersion()
{
}
