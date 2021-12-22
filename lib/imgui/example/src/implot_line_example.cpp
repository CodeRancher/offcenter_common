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
 * @file   imgui_example.cpp
 * @author Scott Brauer
 * @date   12-01-2021
 */

#include <iostream>

#include "easylogging++.h"

INITIALIZE_EASYLOGGINGPP

#include "offcenter/common/imgui/ImGuiAppManager.hpp"
#include "offcenter/common/framework/application/Utility.hpp"

#include "ImPlotLineExampleApp.hpp"
#include "imgui_main.hpp"

int main(int argc, char **argv)
{
	START_EASYLOGGINGPP(argc, argv);

	imgui_main<ImPlotLineExampleApp>(argc, argv, "ImPlot Line Example", "ImGuiLineExampleApp");
}
