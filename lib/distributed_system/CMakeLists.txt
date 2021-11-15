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
# @date   01-28-2019
#

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(LIBS offcenter_common)

add_compile_definitions(ELPP_THREAD_SAFE)

add_library(offcenter_common_distributedsystem STATIC)

set(version 0.0.1)
set_property(TARGET offcenter_common_distributedsystem PROPERTY VERSION ${version})
set_property(TARGET offcenter_common_distributedsystem PROPERTY SOVERSION 0)
set_property(TARGET offcenter_common_distributedsystem PROPERTY INTERFACE_OandaCommonDistributedSystem_MAJOR_VERSION 0)
set_property(TARGET offcenter_common_distributedsystem APPEND PROPERTY COMPATIBLE_INTERFACE_STRING OandaCommonDistributedSystem_MAJOR_VERSION)

target_sources(offcenter_common_distributedsystem
	PRIVATE
		${CMAKE_CURRENT_LIST_DIR}/src/ConsumerDataManager.cpp
	PUBLIC
		$<BUILD_INTERFACE:${CMAKE_CURRENT_LIST_DIR}/include/offcenter/distributedsystem/ConsumerDataListener.hpp>
		$<INSTALL_INTERFACE:include/offcenter/distributedsystem/ConsumerDataListener.hpp>

		$<BUILD_INTERFACE:${CMAKE_CURRENT_LIST_DIR}/include/offcenter/distributedsystem/ConsumerDataManager.hpp>
		$<INSTALL_INTERFACE:include/offcenter/distributedsystem/ConsumerDataManager.hpp>
		
)

target_include_directories(offcenter_common_distributedsystem
	PUBLIC
		"$<BUILD_INTERFACE:${CMAKE_CURRENT_LIST_DIR}/include>"
		"$<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>"

)

#install(TARGETS offcenter_common_distributedsystem EXPORT offcenter_common_distributedsystem DESTINATION lib)
#install (
#	DIRECTORY ${CMAKE_CURRENT_LIST_DIR}/include/
#	DESTINATION include
#	FILES_MATCHING PATTERN "*.h*"
#)

if(ENABLE_UNIT_TESTS)
	add_subdirectory(test)
endif()


