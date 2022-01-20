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
# @date   04-14-2019
#

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_compile_definitions(ELPP_THREAD_SAFE)
add_compile_definitions(ELPP_FRESH_LOG_FILE)
add_compile_definitions(ELPP_NO_DEFAULT_LOG_FILE)

add_executable(${TEST_PREFIX}.${PROJECT_NAME}.program_options
	main.cpp
	#test_single_program_option.cpp
	#test_double_program_option.cpp
	test_double_program_option_group.cpp
	test_positional_option_group.cpp
)

set_target_properties(${TEST_PREFIX}.${PROJECT_NAME}.program_options
	PROPERTIES
		RUNTIME_OUTPUT_DIRECTORY ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${CMAKE_INSTALL_TEST_DIR}
)

target_link_libraries(${TEST_PREFIX}.${PROJECT_NAME}.program_options
	GTest::gtest
	Boost::program_options
)

target_include_directories(${TEST_PREFIX}.${PROJECT_NAME}.program_options
	PUBLIC
		${CMAKE_CURRENT_LIST_DIR}/../include
		${CMAKE_CURRENT_LIST_DIR}/../../common/include
)

gtest_discover_tests(${TEST_PREFIX}.${PROJECT_NAME}.program_options)

add_test(NAME monolithic COMMAND ${TEST_PREFIX}.${PROJECT_NAME}.program_options)
