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
# @date   04-11-2019
#

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_compile_definitions(ELPP_THREAD_SAFE)
add_compile_definitions(ELPP_FRESH_LOG_FILE)
add_compile_definitions(ELPP_NO_DEFAULT_LOG_FILE)

set(EXE_NAME "${TEST_PREFIX}.${PROJECT_NAME}.common")

add_executable(${EXE_NAME}
	${CMAKE_CURRENT_LIST_DIR}/src/main.cpp
	${CMAKE_CURRENT_LIST_DIR}/src/test_simulated_command_line.cpp
	${CMAKE_CURRENT_LIST_DIR}/src/date_time_test.cpp
	${CMAKE_CURRENT_LIST_DIR}/src/date_time_interval_test.cpp
	${CMAKE_CURRENT_LIST_DIR}/src/conversion_test.cpp
)

set_target_properties(${EXE_NAME}
	PROPERTIES
		RUNTIME_OUTPUT_DIRECTORY ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${CMAKE_INSTALL_TEST_DIR}
)

target_link_libraries(${EXE_NAME}
	offcenter_common
	Boost::iostreams
	Boost::headers
	GTest::gtest
	${BZIP2_LIBRARIES}
	${MPFR_LIBRARIES}
	${GMP_LIBRARIES}
	${EASYLOGGINGPP_LIBRARY}
)

target_include_directories(${EXE_NAME}
	PUBLIC
		${EASYLOGGINGPP_INCLUDE_DIR}
)

gtest_discover_tests(${EXE_NAME})

add_test(NAME monolithic COMMAND ${EXE_NAME})
