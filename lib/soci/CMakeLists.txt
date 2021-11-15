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

#set(LIBS offcenter_common)

#include(${CMAKE_CURRENT_LIST_DIR}/../../cmake/FindAPR.cmake)
#include(${CMAKE_CURRENT_LIST_DIR}/../../cmake/FindActiveMQcpp.cmake)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_compile_definitions(ELPP_THREAD_SAFE)

add_library(offcenter_common_soci "")

set(version 0.0.1)

set_property(TARGET offcenter_common_soci PROPERTY VERSION ${version})
set_property(TARGET offcenter_common_soci PROPERTY SOVERSION 0)
set_property(TARGET offcenter_common_soci PROPERTY INTERFACE_OffcenterCommonSOCI_MAJOR_VERSION 0)
set_property(TARGET offcenter_common_soci APPEND PROPERTY COMPATIBLE_INTERFACE_STRING OffcenterCommonSOCI_MAJOR_VERSION)

add_compile_definitions(ELPP_THREAD_SAFE)
add_compile_definitions(ELPP_FRESH_LOG_FILE)
add_compile_definitions(ELPP_NO_DEFAULT_LOG_FILE)

target_sources(offcenter_common_soci
	PRIVATE
		${CMAKE_CURRENT_LIST_DIR}/src/Session.cpp
		${CMAKE_CURRENT_LIST_DIR}/src/MySQLOptions.cpp
		${CMAKE_CURRENT_LIST_DIR}/src/Transaction.cpp
	PUBLIC
		$<BUILD_INTERFACE:${CMAKE_CURRENT_LIST_DIR}/include/offcenter/soci/Session.hpp>
		$<INSTALL_INTERFACE:include/offcenter/soci/Session.hpp>
		
		$<BUILD_INTERFACE:${CMAKE_CURRENT_LIST_DIR}/include/offcenter/soci/MySQLOptions.hpp>
		$<INSTALL_INTERFACE:include/offcenter/soci/MySQLOptions.hpp>
		
		$<BUILD_INTERFACE:${CMAKE_CURRENT_LIST_DIR}/include/offcenter/soci/Transaction.hpp>
		$<INSTALL_INTERFACE:include/offcenter/soci/Transaction.hpp>
		
)

target_link_libraries(offcenter_common_soci
	offcenter_common_threading
	${EASYLOGGINGPP_LIBRARY}
	${SOCI_mysql_PLUGIN}
	${SOCI_LIBRARY}
	${MariaDBClient_LIBRARIES}
)

target_include_directories(offcenter_common_soci
	PUBLIC
		"$<BUILD_INTERFACE:${CMAKE_CURRENT_LIST_DIR}/include>"
		"$<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>"
		
		"$<BUILD_INTERFACE:${SOCI_INCLUDE_DIR}/..>"
		"$<BUILD_INTERFACE:${MariaDBClient_INCLUDE_DIRS}>"
)

#install(TARGETS offcenter_common_soci EXPORT offcenter_common_soci DESTINATION lib)
#install (
#	DIRECTORY ${CMAKE_CURRENT_LIST_DIR}/include/
#	DESTINATION include
#	FILES_MATCHING PATTERN "*.h*"
#)

if(ENABLE_UNIT_TESTS)
	add_subdirectory(test)
endif()

add_subdirectory(example)

