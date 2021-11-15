#
# Copyright 2021 Scott Brauer
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
#     http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an  BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.
#
#
#
# @file   CMakeLists.txt
# @author Scott Brauer
# @date   04-13-2021
#

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable (offcenter_rest_server_example
    ${CMAKE_CURRENT_LIST_DIR}/src/main.cpp
    ${CMAKE_CURRENT_LIST_DIR}/src/RestServerExampleApp.cpp
)

target_link_libraries(offcenter_rest_server_example
	offcenter_common_framework
	offcenter_common
	offcenter_common_program_options
	offcenter_common_restserver
	Boost::program_options
	${EASYLOGGINGPP_LIBRARY}
	cpprestsdk::cpprest
	nlohmann_json::nlohmann_json
	Threads::Threads
)

target_include_directories(offcenter_rest_server_example
	BEFORE PUBLIC
		${CMAKE_CURRENT_LIST_DIR}/include
		#${CMAKE_CURRENT_LIST_DIR}/../include
		#${CMAKE_CURRENT_LIST_DIR}/../../framework/include
		#${CMAKE_CURRENT_LIST_DIR}/../../program_options/include
		#${CMAKE_CURRENT_LIST_DIR}/../../common/include
	SYSTEM
		${EASYLOGGINGPP_INCLUDE_DIR}
)

