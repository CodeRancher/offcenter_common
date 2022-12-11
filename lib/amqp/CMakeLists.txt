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

include(OffcenterBuild)

offcenter_cxx()
offcenter_elpp()
offcenter_lib_setup(offcenter_common_amqp common_amqp)

set(version 0.0.1)

add_library(${LIB_NAME} STATIC)

target_sources(${LIB_NAME}
	PRIVATE
		#${CMAKE_CURRENT_LIST_DIR}/src/Connection.cpp
		${CMAKE_CURRENT_LIST_DIR}/src/ConnectionSettings.cpp
		${CMAKE_CURRENT_LIST_DIR}/src/Helper.cpp
		${CMAKE_CURRENT_LIST_DIR}/src/URLSchemeHost.cpp
		${CMAKE_CURRENT_LIST_DIR}/src/SessionProducer.cpp
		${CMAKE_CURRENT_LIST_DIR}/src/SessionConsumer.cpp
		${CMAKE_CURRENT_LIST_DIR}/src/SessionProducerDynamicDestination.cpp

	PUBLIC
		#$<BUILD_INTERFACE:${CMAKE_CURRENT_LIST_DIR}/include/offcenter/common/amqp/Callback.hpp>
		#$<INSTALL_INTERFACE:include/offcenter/common/amqp/Callback.hpp>

		#$<BUILD_INTERFACE:${CMAKE_CURRENT_LIST_DIR}/include/offcenter/common/amqp/Connection.hpp>
		#$<INSTALL_INTERFACE:include/offcenter/common/amqp/Connection.hpp>
	
		$<BUILD_INTERFACE:${CMAKE_CURRENT_LIST_DIR}/include/offcenter/common/amqp/ConnectionSettings.hpp>
		$<INSTALL_INTERFACE:include/offcenter/common/amqp/ConnectionSettings.hpp>

		$<BUILD_INTERFACE:${CMAKE_CURRENT_LIST_DIR}/include/offcenter/common/amqp/ConnectionOptions.hpp>
		$<INSTALL_INTERFACE:include/offcenter/common/amqp/ConnectionOptions.hpp>
	
		$<BUILD_INTERFACE:${CMAKE_CURRENT_LIST_DIR}/include/offcenter/common/amqp/ConnectionOptionElements.hpp>
		$<INSTALL_INTERFACE:include/offcenter/common/amqp/ConnectionOptionElements.hpp>
	
		$<BUILD_INTERFACE:${CMAKE_CURRENT_LIST_DIR}/include/offcenter/common/amqp/Consumer.hpp>
		$<INSTALL_INTERFACE:include/offcenter/common/amqp/Consumer.hpp>
	
		$<BUILD_INTERFACE:${CMAKE_CURRENT_LIST_DIR}/include/offcenter/common/amqp/SessionConsumer.hpp>
		$<INSTALL_INTERFACE:include/offcenter/common/amqp/SessionConsumer.hpp>
	
		$<BUILD_INTERFACE:${CMAKE_CURRENT_LIST_DIR}/include/offcenter/common/amqp/Helper.hpp>
		$<INSTALL_INTERFACE:include/offcenter/common/amqp/Helper.hpp>
	
		$<BUILD_INTERFACE:${CMAKE_CURRENT_LIST_DIR}/include/offcenter/common/amqp/Message.hpp>
		$<INSTALL_INTERFACE:include/offcenter/common/amqp/Message.hpp>
	
		$<BUILD_INTERFACE:${CMAKE_CURRENT_LIST_DIR}/include/offcenter/common/amqp/MessageBase.hpp>
		$<INSTALL_INTERFACE:include/offcenter/common/amqp/MessageBase.hpp>
	
		$<BUILD_INTERFACE:${CMAKE_CURRENT_LIST_DIR}/include/offcenter/common/amqp/Producer.hpp>
		$<INSTALL_INTERFACE:include/offcenter/common/amqp/Producer.hpp>
	
		$<BUILD_INTERFACE:${CMAKE_CURRENT_LIST_DIR}/include/offcenter/common/amqp/SessionProducer.hpp>
		$<INSTALL_INTERFACE:include/offcenter/common/amqp/SessionProducer.hpp>
	
		$<BUILD_INTERFACE:${CMAKE_CURRENT_LIST_DIR}/include/offcenter/common/amqp/SessionProducerDynamicDestination.hpp>
		$<INSTALL_INTERFACE:include/offcenter/common/amqp/SessionProducerDynamicDestination.hpp>

		$<BUILD_INTERFACE:${CMAKE_CURRENT_LIST_DIR}/include/offcenter/common/amqp/ProducerConsumerBase.hpp>
		$<INSTALL_INTERFACE:include/offcenter/common/amqp/ProducerConsumerBase.hpp>
	
		$<BUILD_INTERFACE:${CMAKE_CURRENT_LIST_DIR}/include/offcenter/common/amqp/URLSchemeHost.hpp>
		$<INSTALL_INTERFACE:include/offcenter/common/amqp/URLSchemeHost.hpp>
	
		$<BUILD_INTERFACE:${CMAKE_CURRENT_LIST_DIR}/include/offcenter/common/amqp/AMQPException.hpp>
		$<INSTALL_INTERFACE:include/offcenter/common/amqp/AMQPException.hpp>
)

target_include_directories(${LIB_NAME}
	PUBLIC
		${EASYLOGGINGPP_INCLUDE_DIR}
		${ACTIVEMQCPP_INCLUDE_DIR}
		${APR_INCLUDE_DIR}
)

target_include_directories(${LIB_NAME}
	PUBLIC
		"$<BUILD_INTERFACE:${CMAKE_CURRENT_LIST_DIR}/include>"
		"$<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>"

	#	"$<BUILD_INTERFACE:${ACTIVEMQCPP_INCLUDE_DIR}>"
#		"$<BUILD_INTERFACE:${APR_INCLUDE_DIR}>"
)

target_link_libraries(${LIB_NAME}
	offcenter_common
	${EASYLOGGINGPP_LIBRARY}
	${APR_LIBRARIES}
)

include(OffcenterInstall)
offcenter_lib_install()

if(ENABLE_UNIT_TESTS)
	add_subdirectory(test)
endif()

add_subdirectory(example)

