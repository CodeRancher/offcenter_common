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

#set(LIBS offcenter_common)

#include(${CMAKE_CURRENT_LIST_DIR}/../../cmake/FindAPR.cmake)
#include(${CMAKE_CURRENT_LIST_DIR}/../../cmake/FindActiveMQcpp.cmake)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_compile_definitions(ELPP_THREAD_SAFE)
add_compile_definitions(ELPP_FRESH_LOG_FILE)
add_compile_definitions(ELPP_NO_DEFAULT_LOG_FILE)

add_library(offcenter_common_threading STATIC)

target_sources(offcenter_common_threading
	PRIVATE
		${CMAKE_CURRENT_LIST_DIR}/src/RunningThread.cpp
		${CMAKE_CURRENT_LIST_DIR}/src/RunningThreadBlockable.cpp
	PUBLIC
		$<BUILD_INTERFACE:${CMAKE_CURRENT_LIST_DIR}/include/offcenter/common/threading/RunningThread.hpp>
		$<INSTALL_INTERFACE:include/offcenter/common/threading/RunningThread.hpp>

		$<BUILD_INTERFACE:${CMAKE_CURRENT_LIST_DIR}/include/offcenter/common/threading/RunningThreadArray.hpp>
		$<INSTALL_INTERFACE:include/offcenter/common/threading/RunningThreadArray.hpp>
)

target_link_libraries(offcenter_common_threading
	${EASYLOGGINGPP_LIBRARY}
)

target_include_directories(offcenter_common_threading
	PUBLIC
		"$<BUILD_INTERFACE:${CMAKE_CURRENT_LIST_DIR}/include>"
		"$<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>"

		${EASYLOGGINGPP_INCLUDE_DIR}
)


#install(TARGETS offcenter_common_threading EXPORT offcenter_common_threading DESTINATION lib)
#install (
#	DIRECTORY ${CMAKE_CURRENT_LIST_DIR}/include/
#	DESTINATION include
#	FILES_MATCHING PATTERN "*.h*"
#)

#if(ENABLE_UNIT_TESTS)
#	add_subdirectory(test)
#endif()

add_subdirectory(example)

