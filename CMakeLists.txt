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

set(PROJECT_NAME offcenter_common)
project (${PROJECT_NAME} LANGUAGES CXX)

message(STATUS "cmake1: ${CMAKE_CURRENT_SOURCE_DIR}/cmake")
message(STATUS "cmake2: ${CMAKE_CURRENT_SOURCE_DIR}/extern/cmake")
list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake)
list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/extern/cmake)
message(STATUS "cmake3: ${CMAKE_MODULE_PATH}")

include(OffcenterBuild)
offcenter_proj_setup(${PROJECT_NAME} 0 0 1)

###############################################################################
# Libraries

INCLUDE(FindPackageHandleStandardArgs)

find_package(EASYLOGGINGPP REQUIRED)
find_package(GMP REQUIRED)
find_package(MPFR REQUIRED)
find_package(Soci REQUIRED)
find_package(MariaDBClient REQUIRED)
find_package(nlohmann_json REQUIRED)
find_package(cpprestsdk REQUIRED)
find_package(TBB REQUIRED)
find_package(BZip2 REQUIRED)
find_package(APR REQUIRED)
find_package(ActiveMQcpp REQUIRED)

offcenter_find_threads()
offcenter_find_boost()
offcenter_find_openssl()

offcenter_cpp_check(OFF)
offcenter_unit_tests(ON)

###############################################################################
# sub projects
add_subdirectory(extern)
add_subdirectory(lib)
#add_subdirectory(app)
#add_subdirectory(doc)

offcenter_proj_install()
