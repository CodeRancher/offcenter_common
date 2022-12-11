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
# @date   12-01-2021
#

offcenter_cxx()
offcenter_elpp()

###############################################################################
# Framework Example
offcenter_example_constants(framework)
add_executable(${EXE_NAME}
    ${CMAKE_CURRENT_LIST_DIR}/src/framework_example.cpp
)

target_compile_definitions(${EXE_NAME}
	PRIVATE
		EXE_NAME=${EXE_NAME}
		EXE_VERSION=${EXE_VERSION}
)

target_link_libraries(${EXE_NAME}
	offcenter_common
	offcenter_common_framework
	Boost::program_options
	${EASYLOGGINGPP_LIBRARY}
	Threads::Threads
)

target_include_directories(${EXE_NAME}
	BEFORE PUBLIC
		${CMAKE_CURRENT_LIST_DIR}/include
	SYSTEM
		${EASYLOGGINGPP_INCLUDE_DIR}
)

offcenter_example()