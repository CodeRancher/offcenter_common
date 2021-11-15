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

add_compile_definitions(ELPP_THREAD_SAFE)
add_compile_definitions(ELPP_FRESH_LOG_FILE)
add_compile_definitions(ELPP_NO_DEFAULT_LOG_FILE)

set(AMQP_LIBRARIES
	offcenter_common_framework
	offcenter_common
	offcenter_common_program_options
	offcenter_common_amqp
	offcenter_common_amqpserver
	Boost::program_options
	${EASYLOGGINGPP_LIBRARY}
	${ACTIVEMQCPP_LIBRARIES}
	${APR_LIBRARIES}
	Threads::Threads
	OpenSSL::SSL
) 

###############################################################################
# Copy config file
#configure_file(${CMAKE_CURRENT_LIST_DIR}/config.ini config.ini COPYONLY)
file(COPY ${CMAKE_CURRENT_LIST_DIR}/config.ini DESTINATION ${CMAKE_BINARY_DIR}/bin)
message(STATUS "COPY ${CMAKE_CURRENT_LIST_DIR}/config.ini DESTINATION ${CMAKE_BINARY_DIR}/bin")


###############################################################################
# Example Consumer
add_executable (offcenter_amqpserver_example_consumer
    ${CMAKE_CURRENT_LIST_DIR}/src/amqp_consumer.cpp
    ${CMAKE_CURRENT_LIST_DIR}/src/AmqpConsumerExampleApp.cpp
    ${CMAKE_CURRENT_LIST_DIR}/src/AmqpDataElement.cpp
)

target_link_libraries(offcenter_amqpserver_example_consumer
	${AMQP_LIBRARIES}
)

target_include_directories(offcenter_amqpserver_example_consumer
	BEFORE PUBLIC
		${CMAKE_CURRENT_LIST_DIR}/include
	SYSTEM
		${EASYLOGGINGPP_INCLUDE_DIR}
		${ACTIVEMQCPP_INCLUDE_DIR}
		${APR_INCLUDE_DIR}
)

###############################################################################
# Example Consumer Producer
add_executable (offcenter_amqpserver_example_consumer_producer
    ${CMAKE_CURRENT_LIST_DIR}/src/amqp_consumer_producer.cpp
    ${CMAKE_CURRENT_LIST_DIR}/src/AmqpConsumerProducerExampleApp.cpp
    ${CMAKE_CURRENT_LIST_DIR}/src/AmqpDataElement.cpp
)

target_link_libraries(offcenter_amqpserver_example_consumer_producer
	${AMQP_LIBRARIES}
)

target_include_directories(offcenter_amqpserver_example_consumer_producer
	BEFORE PUBLIC
		${CMAKE_CURRENT_LIST_DIR}/include
	SYSTEM
		${EASYLOGGINGPP_INCLUDE_DIR}
		${ACTIVEMQCPP_INCLUDE_DIR}
		${APR_INCLUDE_DIR}
)

###############################################################################
# Example Producer
add_executable (offcenter_amqpserver_example_producer
    ${CMAKE_CURRENT_LIST_DIR}/src/amqp_producer.cpp
    ${CMAKE_CURRENT_LIST_DIR}/src/AmqpProducerExampleApp.cpp
    ${CMAKE_CURRENT_LIST_DIR}/src/AmqpDataElement.cpp
)

target_link_libraries(offcenter_amqpserver_example_producer
	${AMQP_LIBRARIES}
)

target_include_directories(offcenter_amqpserver_example_producer
	BEFORE PUBLIC
		${CMAKE_CURRENT_LIST_DIR}/include
	SYSTEM
		${EASYLOGGINGPP_INCLUDE_DIR}
		${ACTIVEMQCPP_INCLUDE_DIR}
		${APR_INCLUDE_DIR}
)

###############################################################################
# Example Consumer
#add_executable (offcenter_amqpmanagedserver_example
#    ${CMAKE_CURRENT_LIST_DIR}/src/amqp_managed_app.cpp
#    ${CMAKE_CURRENT_LIST_DIR}/src/AmqpManagedExampleApp.cpp
#    ${CMAKE_CURRENT_LIST_DIR}/src/AmqpDataElement.cpp
#)
#
#target_link_libraries(offcenter_amqpmanagedserver_example
#	${AMQP_LIBRARIES}
#)
#
#target_include_directories(offcenter_amqpmanagedserver_example
#	BEFORE PUBLIC
#		${CMAKE_CURRENT_LIST_DIR}/include
#	SYSTEM
#		${EASYLOGGINGPP_INCLUDE_DIR}
#		${ACTIVEMQCPP_INCLUDE_DIR}
#		${APR_INCLUDE_DIR}
#)

###############################################################################
# Example Consumer
#add_executable (offcenter_amqpmanagerserver_example
#    ${CMAKE_CURRENT_LIST_DIR}/src/amqp_manager_app.cpp
#    ${CMAKE_CURRENT_LIST_DIR}/src/AmqpManagerExampleApp.cpp
#    ${CMAKE_CURRENT_LIST_DIR}/src/AmqpDataElement.cpp
#)
#
#target_link_libraries(offcenter_amqpmanagerserver_example
#	${AMQP_LIBRARIES}
#)
#
#target_include_directories(offcenter_amqpmanagerserver_example
#	BEFORE PUBLIC
#		${CMAKE_CURRENT_LIST_DIR}/include
#	SYSTEM
#		${EASYLOGGINGPP_INCLUDE_DIR}
#		${ACTIVEMQCPP_INCLUDE_DIR}
#		${APR_INCLUDE_DIR}
#)

