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
 * @file   ImGuiAppManager.hpp
 * @author Scott Brauer
 * @date   12-01-2021
 */

#ifndef OffcenterCommon_IMGUI_IMGUIAPPMANAGER_HPP_
#define OffcenterCommon_IMGUI_IMGUIAPPMANAGER_HPP_

#include "imgui.h"
#include "implot.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include <stdio.h>
#if defined(IMGUI_IMPL_OPENGL_ES2)
	#include <GLES2/gl2.h>
#endif
#include <GLFW/glfw3.h> // Will drag system OpenGL headers

#if defined(_MSC_VER) && (_MSC_VER >= 1900) && !defined(IMGUI_DISABLE_WIN32_FUNCTIONS)
	#pragma comment(lib, "legacy_stdio_definitions")
#endif

#include "offcenter/common/framework/application/AppManager.hpp"
#include "offcenter/common/imgui/ImGuiException.hpp"

namespace offcenter {
namespace common {
namespace imgui {

static void glfw_error_callback(int error, const char* description)
{
    std::cerr << "Glfw Error " << error << ": " << description;
}

template <class IApp>
class ImGuiAppManager:
		public offcenter::common::framework::application::AppManager<IApp>
{
public:
	using Parent = offcenter::common::framework::application::AppManager<IApp>;

public:
	explicit ImGuiAppManager():
		Parent(),
		m_window(nullptr),
		m_clearColor(ImVec4(0.45f, 0.55f, 0.60f, 1.00f))
	{}

	virtual ~ImGuiAppManager() = default;

	void onSetUp() override {
	    // Setup window
	    glfwSetErrorCallback(glfw_error_callback);
	    if (!glfwInit()) {
	        throw offcenter::common::imgui::ImGuiException("Could not initialize glfw");
	    }

	    // Decide GL+GLSL versions
	#if defined(IMGUI_IMPL_OPENGL_ES2)
	    // GL ES 2.0 + GLSL 100
	    const char* glsl_version = "#version 100";
	    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 2);
	    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
	    glfwWindowHint(GLFW_CLIENT_API, GLFW_OPENGL_ES_API);
	#elif defined(__APPLE__)
	    // GL 3.2 + GLSL 150
	    const char* glsl_version = "#version 150";
	    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
	    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);  // 3.2+ only
	    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);            // Required on Mac
	#else
	    // GL 3.0 + GLSL 130
	    const char* glsl_version = "#version 130";
	    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
	    //glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);  // 3.2+ only
	    //glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);            // 3.0+ only
	#endif

	    // Create window with graphics context
	    m_window = glfwCreateWindow(1280, 720, Parent::m_app.windowTitle().c_str(), NULL, NULL);
	    if (m_window == NULL) {
	        throw offcenter::common::imgui::ImGuiException("Could not glfw window");
	    }
	    glfwMakeContextCurrent(m_window);
	    glfwSwapInterval(1); // Enable vsync

	    // Setup Dear ImGui context
	    IMGUI_CHECKVERSION();
	    ImGui::CreateContext();
	    ImGuiIO& io = ImGui::GetIO(); (void)io;
	    //io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
	    //io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls

	    // Setup Dear ImGui style
	    ImGui::StyleColorsDark();
	    //ImGui::StyleColorsClassic();

	    // Setup Platform/Renderer backends
	    ImGui_ImplGlfw_InitForOpenGL(m_window, true);
	    ImGui_ImplOpenGL3_Init(glsl_version);

	    // Load Fonts
	    // - If no fonts are loaded, dear imgui will use the default font. You can also load multiple fonts and use ImGui::PushFont()/PopFont() to select them.
	    // - AddFontFromFileTTF() will return the ImFont* so you can store it if you need to select the font among multiple.
	    // - If the file cannot be loaded, the function will return NULL. Please handle those errors in your application (e.g. use an assertion, or display an error and quit).
	    // - The fonts will be rasterized at a given size (w/ oversampling) and stored into a texture when calling ImFontAtlas::Build()/GetTexDataAsXXXX(), which ImGui_ImplXXXX_NewFrame below will call.
	    // - Read 'docs/FONTS.md' for more instructions and details.
	    // - Remember that in C/C++ if you want to include a backslash \ in a string literal you need to write a double backslash \\ !
	    //io.Fonts->AddFontDefault();
	    //io.Fonts->AddFontFromFileTTF("../../misc/fonts/Roboto-Medium.ttf", 16.0f);
	    //io.Fonts->AddFontFromFileTTF("../../misc/fonts/Cousine-Regular.ttf", 15.0f);
	    //io.Fonts->AddFontFromFileTTF("../../misc/fonts/DroidSans.ttf", 16.0f);
	    //io.Fonts->AddFontFromFileTTF("../../misc/fonts/ProggyTiny.ttf", 10.0f);
	    //ImFont* font = io.Fonts->AddFontFromFileTTF("c:\\Windows\\Fonts\\ArialUni.ttf", 18.0f, NULL, io.Fonts->GetGlyphRangesJapanese());
	    //IM_ASSERT(font != NULL);

	    Parent::m_app.onSetUp();

	}

	void onExecute() override {
	    // Main loop
	    while (!glfwWindowShouldClose(m_window))
	    {
			// Poll and handle events (inputs, window resize, etc.)
			// You can read the io.WantCaptureMouse, io.WantCaptureKeyboard flags to tell if dear imgui wants to use your inputs.
			// - When io.WantCaptureMouse is true, do not dispatch mouse input data to your main application.
			// - When io.WantCaptureKeyboard is true, do not dispatch keyboard input data to your main application.
			// Generally you may always pass all inputs to dear imgui, and hide them from your application based on those two flags.
			glfwPollEvents();

			// Start the Dear ImGui frame
			ImGui_ImplOpenGL3_NewFrame();
			ImGui_ImplGlfw_NewFrame();
			ImGui::NewFrame();

			Parent::m_app.onExecute(m_window);

			// Rendering
			ImGui::Render();
			int display_w, display_h;
			glfwGetFramebufferSize(m_window, &display_w, &display_h);
			glViewport(0, 0, display_w, display_h);
			glClearColor(m_clearColor.x * m_clearColor.w, m_clearColor.y * m_clearColor.w, m_clearColor.z * m_clearColor.w, m_clearColor.w);
			glClear(GL_COLOR_BUFFER_BIT);
			ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

			glfwSwapBuffers(m_window);
	    }
	}

	void onTearDown() override{
		Parent::m_app.onTearDown();

	    // Cleanup
	    ImGui_ImplOpenGL3_Shutdown();
	    ImGui_ImplGlfw_Shutdown();
	    ImGui::DestroyContext();

	    glfwDestroyWindow(m_window);
	    glfwTerminate();

	}

private:
    GLFWwindow* m_window;
    ImVec4 m_clearColor;
};

} /* namespace imgui */
} /* namespace common */
} /* namespace offcenter */

#endif /* OffcenterCommon_IMGUI_IMGUIAPPMANAGER_HPP_ */
