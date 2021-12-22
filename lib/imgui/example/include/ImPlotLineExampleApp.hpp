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
 * @file   ImGuiExampleApp.hpp
 * @author Scott Brauer
 * @date   04-15-2021
 */

#ifndef IMPLOTGRAPHEXAMPLEAPP_HPP_
#define IMPLOTGRAPHEXAMPLEAPP_HPP_

#include "offcenter/common/program_options/ProgramOptionsManager.hpp"

#include "offcenter/common/imgui/IImGuiApp.hpp"

#include "ImGuiProgramOptions.hpp"

/**
 *
 */
class ImPlotLineExampleApp: public offcenter::common::imgui::IImGuiApp {
public:
	explicit ImPlotLineExampleApp();
	virtual ~ImPlotLineExampleApp();

	void onInitProgramOptions(offcenter::common::program_options::ProgramOptionsManager& optionsManager) override;
	void onSetUp() override;
	void onExecute() override;
	void onExecute(GLFWwindow* window) override;
	void onTearDown() override;
	void onHelp(const std::string& help) override;
	void onVersion() override;

private:
	ImGuiExampleProgramOptions::ConfigPtr m_imguiOption;
    ImVec4 m_clearColor;
};

#endif /* IMPLOTGRAPHEXAMPLEAPP_HPP_ */
