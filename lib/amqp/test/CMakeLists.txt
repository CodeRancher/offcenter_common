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
# @date   11-11-2019
#

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_compile_definitions(ELPP_THREAD_SAFE)
add_compile_definitions(ELPP_FRESH_LOG_FILE)
add_compile_definitions(ELPP_NO_DEFAULT_LOG_FILE)

add_executable(offcenter_common_amqp_tests
	${CMAKE_CURRENT_LIST_DIR}/src/main.cpp
	#${CMAKE_CURRENT_LIST_DIR}/src/text_message_test.cpp
	#${CMAKE_CURRENT_LIST_DIR}/src/TopicProducerFixture.cpp
	#${CMAKE_CURRENT_LIST_DIR}/src/async_message_test.cpp
	#${CMAKE_CURRENT_LIST_DIR}/src/AsyncTopicProducerFixture.cpp
	${CMAKE_CURRENT_LIST_DIR}/src/connection_options_test.cpp
	${CMAKE_CURRENT_LIST_DIR}/src/URLSchemeHost_test.cpp
	${CMAKE_CURRENT_LIST_DIR}/src/URLFailover_test.cpp
)

target_link_libraries(offcenter_common_amqp_tests
	offcenter_common_amqp
	GTest::gtest
	GTest::gmock
	${EASYLOGGINGPP_LIBRARY}
	${ACTIVEMQCPP_LIBRARIES}
	${APR_LIBRARIES}
	Threads::Threads
	OpenSSL::SSL
)

target_include_directories(offcenter_common_amqp_tests
	PUBLIC
		${CMAKE_CURRENT_LIST_DIR}/include
		${CMAKE_CURRENT_LIST_DIR}/../include
		${CMAKE_CURRENT_LIST_DIR}/../../common/include
	SYSTEM INTERFACE
		${ACTIVEMQCPP_INCLUDE_DIR}
		${EASYLOGGINGPP_INCLUDE_DIR}
)

gtest_discover_tests(offcenter_common_amqp_tests)

add_test(NAME monolithic COMMAND offcenter_common_amqp_tests)

