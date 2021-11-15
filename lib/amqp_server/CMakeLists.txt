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

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

#configure_file(config.h.in "${CMAKE_CURRENT_BINARY_DIR}/config.h" @ONLY)

add_library(offcenter_common_amqpserver STATIC)

# set_target_properties(offcenter_common_amqpserver
# 	PROPERTIES PUBLIC_HEADER
# 		"foo.h;${CMAKE_CURRENT_BINARY_DIR}/config.h"
# )

set(version 0.0.1)
set_property(TARGET offcenter_common_amqpserver PROPERTY VERSION ${version})
set_property(TARGET offcenter_common_amqpserver PROPERTY SOVERSION 0)
set_property(TARGET offcenter_common_amqpserver PROPERTY INTERFACE_OffcenterCommonAmqp_MAJOR_VERSION 0)
set_property(TARGET offcenter_common_amqpserver APPEND PROPERTY COMPATIBLE_INTERFACE_STRING OffcenterCommonAmqp_MAJOR_VERSION)

add_compile_definitions(ELPP_THREAD_SAFE)
add_compile_definitions(ELPP_FRESH_LOG_FILE)
add_compile_definitions(ELPP_NO_DEFAULT_LOG_FILE)

target_sources(offcenter_common_amqpserver
	PRIVATE
		${CMAKE_CURRENT_LIST_DIR}/src/AmqpServerAppFoundation.cpp
		#${CMAKE_CURRENT_LIST_DIR}/src/Utility.cpp
		#${CMAKE_CURRENT_LIST_DIR}/src/AutoMethodHandler.cpp
	PUBLIC
		#$<BUILD_INTERFACE:${CMAKE_CURRENT_LIST_DIR}/include/offcenter/common/amqpserver/network/Utility.hpp>
		#$<INSTALL_INTERFACE:include/offcenter/common/amqpserver/network/Utility.hpp>

		$<BUILD_INTERFACE:${CMAKE_CURRENT_LIST_DIR}/include/offcenter/common/amqpserver/IAmqpServerApp.hpp>
		$<INSTALL_INTERFACE:include/offcenter/common/amqpserver/IAmqpServerApp.hpp>

		$<BUILD_INTERFACE:${CMAKE_CURRENT_LIST_DIR}/include/offcenter/common/amqpserver/AmqpServerAppManager.hpp>
		$<INSTALL_INTERFACE:include/offcenter/common/amqpserver/AmqpServerAppManager.hpp>

		#$<BUILD_INTERFACE:${CMAKE_CURRENT_LIST_DIR}/include/offcenter/common/amqpserver/AmqpServerAppFoundation.hpp>
		#$<INSTALL_INTERFACE:include/offcenter/common/amqpserver/AmqpServerAppFoundation.hpp>
)

target_link_libraries(offcenter_common_amqpserver
	offcenter_common_framework
	offcenter_common
	offcenter_common_program_options
	Boost::program_options
	Boost::system
	#cpprestsdk::cpprest
	${EASYLOGGINGPP_LIBRARY}
	Threads::Threads
)

target_include_directories(offcenter_common_amqpserver
	SYSTEM PRIVATE
		${EASYLOGGINGPP_INCLUDE_DIR}
)

target_include_directories(offcenter_common_amqpserver
	PUBLIC
		"$<BUILD_INTERFACE:${CMAKE_CURRENT_LIST_DIR}/include>"
		"$<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>"
)

#install(TARGETS offcenter_common_amqp EXPORT offcenter_common_amqp DESTINATION lib)
#install (
#	DIRECTORY ${CMAKE_CURRENT_LIST_DIR}/include/
#	DESTINATION include
#	FILES_MATCHING PATTERN "*.h*"
#)

# install(
# 	TARGETS
# 		offcenter_common_amqpserver
# 	# IMPORTANT: Add the foo library to the "export-set"
# 	EXPORT
# 		OffcenterCommonTargets
# 	RUNTIME DESTINATION "${INSTALL_BIN_DIR}" COMPONENT bin
# 	LIBRARY DESTINATION "${INSTALL_LIB_DIR}" COMPONENT shlib
# 	PUBLIC_HEADER DESTINATION "${INSTALL_INCLUDE_DIR}/foo"
# 	COMPONENT dev
# )

if(ENABLE_UNIT_TESTS)
	add_subdirectory(test)
endif()

add_subdirectory(example)

