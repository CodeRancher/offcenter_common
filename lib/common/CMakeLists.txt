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

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_compile_definitions(ELPP_THREAD_SAFE)

add_library(offcenter_common STATIC)

set(version 0.0.1)
set_property(TARGET offcenter_common PROPERTY VERSION ${version})
set_property(TARGET offcenter_common PROPERTY SOVERSION 0)
set_property(TARGET offcenter_common PROPERTY INTERFACE_OffcenterCommon_MAJOR_VERSION 0)
set_property(TARGET offcenter_common APPEND PROPERTY COMPATIBLE_INTERFACE_STRING OffcenterCommon_MAJOR_VERSION)

target_sources(offcenter_common
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

target_include_directories(offcenter_common
	PUBLIC
		"$<BUILD_INTERFACE:${CMAKE_CURRENT_LIST_DIR}/include>"
		"$<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>"

		"$<BUILD_INTERFACE:${EASYLOGGINGPP_INCLUDE_DIR}>"
		

#	SYSTEM
#		${ACTIVEMQCPP_INCLUDE_DIR}
#		${APR_INCLUDE_DIR}
)

target_link_libraries(offcenter_common
	Boost::iostreams
	Boost::headers
	${BZIP2_LIBRARIES}
	${MPFR_LIBRARIES}
	${GMP_LIBRARIES}
	${EASYLOGGINGPP_LIBRARY}
)

#install(TARGETS offcenter_common EXPORT offcenter_common DESTINATION lib)
#install (
#	DIRECTORY ${CMAKE_CURRENT_LIST_DIR}/include/
#	DESTINATION include
#	FILES_MATCHING PATTERN "*.h*"
#)

if(ENABLE_UNIT_TESTS)
	add_subdirectory(test)
endif()
add_subdirectory(sandbox)
