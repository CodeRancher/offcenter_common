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
# @date   05-02-2019
#

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_compile_definitions(ELPP_THREAD_SAFE)

add_compile_definitions(CONFIGFILE_EMPTY="${CMAKE_CURRENT_LIST_DIR}/data/config_empty.cfg")
add_compile_definitions(CONFIGFILE_BASIC="${CMAKE_CURRENT_LIST_DIR}/data/config_basic.cfg")

add_executable(offcenter_common_rest_server_tests
	${CMAKE_CURRENT_LIST_DIR}/src/main.cpp
	${CMAKE_CURRENT_LIST_DIR}/src/test_auto_method_path.cpp
	${CMAKE_CURRENT_LIST_DIR}/src/test_auto_method_handler.cpp
)

target_link_libraries(offcenter_common_rest_server_tests
	GTest::gtest
	offcenter_common_framework
	offcenter_common_restserver
	Boost::program_options
	cpprestsdk::cpprest
	Threads::Threads
	${Boost_LIBRARIES}
)

target_include_directories(offcenter_common_rest_server_tests
	PUBLIC
		${CMAKE_CURRENT_LIST_DIR}/include
		${CMAKE_CURRENT_LIST_DIR}/../include
		${CMAKE_CURRENT_LIST_DIR}/../../common/include
		${CMAKE_CURRENT_LIST_DIR}/../../program_options/include
	SYSTEM INTERFACE
		${ACTIVEMQCPP_INCLUDE_DIR}
		${APR_INCLUDE_DIR}
)

gtest_discover_tests(offcenter_common_rest_server_tests)

add_test(NAME monolithic COMMAND offcenter_common_rest_server_tests)

