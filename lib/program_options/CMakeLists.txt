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

include(OffcenterBuild)

offcenter_cxx()
offcenter_elpp()
offcenter_lib_setup(offcenter_common_program_options common_program_options)
set(version 0.0.1)

add_library(${LIB_NAME} STATIC)

target_sources(${LIB_NAME}
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

target_include_directories(${LIB_NAME}
	PUBLIC
		"$<BUILD_INTERFACE:${CMAKE_CURRENT_LIST_DIR}/include>"
		"$<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>"
)

include(OffcenterInstall)
offcenter_lib_install()

if(ENABLE_UNIT_TESTS)
	add_subdirectory(test)
endif()

add_subdirectory(example)
