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

# # set minimum cmake version
# cmake_minimum_required(VERSION 3.11 FATAL_ERROR)

# # project name and language
# project(extern LANGUAGES CXX)

# # require C++17
# set(CMAKE_CXX_STANDARD 17)
# set(CMAKE_CXX_EXTENSIONS OFF)
# set(CMAKE_CXX_STANDARD_REQUIRED ON)

# set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON)
# cmake_policy(SET CMP0074 NEW)

# #include(${CMAKE_CURRENT_LIST_DIR}/../cmake/FindAPR.cmake)
# #include(${CMAKE_CURRENT_LIST_DIR}/../cmake/FindActiveMQcpp.cmake)

# #include(FetchContent)
# include(ExternalProject)

# # set(Boost_USE_STATIC_LIBS        ON)
# # set(Boost_USE_DEBUG_LIBS        OFF)
# # set(Boost_USE_RELEASE_LIBS       ON)
# # set(Boost_USE_MULTITHREADED      ON)
# # set(Boost_USE_STATIC_RUNTIME    OFF)
# # find_package(Boost
# # 	1.80
# # 	COMPONENTS iostreams atomic thread system regex filesystem random chrono serialization 
# # )

# set(CPPCHECK_EXCLUDES
#     ${CMAKE_BINARY_DIR}/_deps
# )

# #include(cmake/TBBGet.cmake)
# #include(cmake/TBBBuild.cmake)
# #tbb_get(TBB_ROOT tbb_root SOURCE_CODE)
# #tbb_build(TBB_ROOT ${tbb_root} CONFIG_DIR TBB_DIR)
# #find_package(TBB <options>)

# # we will use the network to fetch Google Test sources
# # make it possible to disable unit tests when not on network
# #option(ENABLE_UNIT_TESTS "Enable unit tests" ON)
# #message(STATUS "Enable testing: ${ENABLE_UNIT_TESTS}")

# #FetchContent_Declare(
# #	apr
# #    GIT_REPOSITORY	https://github.com/apache/apr.git
# #    GIT_TAG			1.7.0
# #)

# #ExternalProject_Add(
# #	apr
# #	GIT_REPOSITORY    https://github.com/apache/apr.git
# #	GIT_TAG           1.7.0
# #)

# #ExternalProject_Add(libantlr
# #    SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/libantlr
# #    CONFIGURE_COMMAND ${CMAKE_CURRENT_SOURCE_DIR}/libantlr/configure --prefix=<INSTALL_DIR>
# #    BUILD_COMMAND ${MAKE})
    
    
	
# #FetchContent_Declare(
# #	activemq-cpp
# #    GIT_REPOSITORY	https://gitbox.apache.org/repos/asf/activemq-cpp.git  
# #    GIT_TAG			activemq-cpp-3.9.5
# #)
# #	
# #FetchContent_MakeAvailable(
# #	#apr
# #	activemq-cpp
# #	#ThorsSerializer
# #	#cpprestsdk
# #)
# #
# #message(STATUS "APR include dir: ${APR_INCLUDE_DIR}")
# #message(STATUS "APR binary dir: ${apr_BINARY_DIR}")

# if(ENABLE_UNIT_TESTS)

# 	#include(GoogleTest)
	
# 	#find_package(GTest REQUIRED)

#   # the following code to fetch googletest
#   # is inspired by and adapted after:
#   #   - https://cmake.org/cmake/help/v3.11/module/FetchContent.html

# 	# FetchContent_Declare(
#     # 	googletest
#     # 	GIT_REPOSITORY https://github.com/google/googletest.git
#     # 	GIT_TAG        release-1.10.0
# 	# )
# 	#find_package(GTest REQUIRED)

# 	# FetchContent_MakeAvailable(
# 	# 	googletest
# 	# )

# #  FetchContent_GetProperties(googletest)
# #
# #  if(NOT googletest_POPULATED)
# #    FetchContent_Populate(googletest)
# #
# #    # Prevent GoogleTest from overriding our compiler/linker options
# #    # when building with Visual Studio
# #    set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
# #    # Prevent GoogleTest from using PThreads
# #    set(gtest_disable_pthreads ON CACHE BOOL "" FORCE)
# #
# #    # adds the targers: gtest, gtest_main, gmock, gmock_main
# #    add_subdirectory(
# #      ${googletest_SOURCE_DIR}
# #      ${googletest_BINARY_DIR}
# #      )
# #
# #    # Silence std::tr1 warning on MSVC
# #    if(MSVC)
# #      foreach(_tgt gtest gtest_main gmock gmock_main)
# #        target_compile_definitions(${_tgt}
# #          PRIVATE
# #            "_SILENCE_TR1_NAMESPACE_DEPRECATION_WARNING"
# #          )
# #      endforeach()
# #    endif()
# #  endif()

# endif()

# set(CMAKE_VERBOSE_MAKEFILE ON)

