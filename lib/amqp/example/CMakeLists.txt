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
# @date   03-15-2021
#

# require C++14
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON)

add_compile_definitions(ELPP_THREAD_SAFE)
add_compile_definitions(ELPP_FRESH_LOG_FILE)
add_compile_definitions(ELPP_NO_DEFAULT_LOG_FILE)

add_executable(
	amqp_example_simple_consumer 
	src/amqp_example_simple_consumer.cpp
)

target_link_libraries(
	amqp_example_simple_consumer
	${EASYLOGGINGPP_LIBRARY}
	${ACTIVEMQCPP_LIBRARIES}
	${APR_LIBRARIES}
	Threads::Threads
)

target_include_directories(amqp_example_simple_consumer
	PUBLIC
		${CMAKE_CURRENT_LIST_DIR}/include
		${CMAKE_CURRENT_LIST_DIR}/../include
		${CMAKE_CURRENT_LIST_DIR}/../../common/include
	SYSTEM
		${ACTIVEMQCPP_INCLUDE_DIR}
		${EASYLOGGINGPP_INCLUDE_DIR}
)

add_executable(
	amqp_example_simple_producer 
	src/amqp_example_simple_producer.cpp
)

target_link_libraries(
	amqp_example_simple_producer
	${EASYLOGGINGPP_LIBRARY}
	${ACTIVEMQCPP_LIBRARIES}
	${APR_LIBRARIES}
	Threads::Threads
)

target_include_directories(amqp_example_simple_producer
	PUBLIC
		${CMAKE_CURRENT_LIST_DIR}/include
		${CMAKE_CURRENT_LIST_DIR}/../include
		${CMAKE_CURRENT_LIST_DIR}/../../common/include
	SYSTEM
		${ACTIVEMQCPP_INCLUDE_DIR}
		${EASYLOGGINGPP_INCLUDE_DIR}
)

add_executable(offcenter_amqp_process_message_example 
	src/process_amqp_message_example.cpp
)

target_link_libraries(offcenter_amqp_process_message_example
	offcenter_common_amqp
	offcenter_common_threading
	${EASYLOGGINGPP_LIBRARY}
	${ACTIVEMQCPP_LIBRARIES}
	${APR_LIBRARIES}
	Threads::Threads
	OpenSSL::SSL
)

target_include_directories(offcenter_amqp_process_message_example
	PUBLIC
		${CMAKE_CURRENT_LIST_DIR}/include
		${CMAKE_CURRENT_LIST_DIR}/../include
		${CMAKE_CURRENT_LIST_DIR}/../../common/include
	SYSTEM
		${ACTIVEMQCPP_INCLUDE_DIR}
		${EASYLOGGINGPP_INCLUDE_DIR}
		${APR_INCLUDE_DIR}
)
