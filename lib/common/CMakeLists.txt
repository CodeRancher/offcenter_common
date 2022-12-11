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
# @date   04-07-2019
#

include(OffcenterBuild)

offcenter_cxx()
offcenter_elpp()
offcenter_lib_setup(offcenter_common common)
set(version 0.0.1)

add_library(${LIB_NAME} STATIC)

target_sources(${LIB_NAME}
	PRIVATE
		${CMAKE_CURRENT_LIST_DIR}/src/DateTime.cpp
		${CMAKE_CURRENT_LIST_DIR}/src/Utility.cpp
		${CMAKE_CURRENT_LIST_DIR}/src/Processes.cpp
		${CMAKE_CURRENT_LIST_DIR}/src/Conversions.cpp
	PUBLIC
		$<BUILD_INTERFACE:${CMAKE_CURRENT_LIST_DIR}/include/offcenter/common/ScopeGuard.hpp>
		$<INSTALL_INTERFACE:include/offcenter/common/ScopeGuard.hpp>
		
		$<BUILD_INTERFACE:${CMAKE_CURRENT_LIST_DIR}/include/offcenter/common/SimulatedCommandLine.hpp>
		$<INSTALL_INTERFACE:include/offcenter/common/SimulatedCommandLine.hpp>

		$<BUILD_INTERFACE:${CMAKE_CURRENT_LIST_DIR}/include/offcenter/common/WaitForMessage.hpp>
		$<INSTALL_INTERFACE:include/offcenter/common/WaitForMessage.hpp>
	
		$<BUILD_INTERFACE:${CMAKE_CURRENT_LIST_DIR}/include/offcenter/common/Utility.hpp>
		$<INSTALL_INTERFACE:include/offcenter/common/Utility.hpp>
	
		$<BUILD_INTERFACE:${CMAKE_CURRENT_LIST_DIR}/include/offcenter/common/DateTime.hpp>
		$<INSTALL_INTERFACE:include/offcenter/common/DateTime.hpp>
	
		$<BUILD_INTERFACE:${CMAKE_CURRENT_LIST_DIR}/include/offcenter/common/DateTimeInterval.hpp>
		$<INSTALL_INTERFACE:include/offcenter/common/DateTimeInterval.hpp>
	
		$<BUILD_INTERFACE:${CMAKE_CURRENT_LIST_DIR}/include/offcenter/common/Conversions.hpp>
		$<INSTALL_INTERFACE:include/offcenter/common/Conversions.hpp>
)

target_include_directories(${LIB_NAME}
	PUBLIC
		"$<BUILD_INTERFACE:${CMAKE_CURRENT_LIST_DIR}/include>"
		"$<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>"

		"$<BUILD_INTERFACE:${EASYLOGGINGPP_INCLUDE_DIR}>"
)

#link_directories(${Boost_LIBRARY_DIRS})

target_link_libraries(${LIB_NAME}
	Boost::iostreams
	Boost::headers
	${BZIP2_LIBRARIES}
	${MPFR_LIBRARIES}
	${GMP_LIBRARIES}
	${EASYLOGGINGPP_LIBRARY}
)

include(OffcenterInstall)
offcenter_lib_install()

if(ENABLE_UNIT_TESTS)
	add_subdirectory(test)
endif()

add_subdirectory(sandbox)
