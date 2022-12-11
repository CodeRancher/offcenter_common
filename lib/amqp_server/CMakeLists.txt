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
# @date   04-13-2021
#

include(OffcenterBuild)

offcenter_cxx()
offcenter_elpp()
offcenter_lib_setup(offcenter_common_amqpserver common_amqpserver)
set(version 0.0.1)

add_library(${LIB_NAME} STATIC)

target_sources(${LIB_NAME}
	PRIVATE
		${CMAKE_CURRENT_LIST_DIR}/src/AmqpServerAppFoundation.cpp
		#${CMAKE_CURRENT_LIST_DIR}/src/Utility.cpp
		#${CMAKE_CURRENT_LIST_DIR}/src/AutoMethodHandler.cpp
	PUBLIC
		#$<BUILD_INTERFACE:${CMAKE_CURRENT_LIST_DIR}/${LIB_COMMON_INC_BASE}/common/amqpserver/network/Utility.hpp>
		#$<INSTALL_INTERFACE:${LIB_COMMON_INC_BASE}/common/amqpserver/network/Utility.hpp>

		$<BUILD_INTERFACE:${CMAKE_CURRENT_LIST_DIR}/${LIB_COMMON_INC_BASE}/common/amqpserver/IAmqpServerApp.hpp>
		$<INSTALL_INTERFACE:${LIB_COMMON_INC_BASE}/common/amqpserver/IAmqpServerApp.hpp>

		$<BUILD_INTERFACE:${CMAKE_CURRENT_LIST_DIR}/${LIB_COMMON_INC_BASE}/common/amqpserver/AmqpServerAppManager.hpp>
		$<INSTALL_INTERFACE:${LIB_COMMON_INC_BASE}/common/amqpserver/AmqpServerAppManager.hpp>

		#$<BUILD_INTERFACE:${CMAKE_CURRENT_LIST_DIR}/${LIB_COMMON_INC_BASE}/common/amqpserver/AmqpServerAppFoundation.hpp>
		#$<INSTALL_INTERFACE:${LIB_COMMON_INC_BASE}/common/amqpserver/AmqpServerAppFoundation.hpp>
)

target_include_directories(${LIB_NAME}
	PUBLIC
		"$<BUILD_INTERFACE:${CMAKE_CURRENT_LIST_DIR}/include>"
		"$<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>"
)

target_link_libraries(${LIB_NAME}
	offcenter_common_framework
	offcenter_common
	offcenter_common_program_options
	Boost::program_options
	Boost::system
	#cpprestsdk::cpprest
	${EASYLOGGINGPP_LIBRARY}
	Threads::Threads
)

target_include_directories(${LIB_NAME}
	SYSTEM PRIVATE
		${EASYLOGGINGPP_INCLUDE_DIR}
)

include(OffcenterInstall)
offcenter_lib_install()

if(ENABLE_UNIT_TESTS)
	add_subdirectory(test)
endif()

add_subdirectory(example)

