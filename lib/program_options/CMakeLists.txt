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

add_library(offcenter_common_program_options "")

set(version 0.0.1)
set_property(TARGET offcenter_common_program_options PROPERTY VERSION ${version})
set_property(TARGET offcenter_common_program_options PROPERTY SOVERSION 0)
set_property(TARGET offcenter_common_program_options PROPERTY INTERFACE_OandaCommonProgramOptions_MAJOR_VERSION 0)
set_property(TARGET offcenter_common_program_options APPEND PROPERTY COMPATIBLE_INTERFACE_STRING OandaCommonProgramOptions_MAJOR_VERSION)

target_sources(offcenter_common_program_options
	PRIVATE
		${CMAKE_CURRENT_LIST_DIR}/src/offcenter_program_options.cpp
	PUBLIC
		$<BUILD_INTERFACE:${CMAKE_CURRENT_LIST_DIR}/include/offcenter/common/program_options/ProgramOptionsManager.hpp>
		$<INSTALL_INTERFACE:include/offcenter/common/program_options/ProgramOptionsManager.hpp>
		
		$<BUILD_INTERFACE:${CMAKE_CURRENT_LIST_DIR}/include/offcenter/common/program_options/ProgramOptionsGroup.hpp>
		$<INSTALL_INTERFACE:include/offcenter/common/program_options/ProgramOptionsGroup.hpp>
		
		$<BUILD_INTERFACE:${CMAKE_CURRENT_LIST_DIR}/include/offcenter/common/program_options/IProgramOptionsGroup.hpp>
		$<INSTALL_INTERFACE:include/offcenter/common/program_options/IProgramOptionsGroup.hpp>
		
)

#install(TARGETS offcenter_common_program_options EXPORT offcenter_common_program_options DESTINATION lib)
#install (
#	DIRECTORY ${CMAKE_CURRENT_LIST_DIR}/include/
#	DESTINATION include
#	FILES_MATCHING PATTERN "*.h*"
#)
target_include_directories(offcenter_common_amqp
	PUBLIC
		"$<BUILD_INTERFACE:${CMAKE_CURRENT_LIST_DIR}/include>"
		"$<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>"

#	SYSTEM
#		${ACTIVEMQCPP_INCLUDE_DIR}
#		${APR_INCLUDE_DIR}
)


if(ENABLE_UNIT_TESTS)
	add_subdirectory(test)
endif()

add_subdirectory(example)
