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

include(OffcenterBuild)

offcenter_cxx()
offcenter_elpp()
offcenter_lib_setup(offcenter_common_soci common_soci)
set(version 0.0.1)

add_library(${LIB_NAME} STATIC)

target_sources(${LIB_NAME}
	PRIVATE
		${CMAKE_CURRENT_LIST_DIR}/src/Session.cpp
		${CMAKE_CURRENT_LIST_DIR}/src/MySQLOptions.cpp
		${CMAKE_CURRENT_LIST_DIR}/src/Transaction.cpp
	PUBLIC
		$<BUILD_INTERFACE:${CMAKE_CURRENT_LIST_DIR}/include/offcenter/common/soci/Session.hpp>
		$<INSTALL_INTERFACE:include/offcenter/common/soci/Session.hpp>
		
		$<BUILD_INTERFACE:${CMAKE_CURRENT_LIST_DIR}/include/offcenter/common/soci/MySQLOptions.hpp>
		$<INSTALL_INTERFACE:include/offcenter/common/soci/MySQLOptions.hpp>
		
		$<BUILD_INTERFACE:${CMAKE_CURRENT_LIST_DIR}/include/offcenter/common/soci/Transaction.hpp>
		$<INSTALL_INTERFACE:include/offcenter/common/soci/Transaction.hpp>
		
)

target_link_libraries(${LIB_NAME}
	offcenter_common_threading
	${EASYLOGGINGPP_LIBRARY}
	${SOCI_mysql_PLUGIN}
	${SOCI_LIBRARY}
	${MariaDBClient_LIBRARIES}
)

target_include_directories(${LIB_NAME}
	PUBLIC
		"$<BUILD_INTERFACE:${CMAKE_CURRENT_LIST_DIR}/include>"
		"$<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>"
		
		"$<BUILD_INTERFACE:${SOCI_INCLUDE_DIR}/..>"
		"$<BUILD_INTERFACE:${MariaDBClient_INCLUDE_DIRS}>"
)

include(OffcenterInstall)
offcenter_lib_install()

if(ENABLE_UNIT_TESTS)
	add_subdirectory(test)
endif()

add_subdirectory(example)

