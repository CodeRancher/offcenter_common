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
# @date   09-15-2021
#

offcenter_cxx()
offcenter_elpp()

offcenter_exe_constants(app_manager)

###############################################################################
# Copy config file
#configure_file(${CMAKE_CURRENT_LIST_DIR}/config.ini config.ini COPYONLY)
#file(COPY ${CMAKE_CURRENT_LIST_DIR}/signal_current_candle.config.ini DESTINATION ${CMAKE_BINARY_DIR}/bin)
#message(STATUS "COPY ${CMAKE_CURRENT_LIST_DIR}/signal_current_candle.config.ini DESTINATION ${CMAKE_BINARY_DIR}/bin")


###############################################################################
# Example Consumer
add_executable (${EXE_NAME}
    ${CMAKE_CURRENT_LIST_DIR}/src/app_manager.cpp
    ${CMAKE_CURRENT_LIST_DIR}/src/AppManagerApp.cpp
)

target_link_libraries(${EXE_NAME}
	offcenter_common_framework
	offcenter_common
	offcenter_common_threading
	offcenter_common_program_options
	Boost::program_options
	${EASYLOGGINGPP_LIBRARY}
	Threads::Threads
	OpenSSL::SSL
)

target_include_directories(${EXE_NAME}
	BEFORE PUBLIC
		${CMAKE_CURRENT_LIST_DIR}/include
	SYSTEM
		${EASYLOGGINGPP_INCLUDE_DIR}
)

offcenter_exe_install()
