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

cmake_minimum_required (VERSION 3.19 FATAL_ERROR)

project (offcenter_common LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(OFFCENTER_COMMON_MAJOR_VERSION 0)
set(OFFCENTER_COMMON_MINOR_VERSION 0)
set(OFFCENTER_COMMON_PATCH_VERSION 1)
set(OFFCENTER_COMMON_VERSION ${OFFCENTER_COMMON_MAJOR_VERSION}.${OFFCENTER_COMMON_MINOR_VERSION}.${OFFCENTER_COMMON_PATCH_VERSION})

include(GNUInstallDirs)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY
  ${CMAKE_BINARY_DIR}/${CMAKE_INSTALL_LIBDIR})
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY
  ${CMAKE_BINARY_DIR}/${CMAKE_INSTALL_LIBDIR})
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY
  ${CMAKE_BINARY_DIR}/${CMAKE_INSTALL_BINDIR})

list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake)

###############################################################################
# Libraries

include(FetchContent)
include(ExternalProject)
INCLUDE(FindPackageHandleStandardArgs)

cmake_policy(SET CMP0074 NEW)

# LoggingCpp
find_package(EASYLOGGINGPP REQUIRED)

set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(Threads REQUIRED)

set(Boost_USE_STATIC_LIBS        ON)
set(Boost_USE_DEBUG_LIBS        OFF)
set(Boost_USE_RELEASE_LIBS       ON)
set(Boost_USE_MULTITHREADED      ON)
set(Boost_USE_STATIC_RUNTIME    OFF)
find_package(Boost
	1.74
	COMPONENTS program_options atomic thread system regex filesystem random chrono serialization
)

find_package(Soci REQUIRED)
find_package(MariaDBClient REQUIRED)
find_package(nlohmann_json REQUIRED)
find_package(cpprestsdk REQUIRED)

set(OPENSSL_USE_STATIC_LIBS TRUE)
find_package(OpenSSL REQUIRED)

# CPPCheck
option(ENABLE_CODE_ANALYSIS "Run code analysis" OFF)
message(STATUS "ENABLE_CODE_ANALYSIS       ${ENABLE_CODE_ANALYSIS}")

if(ENABLE_CODE_ANALYSIS)
    find_program(CMAKE_CXX_CPPCHECK NAMES cppcheck)
    message(STATUS "cppcheck                   ${CMAKE_CXX_CPPCHECK}")
    
    if(CMAKE_CXX_CPPCHECK)
        # Notes:
        # - unmatchedSuppression needed since not all source files are
        #   analyzed simultaneously
        # - unusedFunction needed since not all source files are
        #   analyzed simultaneously
        # - template needed to force "warning" into output string, and
        #   to make the 'id' available for suppression

	    ## set exclude files and folders
	    foreach(ex ${CPPCHECK_EXCLUDES})
	        list(APPEND _CPPCHECK_EXCLUDES "-i${ex}")
	    endforeach(ex)

        list(
        	APPEND CMAKE_CXX_CPPCHECK 
	            "--enable=all"
	            "--inconclusive"
	            "--inline-suppr"
	            "--suppress=missingIncludeSystem"
	            "--suppress=unmatchedSuppression"
	            "--suppress=unusedFunction"
	            "--template={file}:{line}:0:warning: {severity}:{id}:{message}"
        	)
    endif()
endif(ENABLE_CODE_ANALYSIS)

###############################################################################
# Unit testing
option(ENABLE_UNIT_TESTS "Build the tests" ON)
if(ENABLE_UNIT_TESTS)
    enable_testing()
    find_package(GTest REQUIRED)
    
endif()
message(STATUS "ENABLE_UNIT_TESTS ${ENABLE_UNIT_TESTS}")

###############################################################################
# sub projects
add_subdirectory(extern)
add_subdirectory(lib)
add_subdirectory(app)
add_subdirectory(doc)
