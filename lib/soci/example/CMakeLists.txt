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
# @date   03-29-2021
#

offcenter_cxx()
offcenter_elpp()

###############################################################################
offcenter_example_constants(soci_create_simple_db)
add_executable(${EXE_NAME}
	${CMAKE_CURRENT_LIST_DIR}/src/soci_create_simple_db.cpp
)

target_link_libraries(${EXE_NAME}
	offcenter_common_framework
	offcenter_common_soci
	Boost::program_options
	${EASYLOGGINGPP_LIBRARY}
	${SOCI_mysql_PLUGIN}
	${SOCI_LIBRARY}
	MariaDBClient::MariaDBClient
	${CMAKE_DL_LIBS}
	Threads::Threads
)

target_include_directories(${EXE_NAME}
	BEFORE PUBLIC
		"$<BUILD_INTERFACE:${CMAKE_CURRENT_LIST_DIR}/include>"
		"$<BUILD_INTERFACE:${CMAKE_CURRENT_LIST_DIR}/../include>"
		"$<BUILD_INTERFACE:${CMAKE_CURRENT_LIST_DIR}/../../common/include>"
		"$<BUILD_INTERFACE:${CMAKE_CURRENT_LIST_DIR}/../../framework/include>"
		"$<BUILD_INTERFACE:${CMAKE_CURRENT_LIST_DIR}/../../program_options/include>"
		"$<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>"

	SYSTEM PRIVATE
		${EASYLOGGINGPP_INCLUDE_DIR}
		${MariaDBClient_INCLUDE_DIRS}
		${SOCI_INCLUDE_DIR}/..
)

offcenter_example()
