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
# @date   05-27-2019
#

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_library(offcenter_common_amqp STATIC)

set(version 0.0.1)
set_property(TARGET offcenter_common_amqp PROPERTY VERSION ${version})
set_property(TARGET offcenter_common_amqp PROPERTY SOVERSION 0)
set_property(TARGET offcenter_common_amqp PROPERTY INTERFACE_OffcenterCommonAmqp_MAJOR_VERSION 0)
set_property(TARGET offcenter_common_amqp APPEND PROPERTY COMPATIBLE_INTERFACE_STRING OffcenterCommonAmqp_MAJOR_VERSION)

add_compile_definitions(ELPP_THREAD_SAFE)
add_compile_definitions(ELPP_FRESH_LOG_FILE)
add_compile_definitions(ELPP_NO_DEFAULT_LOG_FILE)

target_sources(offcenter_common_amqp
	PRIVATE
		#${CMAKE_CURRENT_LIST_DIR}/src/Connection.cpp
		${CMAKE_CURRENT_LIST_DIR}/src/ConnectionSettings.cpp
		${CMAKE_CURRENT_LIST_DIR}/src/Helper.cpp
		${CMAKE_CURRENT_LIST_DIR}/src/URLSchemeHost.cpp
		${CMAKE_CURRENT_LIST_DIR}/src/SessionProducer.cpp
		${CMAKE_CURRENT_LIST_DIR}/src/SessionConsumer.cpp
		${CMAKE_CURRENT_LIST_DIR}/src/SessionProducerDynamicDestination.cpp

	PUBLIC
		#$<BUILD_INTERFACE:${CMAKE_CURRENT_LIST_DIR}/include/offcenter/amqp/Callback.hpp>
		#$<INSTALL_INTERFACE:include/offcenter/amqp/Callback.hpp>

		#$<BUILD_INTERFACE:${CMAKE_CURRENT_LIST_DIR}/include/offcenter/amqp/Connection.hpp>
		#$<INSTALL_INTERFACE:include/offcenter/amqp/Connection.hpp>
	
		$<BUILD_INTERFACE:${CMAKE_CURRENT_LIST_DIR}/include/offcenter/amqp/ConnectionSettings.hpp>
		$<INSTALL_INTERFACE:include/offcenter/amqp/ConnectionSettings.hpp>

		$<BUILD_INTERFACE:${CMAKE_CURRENT_LIST_DIR}/include/offcenter/amqp/ConnectionOptions.hpp>
		$<INSTALL_INTERFACE:include/offcenter/amqp/ConnectionOptions.hpp>
	
		$<BUILD_INTERFACE:${CMAKE_CURRENT_LIST_DIR}/include/offcenter/amqp/ConnectionOptionElements.hpp>
		$<INSTALL_INTERFACE:include/offcenter/amqp/ConnectionOptionElements.hpp>
	
		$<BUILD_INTERFACE:${CMAKE_CURRENT_LIST_DIR}/include/offcenter/amqp/Consumer.hpp>
		$<INSTALL_INTERFACE:include/offcenter/amqp/Consumer.hpp>
	
		$<BUILD_INTERFACE:${CMAKE_CURRENT_LIST_DIR}/include/offcenter/amqp/SessionConsumer.hpp>
		$<INSTALL_INTERFACE:include/offcenter/amqp/SessionConsumer.hpp>
	
		$<BUILD_INTERFACE:${CMAKE_CURRENT_LIST_DIR}/include/offcenter/amqp/Helper.hpp>
		$<INSTALL_INTERFACE:include/offcenter/amqp/Helper.hpp>
	
		$<BUILD_INTERFACE:${CMAKE_CURRENT_LIST_DIR}/include/offcenter/amqp/Message.hpp>
		$<INSTALL_INTERFACE:include/offcenter/amqp/Message.hpp>
	
		$<BUILD_INTERFACE:${CMAKE_CURRENT_LIST_DIR}/include/offcenter/amqp/MessageBase.hpp>
		$<INSTALL_INTERFACE:include/offcenter/amqp/MessageBase.hpp>
	
		$<BUILD_INTERFACE:${CMAKE_CURRENT_LIST_DIR}/include/offcenter/amqp/Producer.hpp>
		$<INSTALL_INTERFACE:include/offcenter/amqp/Producer.hpp>
	
		$<BUILD_INTERFACE:${CMAKE_CURRENT_LIST_DIR}/include/offcenter/amqp/SessionProducer.hpp>
		$<INSTALL_INTERFACE:include/offcenter/amqp/SessionProducer.hpp>
	
		$<BUILD_INTERFACE:${CMAKE_CURRENT_LIST_DIR}/include/offcenter/amqp/SessionProducerDynamicDestination.hpp>
		$<INSTALL_INTERFACE:include/offcenter/amqp/SessionProducerDynamicDestination.hpp>

		$<BUILD_INTERFACE:${CMAKE_CURRENT_LIST_DIR}/include/offcenter/amqp/ProducerConsumerBase.hpp>
		$<INSTALL_INTERFACE:include/offcenter/amqp/ProducerConsumerBase.hpp>
	
		$<BUILD_INTERFACE:${CMAKE_CURRENT_LIST_DIR}/include/offcenter/amqp/URLSchemeHost.hpp>
		$<INSTALL_INTERFACE:include/offcenter/amqp/URLSchemeHost.hpp>
	
		$<BUILD_INTERFACE:${CMAKE_CURRENT_LIST_DIR}/include/offcenter/amqp/AMQPException.hpp>
		$<INSTALL_INTERFACE:include/offcenter/amqp/AMQPException.hpp>
)

#message(STATUS "ActiveMQ source dir: ${activemq-cpp_SOURCE_DIR}")
#message(STATUS "ActiveMQ binary dir: ${activemq-cpp_BINARY_DIR}")

target_link_libraries(offcenter_common_amqp
	offcenter_common
	${EASYLOGGINGPP_LIBRARY}
	${APR_LIBRARIES}
)

target_include_directories(offcenter_common_amqp
	SYSTEM PUBLIC
		${EASYLOGGINGPP_INCLUDE_DIR}
)

target_include_directories(offcenter_common_amqp
	PUBLIC
		"$<BUILD_INTERFACE:${CMAKE_CURRENT_LIST_DIR}/include>"
		"$<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>"

		"$<BUILD_INTERFACE:${ACTIVEMQCPP_INCLUDE_DIR}>"
		"$<BUILD_INTERFACE:${APR_INCLUDE_DIR}>"
)

#install(TARGETS offcenter_common_amqp EXPORT offcenter_common_amqp DESTINATION lib)
#install (
#	DIRECTORY ${CMAKE_CURRENT_LIST_DIR}/include/
#	DESTINATION include
#	FILES_MATCHING PATTERN "*.h*"
#)

if(ENABLE_UNIT_TESTS)
	add_subdirectory(test)
endif()

add_subdirectory(example)

