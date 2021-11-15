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
# @date   03-23-2021
#

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_compile_definitions(ELPP_THREAD_SAFE)
add_compile_definitions(ELPP_FRESH_LOG_FILE)
add_compile_definitions(ELPP_NO_DEFAULT_LOG_FILE)

add_executable(offcenter_soci_tests
	${CMAKE_CURRENT_LIST_DIR}/src/main.cpp
	${CMAKE_CURRENT_LIST_DIR}/src/mysql_options_test.cpp
	${CMAKE_CURRENT_LIST_DIR}/src/mysql_program_options_test.cpp
	${CMAKE_CURRENT_LIST_DIR}/src/soci_session_test.cpp
	${CMAKE_CURRENT_LIST_DIR}/src/globalvariables.cpp
)

target_link_libraries(offcenter_soci_tests
	offcenter_common_soci
	GTest::gtest
	${EASYLOGGINGPP_LIBRARY}
	${SOCI_mysql_PLUGIN}
	${SOCI_LIBRARY}
	MariaDBClient::MariaDBClient
	Boost::program_options
	Threads::Threads
	${CMAKE_DL_LIBS}
)

target_include_directories(offcenter_soci_tests
	PUBLIC
		${CMAKE_CURRENT_LIST_DIR}/include
		${CMAKE_CURRENT_LIST_DIR}/../include
		${CMAKE_CURRENT_LIST_DIR}/../../program_options/include
		${CMAKE_CURRENT_LIST_DIR}/../../common/include

	SYSTEM
		${EASYLOGGINGPP_INCLUDE_DIR}
		${MariaDBClient_INCLUDE_DIRS}
)

gtest_discover_tests(offcenter_soci_tests)

add_test(NAME monolithic COMMAND offcenter_soci_tests)

