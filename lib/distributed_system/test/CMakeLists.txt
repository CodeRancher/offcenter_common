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

offcenter_cxx()
offcenter_elpp()
offcenter_test_constants(offcenter_common_distributed_system_tests)

add_executable(${EXE_NAME}
	src/main.cpp
	src/simple_consumerdata_test.cpp
	src/SimpleConsumerDataFixture.cpp
	src/triple_call_consumerdata_test.cpp
)

target_link_libraries(${EXE_NAME}
	offcenter_common_distributed_system
	GTest::gtest
	${EASYLOGGINGPP_LIBRARY}
	${ACTIVEMQCPP_LIBRARIES}
	#${APR_LIBRARIES}
	Threads::Threads
)

target_include_directories(${EXE_NAME}
	PUBLIC
		${CMAKE_CURRENT_LIST_DIR}/include
		${CMAKE_CURRENT_LIST_DIR}/../include
		${CMAKE_CURRENT_LIST_DIR}/../../amqp/include
		${CMAKE_CURRENT_LIST_DIR}/../../common/include
		
	SYSTEM PRIVATE
		${ACTIVEMQCPP_INCLUDE_DIR}
		${EASYLOGGINGPP_INCLUDE_DIR}
		
)

offcenter_test()