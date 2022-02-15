/**
 * Copyright 2022 Scott Brauer
 *
 * Licensed under the Apache License, Version 2.0 (the );
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
 * @file   app_manager.cpp
 * @author Scott Brauer
 * @date   01-23-2022
 */

#include <iostream>

#include "easylogging++.h"

INITIALIZE_EASYLOGGINGPP

#include "offcenter/common/framework/application/AppManager.hpp"
#include "offcenter/common/framework/application/BasicAppConfig.hpp"
#include "offcenter/common/framework/application/Utility.hpp"
#include "offcenter/common/framework/application/framework_application_main.hpp"
#include "offcenter/common/app_manager/AppManagerApp.hpp"

int main(int argc, char **argv)
{
	START_EASYLOGGINGPP(argc, argv);

	framework_application_main<offcenter::common::appmanager::AppManagerApp>(argc, argv, "Application Manager", "AppManagerApp");
}

