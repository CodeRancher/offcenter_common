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

offcenter_cxx()
offcenter_elpp()
offcenter_test_constants(offcenter_soci_tests)

add_executable(${EXE_NAME}
	${CMAKE_CURRENT_LIST_DIR}/src/main.cpp
	${CMAKE_CURRENT_LIST_DIR}/src/mysql_options_test.cpp
	${CMAKE_CURRENT_LIST_DIR}/src/mysql_program_options_test.cpp
	${CMAKE_CURRENT_LIST_DIR}/src/soci_session_test.cpp
	${CMAKE_CURRENT_LIST_DIR}/src/globalvariables.cpp
)

target_link_libraries(${EXE_NAME}
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

target_include_directories(${EXE_NAME}
	PUBLIC
		${CMAKE_CURRENT_LIST_DIR}/include
		${CMAKE_CURRENT_LIST_DIR}/../include
		${CMAKE_CURRENT_LIST_DIR}/../../program_options/include
		${CMAKE_CURRENT_LIST_DIR}/../../common/include

	SYSTEM PRIVATE
		${EASYLOGGINGPP_INCLUDE_DIR}
		${MariaDBClient_INCLUDE_DIRS}
)

offcenter_test()