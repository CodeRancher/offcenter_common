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
# @date   11-11-2019
#

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_compile_definitions(ELPP_THREAD_SAFE)
add_compile_definitions(ELPP_FRESH_LOG_FILE)
add_compile_definitions(ELPP_NO_DEFAULT_LOG_FILE)

add_executable(
	offcenter_common_distributedsystem_tests
	src/main.cpp
	src/simple_consumerdata_test.cpp
	src/SimpleConsumerDataFixture.cpp
	src/triple_call_consumerdata_test.cpp
)

target_link_libraries(offcenter_common_distributedsystem_tests
	offcenter_common_distributedsystem
	GTest::gtest
	${EASYLOGGINGPP_LIBRARY}
	${ACTIVEMQCPP_LIBRARIES}
	#${APR_LIBRARIES}
	Threads::Threads
)

target_include_directories(offcenter_common_distributedsystem_tests
	PUBLIC
		${CMAKE_CURRENT_LIST_DIR}/include
		${CMAKE_CURRENT_LIST_DIR}/../include
		${CMAKE_CURRENT_LIST_DIR}/../../amqp/include
		${CMAKE_CURRENT_LIST_DIR}/../../common/include
		
		"$<BUILD_INTERFACE:${ACTIVEMQCPP_INCLUDE_DIR}>"

		${EASYLOGGINGPP_INCLUDE_DIR}
		
)

gtest_discover_tests(offcenter_common_distributedsystem_tests)

add_test(NAME monolithic COMMAND offcenter_common_distributedsystem_tests)