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

add_compile_definitions(ELPP_THREAD_SAFE)
add_compile_definitions(ELPP_FRESH_LOG_FILE)
add_compile_definitions(ELPP_NO_DEFAULT_LOG_FILE)


	            #"--template='{file}:{line}: warning: {id} ({severity}): {message}'"
	            #"--quiet"
	            #(.*?):(\d+):(\d+:)? [Ee]rror: (conflicting types for .*[`'"](.*)['"].*)
	            #(.*?):(\d+):(\d+:)?\s*(([Ww]arning)|(WARNING)): (.*)

#find_program(CMAKE_CXX_CPPCHECK NAMES cppcheck)
#if (CMAKE_CXX_CPPCHECK)
#    list(
#        APPEND CMAKE_CXX_CPPCHECK 
#            "--enable=warning"
#            "--inconclusive"
#            "--force" 
#            "--inline-suppr"
#            "--suppressions-list=${CMAKE_SOURCE_DIR}/CppCheckSuppressions.txt"
#    )
#endif()

###############################################################################
# Logging
option(RUNNING_THREAD_TRACE "Running Thread Trace" OFF)
if(RUNNING_THREAD_TRACE)
	message(STATUS "Tracing Running Threads")
    add_definitions(-DRUNNINGTHREADTRACE)
endif()

add_subdirectory(common)
add_subdirectory(threading)
add_subdirectory(amqp)
add_subdirectory(soci)
add_subdirectory(distributed_system)
add_subdirectory(program_options)
add_subdirectory(framework)
add_subdirectory(rest_server)
add_subdirectory(amqp_server)
#add_subdirectory(schedule)

install(TARGETS
			offcenter_common_amqp
			offcenter_common_amqpserver
			offcenter_common
			offcenter_common_distributedsystem
			offcenter_common_framework
			offcenter_common_program_options
			offcenter_common_restserver
			offcenter_common_soci
			offcenter_common_threading
        EXPORT  OffcenterCommonTargets
        LIBRARY DESTINATION lib
        ARCHIVE DESTINATION lib
        RUNTIME DESTINATION bin
        INCLUDES DESTINATION include
)

install (
	DIRECTORY ${CMAKE_CURRENT_LIST_DIR}/include/
	DESTINATION include
	FILES_MATCHING PATTERN "*.h*"
)

install(EXPORT OffcenterCommonTargets
        FILE OffcenterCommonTargets.cmake
        NAMESPACE OffcenterCommon::
        DESTINATION lib/cmake/offcentercommon
)

include(CMakePackageConfigHelpers)
set(version 0.0.1)

# generate the version file for the config file
write_basic_package_version_file(
	"${CMAKE_CURRENT_BINARY_DIR}/OffcenterCommonConfigVersion.cmake"
	VERSION "${version}"
	COMPATIBILITY AnyNewerVersion
)

# create config file
configure_package_config_file(${CMAKE_CURRENT_SOURCE_DIR}/offcenter-common-config.cmake.in
	"${CMAKE_CURRENT_BINARY_DIR}/OffcenterCommonConfig.cmake"
	INSTALL_DESTINATION lib/cmake/offcentercommon
)

# install config files
install(FILES
	"${CMAKE_CURRENT_BINARY_DIR}/OffcenterCommonConfig.cmake"
	"${CMAKE_CURRENT_BINARY_DIR}/OffcenterCommonConfigVersion.cmake"
	DESTINATION lib/cmake/offcentercommon
)

# generate the export targets for the build tree
export(EXPORT OffcenterCommonTargets
	FILE "${CMAKE_CURRENT_BINARY_DIR}/cmake/OffcenterCommonTargets.cmake"
	NAMESPACE OffcenterCommon::
)
