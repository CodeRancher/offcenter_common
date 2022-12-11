#
# Copyright 2022 Scott Brauer
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
# @file   OffcenterBuild.cmake
# @author Scott Brauer
# @date   09-25-2022
#

# offcenter_cmake_min
# Basic version of cmake
function(offcenter_cmake_min)
    cmake_minimum_required (VERSION 3.15 FATAL_ERROR)
endfunction()

# offcenter_cxx
# Standard CXX cmake settings across all builds
macro(offcenter_cxx)
    set(CMAKE_CXX_STANDARD 17)
    set(CMAKE_CXX_EXTENSIONS OFF)
    set(CMAKE_CXX_STANDARD_REQUIRED ON)
endmacro()

# offcenter_gnu_dirs
# Standard GTNU Dirs
macro(offcenter_gnu_dirs)
    include(GNUInstallDirs)
    set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/${CMAKE_INSTALL_LIBDIR})
    set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/${CMAKE_INSTALL_LIBDIR})
    set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/${CMAKE_INSTALL_BINDIR})
endmacro()

###############################################################################
# Easylogging
# Standard Easylogging cmake settings across all builds
macro(offcenter_elpp)
    add_compile_definitions(ELPP_THREAD_SAFE)
    add_compile_definitions(ELPP_FRESH_LOG_FILE)
    add_compile_definitions(ELPP_NO_DEFAULT_LOG_FILE)
endmacro()

# offcenter_cmake_min
# Basic version of cmake
function(offcenter_project name)
    project (name LANGUAGES CXX)

    offcenter_cxx()
    offcenter_gnu_dirs()
endfunction()

# ###############################################################################
# # offcenter_proj_constants
# # Defines all Offcenter project contansts in one macro call
# macro(offcenter_proj_constants proj_name major minor patch)
#     set(PROJ_NAME ${proj_name})

#     offcenter_cxx()
#     offcenter_version(${PROJ_NAME} ${major} ${minor} ${patch})
#     offcenter_gnu_dirs()
#     offcenter_example_test_dirs()

#     #offcenter_lib_setup()
    
#     # set(LIB_TAG ${lib_tag})
#     # set(LIB_TARGETS ${LIB_NAME}-targets)
#     # set(LIB_NAMESPACE Offcenter)
#     # set(LIB_CMAKE_DIR cmake)

#     # set(LIB_NAMES ${LIB_NAMES} ${lib_name}) 
#     # set(LIB_NAMES ${LIB_NAMES} PARENT_SCOPE)

#     message(STATUS "Project: ${PROJ_NAME} version(${${PROJ_NAME}_version})")
# endmacro()

# ###############################################################################
# # offcenter_lib_constants
# # Defines all Offcenter library contansts in one macro call
# macro(offcenter_libs_constants lib_name lib_tag)
#     set(LIB_NAME ${lib_name})
#     set(LIB_TAG ${lib_tag})
#     set(LIB_TARGETS ${LIB_TAG}Targets)
#     set(LIB_NAMESPACE ${LIB_TAG})
#     set(LIB_CMAKE_DIR ${LIB_NAME})

#     message(STATUS "Library: ${LIB_NAME} tag(${LIB_TAG}) targets(${LIB_TARGETS}) namespace(${LIB_NAMESPACE}) cmake_dir(${LIB_CMAKE_DIR})")
# endmacro()

# ###############################################################################
# # offcenter_lib_constants
# # Defines all Offcenter library contansts in one macro call
# macro(offcenter_lib_constants lib_name lib_tag)
#     set(LIB_NAME ${lib_name})
#     set(LIB_TAG ${lib_tag})
#     set(LIB_TARGETS ${LIB_TAG}Targets)
#     set(LIB_NAMESPACE ${LIB_TAG})
#     set(LIB_CMAKE_DIR ${LIB_NAME})

#     message(STATUS "Library: ${LIB_NAME} tag(${LIB_TAG}) targets(${LIB_TARGETS}) namespace(${LIB_NAMESPACE}) cmake_dir(${LIB_CMAKE_DIR})")
# endmacro()

###############################################################################
# offcenter_libs_setup
# 
# macro(offcenter_libs_setup)
#     set(LIB_NAMES "")
# endmacro()

# ###############################################################################
# # offcenter_lib_constants
# # Defines all Offcenter library contansts in one macro call
# macro(offcenter_lib_constants_2 lib_name lib_tag)
#     set(LIB_NAME ${lib_name})
#     set(LIB_TAG ${lib_tag})
#     set(LIB_TARGETS ${LIB_NAME}-targets)
#     set(LIB_NAMESPACE Offcenter)
#     set(LIB_CMAKE_DIR cmake)

#     set(LIB_NAMES ${LIB_NAMES} ${lib_name}) 
#     set(LIB_NAMES ${LIB_NAMES} PARENT_SCOPE)

#     set(LIB_COMMON_INC_BASE include/offcenter)

#     message(STATUS "Library: ${LIB_NAME} tag(${LIB_TAG}) targets(${LIB_TARGETS}) namespace(${LIB_NAMESPACE}) cmake_dir(${LIB_CMAKE_DIR}) inc_base(${LIB_COMMON_INC_BASE})")
# endmacro()

###############################################################################
# offcenter_exe_constants
# Defines all Offcenter application contansts in one macro call
macro(offcenter_exe_constants exe_name)
    set(EXE_NAME ${exe_name})
    message(STATUS "Executable: ${EXE_NAME}")
endmacro()

###############################################################################
# offcenter_example_constants
# Defines all Offcenter example contansts in one macro call
macro(offcenter_example_constants exe_name)
    set(EXE_NAME ${EXAMPLE_PREFIX}.${PROJECT_NAME}.${exe_name})
endmacro()

###############################################################################
# offcenter_test
# Defines all Offcenter test in one macro call
macro(offcenter_example)
    set_target_properties(${EXE_NAME}
	    PROPERTIES
		    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${CMAKE_INSTALL_EXAMPLE_DIR}
    )
    message(STATUS "Example: ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${CMAKE_INSTALL_EXAMPLE_DIR}/${EXE_NAME}")
endmacro()

###############################################################################
# offcenter_test_constants
# Defines all Offcenter test contansts in one macro call
macro(offcenter_test_constants exe_name)
    set(EXE_NAME ${TEST_PREFIX}.${PROJECT_NAME}.${exe_name})
endmacro()

###############################################################################
# offcenter_test
# Defines all Offcenter test in one macro call
macro(offcenter_test)
    set_target_properties(${EXE_NAME}
	    PROPERTIES
		    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${CMAKE_INSTALL_TEST_DIR}
    )

    if(ENABLE_UNIT_TESTS)
        gtest_discover_tests(${EXE_NAME})
        add_test(NAME monolithic COMMAND ${EXE_NAME})
    endif()
    message(STATUS "Test:    ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${CMAKE_INSTALL_TEST_DIR}/${EXE_NAME}")
endmacro()

# offcenter_unit_tests
# Basic version of cmake
function(offcenter_unit_tests default_value)
    option(ENABLE_UNIT_TESTS "Build the tests" ${default_value})
    if(ENABLE_UNIT_TESTS)
        enable_testing()
        find_package(GTest REQUIRED)
    endif()
    message(STATUS "ENABLE_UNIT_TESTS ${ENABLE_UNIT_TESTS}")
endfunction()

# offcenter_cpp_check
# Basic version of cmake
function(offcenter_cpp_check default_value)
    option(ENABLE_CODE_ANALYSIS "Run code analysis" ${default_value})
    message(STATUS "ENABLE_CODE_ANALYSIS ${ENABLE_CODE_ANALYSIS}")

    if(ENABLE_CODE_ANALYSIS)
        find_program(CMAKE_CXX_CPPCHECK NAMES cppcheck)
        message(STATUS "cppcheck                   ${CMAKE_CXX_CPPCHECK}")

    #    set(CPPCHECK_EXCLUDES
    #        ${CMAKE_BINARY_DIR}/_deps
    #        #${CMAKE_BINARY_DIR}/_deps/nlohmann_json-src/single_include/nlohmann
    #        #${CMAKE_BINARY_DIR}/_deps/nlohmann_json-src/test/src
    #        #${CMAKE_BINARY_DIR}/_deps/nlohmann_json-build/test/CMakeFiles/test-unicode.dir/src
    #        ${CMAKE_BINARY_DIR}/extern
    #        ${CMAKE_SOURCE_DIR}/extern
    #        $ENV{HOME}/dev_tools
    #        $ENV{HOME}/dev_libs
    #    )
    #    message(STATUS "CPPCHECK_EXCLUDES                   ${CPPCHECK_EXCLUDES}")

        if(CMAKE_CXX_CPPCHECK)
            # Notes:
            # - unmatchedSuppression needed since not all source files are
            #   analyzed simultaneously
            # - unusedFunction needed since not all source files are
            #   analyzed simultaneously
            # - template needed to force "warning" into output string, and
            #   to make the 'id' available for suppression

            ## set exclude files and folders
    #	    foreach(ex ${CPPCHECK_EXCLUDES})
    #	        list(APPEND _CPPCHECK_EXCLUDES "-i${ex}")
    #	    endforeach(ex)

            list(
                APPEND CMAKE_CXX_CPPCHECK 
                    "--check-config"
                    "--enable=all"
                    "--verbose"
                    "--inconclusive"
                    "--inline-suppr"
                    #"--suppress=missingIncludeSystem"
                    #"--suppress=unmatchedSuppression"
                    #"--suppress=unusedFunction"
                    "--template={file}:{line}:0:warning: {severity}:{id}:{message}"
                )
        endif()
    endif(ENABLE_CODE_ANALYSIS)
                    #"--template='{file}:{line}: warning: {id} ({severity}): {message}'"
                    #"--quiet"
                    #(.*?):(\d+):(\d+:)? [Ee]rror: (conflicting types for .*[`'"](.*)['"].*)
                    #(.*?):(\d+):(\d+:)?\s*(([Ww]arning)|(WARNING)): (.*)


endfunction()

# offcenter_v20_logging
# Basic version of cmake
function(offcenter_v20_logging default_value)
    option(LOG_V20_ACCESS "Log V20 Access" ${default_value})
    if(LOG_V20_ACCESS)
        message(STATUS "Logging V20 Access")
        add_definitions(-DLOG_V20_ACCESS)
        add_definitions(-DELPP_FRESH_LOG_FILE)
        add_definitions(-DELPP_THREAD_SAFE)
    endif()
endfunction()

# offcenter_version
# Version info
macro(offcenter_version project major minor patch)
    set(${project}_major_version ${major})
    set(${project}_minor_version ${minor})
    set(${project}_patch_version ${patch})
    set(${project}_version ${major}.${minor}.${patch})
endmacro()

# offcenter_example_test_dirs
# Set constants for example and test
macro(offcenter_example_test_dirs)
    set(CMAKE_INSTALL_EXAMPLE_DIR "example")  
    set(EXAMPLE_PREFIX "example")  
    set(CMAKE_INSTALL_TEST_DIR "test")  
    set(TEST_PREFIX "test")  
endmacro()

###############################################################################
# Thread Trace
macro(offcenter_thread_trace default_value)
    option(RUNNING_THREAD_TRACE "Running Thread Trace" ${default_value})
    if(RUNNING_THREAD_TRACE)
        message(STATUS "Tracing Running Threads")
        add_definitions(-DRUNNINGTHREADTRACE)
    endif()
endmacro()

###############################################################################
# Boost
macro(offcenter_find_boost)
    set(Boost_USE_STATIC_LIBS        ON)
    set(Boost_USE_DEBUG_LIBS        OFF)
    set(Boost_USE_RELEASE_LIBS       ON)
    set(Boost_USE_MULTITHREADED      ON)
    set(Boost_USE_STATIC_RUNTIME    OFF)
    find_package(Boost
        1.80
        COMPONENTS iostreams atomic thread system regex filesystem random chrono serialization program_options
    )
endmacro()

###############################################################################
# openssl
macro(offcenter_find_openssl)
    set(OPENSSL_USE_STATIC_LIBS TRUE)
    find_package(OpenSSL REQUIRED)
endmacro()

###############################################################################
# threads
macro(offcenter_find_threads)
    set(THREADS_PREFER_PTHREAD_FLAG ON)
    find_package(Threads REQUIRED)
endmacro()

###############################################################################
# offcenter_proj_constants
# Defines all Offcenter project contansts in one macro call
macro(offcenter_proj_setup proj_name major minor patch)
    offcenter_cxx()
    offcenter_version(${proj_name} ${major} ${minor} ${patch})
    offcenter_gnu_dirs()
    offcenter_example_test_dirs()

    set(PROJ_LIB_NAMES "")
    set(PROJ_NAMESPACE Offcenter)
    set(PROJ_CMAKE_DIR cmake)

    #offcenter_lib_setup()
    
    # set(LIB_TAG ${lib_tag})
    # set(LIB_TARGETS ${LIB_NAME}-targets)
    # set(LIB_NAMESPACE Offcenter)
    # set(LIB_CMAKE_DIR cmake)

    # set(LIB_NAMES ${LIB_NAMES} ${lib_name}) 
    # set(LIB_NAMES ${LIB_NAMES} PARENT_SCOPE)

    message(STATUS "Project: ${proj_name} version(${${proj_name}_version})")
endmacro()

###############################################################################
# offcenter_lib_constants
# Defines all Offcenter library contansts in one macro call
macro(offcenter_libs_setup)
    set(LIB_NAMES "")
endmacro()

###############################################################################
# offcenter_lib_constants
# Defines all Offcenter library contansts in one macro call
macro(offcenter_lib_setup lib_name lib_tag)
    set(LIB_NAME ${lib_name})
    set(LIB_TAG ${lib_tag})
    set(LIB_TARGETS ${LIB_NAME}-targets)
    set(LIB_NAMESPACE Offcenter)
    set(LIB_CMAKE_DIR cmake)
    set(LIB_COMMON_INC_BASE include/offcenter)

    message(STATUS "Library: ${LIB_NAME} tag(${LIB_TAG}) targets(${LIB_TARGETS}) namespace(${LIB_NAMESPACE}) cmake_dir(${LIB_CMAKE_DIR}) inc_base(${LIB_COMMON_INC_BASE})")
endmacro()