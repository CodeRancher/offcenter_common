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
# @date   05-02-2019
#

offcenter_cxx()
offcenter_elpp()
offcenter_test_constants(offcenter_common_framework_tests)

add_compile_definitions(CONFIGFILE_EMPTY="${CMAKE_CURRENT_LIST_DIR}/data/config_empty.cfg")
add_compile_definitions(CONFIGFILE_BASIC="${CMAKE_CURRENT_LIST_DIR}/data/config_basic.cfg")

add_executable(${EXE_NAME}
	${CMAKE_CURRENT_LIST_DIR}/src/main.cpp
	${CMAKE_CURRENT_LIST_DIR}/src/test_basic_app.cpp
	${CMAKE_CURRENT_LIST_DIR}/src/test_basic_app_with_config.cpp
	${CMAKE_CURRENT_LIST_DIR}/src/test_amqp_app.cpp
	${CMAKE_CURRENT_LIST_DIR}/src/test_distributed_logging_app.cpp
	${CMAKE_CURRENT_LIST_DIR}/src/test_distributed_status_app.cpp
	${CMAKE_CURRENT_LIST_DIR}/src/test_admin_status.cpp
	${CMAKE_CURRENT_LIST_DIR}/src/test_admin_control.cpp
)

target_link_libraries(${EXE_NAME}
	GTest::gtest
	offcenter_common_framework
	offcenter_common_amqp
	offcenter_common
	Boost::program_options
	${EASYLOGGINGPP_LIBRARY}
	${ACTIVEMQCPP_LIBRARIES}
	${APR_LIBRARIES}
	Threads::Threads
	OpenSSL::SSL
)

target_include_directories(${EXE_NAME}
	PUBLIC
		${CMAKE_CURRENT_LIST_DIR}/include
		${CMAKE_CURRENT_LIST_DIR}/../include
		${CMAKE_CURRENT_LIST_DIR}/../../common/include
		${CMAKE_CURRENT_LIST_DIR}/../../program_options/include
	SYSTEM PRIVATE
		${ACTIVEMQCPP_INCLUDE_DIR}
		${APR_INCLUDE_DIR}
)

offcenter_test()