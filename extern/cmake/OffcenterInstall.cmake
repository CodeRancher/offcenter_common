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
# @file   OffcenterInstall.cmake
# @author Scott Brauer
# @date   09-25-2022
#

# function(offcenter_lib_install LIB_TARGETS LIB_NAMESPACE LIB_CMAKE_DIR LIB_NAME version LIB_TAG)

#     install(
#         TARGETS ${LIB_NAME}
#         EXPORT  ${LIB_TARGETS}
#         LIBRARY DESTINATION lib
#         ARCHIVE DESTINATION lib
#         RUNTIME DESTINATION bin
#         INCLUDES DESTINATION include
#     )
    
#     install (
#         DIRECTORY ${CMAKE_CURRENT_LIST_DIR}/include/
#         DESTINATION include
#         FILES_MATCHING PATTERN "*.h*"
#     )
    
#     install(
#         EXPORT ${LIB_TARGETS}
#         FILE ${LIB_TARGETS}.cmake
#         NAMESPACE ${LIB_NAMESPACE}::
#         #DESTINATION lib/cmake/${LIB_CMAKE_DIR}
#         DESTINATION lib/cmake
#     )

#     include(CMakePackageConfigHelpers)
   
#     set_property(TARGET ${LIB_NAME} PROPERTY VERSION ${version})
#     set_property(TARGET ${LIB_NAME} PROPERTY SOVERSION 0)
#     set_property(TARGET ${LIB_NAME} PROPERTY INTERFACE_${LIB_TAG}_MAJOR_VERSION 0)
#     set_property(TARGET ${LIB_NAME} APPEND PROPERTY COMPATIBLE_INTERFACE_STRING ${LIB_TAG}_MAJOR_VERSION)

#     # generate the version file for the config file
#     write_basic_package_version_file(
#         "${CMAKE_CURRENT_BINARY_DIR}/${LIB_TAG}ConfigVersion.cmake"
#         VERSION "${version}"
#         COMPATIBILITY AnyNewerVersion
#     )

#     # create config file
#     configure_package_config_file(
#         "${CMAKE_CURRENT_SOURCE_DIR}/${LIB_NAME}-config.cmake.in"
#         "${CMAKE_CURRENT_BINARY_DIR}/${LIB_TAG}-config.cmake"
#         INSTALL_DESTINATION cmake
#         PATH_VARS ${CMAKE_CURRENT_LIST_DIR}/include/
#     )

#     # install config files
#     install(FILES
#         "${CMAKE_CURRENT_BINARY_DIR}/${LIB_TAG}Config.cmake"
#         "${CMAKE_CURRENT_BINARY_DIR}/${LIB_TAG}ConfigVersion.cmake"
#         #DESTINATION lib/cmake/${LIB_CMAKE_DIR}
#         DESTINATION lib/cmake
#     )

#     # generate the export targets for the build tree
#     export(EXPORT ${LIB_TARGETS}
#         FILE "${CMAKE_CURRENT_BINARY_DIR}/cmake/${LIB_TARGETS}.cmake"
#         NAMESPACE ${LIB_NAMESPACE}::
#     )

# endfunction(offcenter_lib_install)

###############################################################################
#
function(offcenter_lib_install_2)

    set(${LIB_NAME}_INCLUDE_DIRS "include")
    set(CMAKE_CONFIG_DEST "cmake")

    install(
        TARGETS ${LIB_NAME}
        EXPORT  ${LIB_TARGETS}
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
    
    install(
        EXPORT ${LIB_TARGETS}
        FILE ${LIB_TARGETS}.cmake
        NAMESPACE Offcenter
        DESTINATION cmake
    )

    include(CMakePackageConfigHelpers)

    # # create config file
    # configure_package_config_file(
    #     "${CMAKE_CURRENT_SOURCE_DIR}/${LIB_NAME}-config.cmake.in"
    #     "${CMAKE_CURRENT_BINARY_DIR}/${LIB_NAME}-config.cmake"
    #     INSTALL_DESTINATION "cmake"
    #     NO_SET_AND_CHECK_MACRO
    #     NO_CHECK_REQUIRED_COMPONENTS_MACRO
    #     # PATH_VARS
    #     # INCLUDE_INSTALL_DIR
    #     # SYSCONFIG_INSTALL_DIR
    #     #PATH_VARS cmake
    # )

    # # generate the version file for the config file
    # write_basic_package_version_file(
    #     "${CMAKE_CURRENT_BINARY_DIR}/${LIB_NAME}-configversion.cmake"
    #     VERSION "${PROJECT_NAME}_version"
    #     COMPATIBILITY AnyNewerVersion
    # )

    # # install config files
    # install(
    #     FILES
    #     "${CMAKE_CURRENT_BINARY_DIR}/${LIB_NAME}-config.cmake"
    #     "${CMAKE_CURRENT_BINARY_DIR}/${LIB_NAME}-configversion.cmake"
    #     #DESTINATION lib/cmake/${LIB_CMAKE_DIR}
    #     DESTINATION cmake
    # )
    
   
    # set_property(TARGET ${LIB_NAME} PROPERTY VERSION ${version})
    # set_property(TARGET ${LIB_NAME} PROPERTY SOVERSION 0)
    # set_property(TARGET ${LIB_NAME} PROPERTY INTERFACE_${LIB_TAG}_MAJOR_VERSION 0)
    # set_property(TARGET ${LIB_NAME} APPEND PROPERTY COMPATIBLE_INTERFACE_STRING ${LIB_TAG}_MAJOR_VERSION)

    # generate the version file for the config file
#     write_basic_package_version_file(
#         "${CMAKE_CURRENT_BINARY_DIR}/${LIB_NAME}-configversion.cmake"
#         VERSION "${version}"
#         COMPATIBILITY AnyNewerVersion
#     )

#     # create config file
#     configure_package_config_file(
#         "${CMAKE_CURRENT_SOURCE_DIR}/${LIB_NAME}-config.cmake.in"
#         "${CMAKE_CURRENT_BINARY_DIR}/${LIB_NAME}-config.cmake"
#         INSTALL_DESTINATION "${CMAKE_CONFIG_DEST}"
#         PATH_VARS ${LIB_NAME}_INCLUDE_DIRS
#     )

#     # install config files
#     install(
#         FILES
#         "${CMAKE_CURRENT_BINARY_DIR}/${LIB_NAME}-config.cmake"
#         "${CMAKE_CURRENT_BINARY_DIR}/${LIB_NAME}-configversion.cmake"
#         #DESTINATION lib/cmake/${LIB_CMAKE_DIR}
#         DESTINATION cmake
#     )

#     # generate the export targets for the build tree
#     install(
#         EXPORT ${LIB_TARGETS}
#         DESTINATION ${CMAKE_CONFIG_DEST}
#         FILE "${LIB_TARGETS}.cmake"
# #        NAMESPACE ${LIB_NAMESPACE}::
#     )
#     export(
#         EXPORT ${LIB_TARGETS}
#         DESTINATION ${CMAKE_CONFIG_DEST}
#         FILE "${LIB_TARGETS}.cmake"
# #        NAMESPACE ${LIB_NAMESPACE}::
#     )

endfunction()

# macro(header_interface build_dir install_dir header_file)
#     $<BUILD_INTERFACE:${build_dir}/${header_file}
# 	$<INSTALL_INTERFACE:${install_dir}/${header_file}
# endmacro()

# macro(headers_interface build_dir install_dir)
#     foreach(header_file IN LISTS ARGN)
#         header_interface(${build_dir} ${install_dir} ${header_file})
#     endforeach()
# endmacro()

###############################################################################
#
function(offcenter_libs_install LIB_TARGET)

    message(STATUS "offcenter_libs_install: LIB_NAMES: ${LIB_NAMES} LIB_TARGET(${LIB_TARGET})")

    install(
        TARGETS ${LIB_NAMES}
        EXPORT  ${LIB_TARGET}
        LIBRARY DESTINATION lib
        ARCHIVE DESTINATION lib
        RUNTIME DESTINATION bin
        INCLUDES DESTINATION include
    )
    
    # install (
    #     DIRECTORY ${CMAKE_CURRENT_LIST_DIR}/include/
    #     DESTINATION include
    #     FILES_MATCHING PATTERN "*.h*"
    # )

    install(
        EXPORT ${LIB_TARGET}
        FILE ${LIB_TARGET}.cmake
        NAMESPACE Offcenter
        DESTINATION cmake
    )

    # # generate the version file for the config file
    # write_basic_package_version_file(
    #     "${CMAKE_CURRENT_BINARY_DIR}/offcenter_common-configversion.cmake"
    #     VERSION "${PROJECT_NAME}_version"
    #     COMPATIBILITY AnyNewerVersion
    # )

    # # create config file
    # configure_package_config_file(
    #     "${CMAKE_CURRENT_SOURCE_DIR}/offcenter_common-config.cmake.in"
    #     "${CMAKE_CURRENT_BINARY_DIR}/offcenter_common-config.cmake"
    #     INSTALL_DESTINATION "cmake"
    #     #PATH_VARS cmake
    # )

    # # install config files
    # install(
    #     FILES
    #     "${CMAKE_CURRENT_BINARY_DIR}/offcenter_common-config.cmake"
    #     "${CMAKE_CURRENT_BINARY_DIR}/offcenter_common-configversion.cmake"
    #     #DESTINATION lib/cmake/${LIB_CMAKE_DIR}
    #     DESTINATION cmake
    # )

    # # generate the version file for the config file
    # write_basic_package_version_file(
    #     "${CMAKE_CURRENT_BINARY_DIR}/offcenter_common-configversion.cmake"
    #     VERSION "${PROJECT_NAME}_version"
    #     COMPATIBILITY AnyNewerVersion
    # )

    # # create config file
    # configure_package_config_file(
    #     "${CMAKE_CURRENT_SOURCE_DIR}/offcenter_common-config.cmake.in"
    #     "${CMAKE_CURRENT_BINARY_DIR}/offcenter_common-config.cmake"
    #     INSTALL_DESTINATION "cmake"
    #     #PATH_VARS cmake
    # )

    # # install config files
    # install(
    #     FILES
    #     "${CMAKE_CURRENT_BINARY_DIR}/offcenter_common-config.cmake"
    #     "${CMAKE_CURRENT_BINARY_DIR}/offcenter_common-configversion.cmake"
    #     #DESTINATION lib/cmake/${LIB_CMAKE_DIR}
    #     DESTINATION cmake
    # )

endfunction()

###############################################################################
#
macro(offcenter_proj_install)
    #message(STATUS "offcenter_proj_install: LIB_NAMES: ${LIB_NAMES} PROJ_LIB_NAMES: ${PROJ_LIB_NAMES}")
    message(STATUS "offcenter_proj_install: PROJ_LIB_NAMES: ${PROJ_LIB_NAMES}")

    set(TARGET_NAME ${PROJECT_NAME}-targets)

    install(
        TARGETS ${PROJ_LIB_NAMES}
        EXPORT  ${TARGET_NAME}
        LIBRARY DESTINATION lib
        ARCHIVE DESTINATION lib
        RUNTIME DESTINATION bin
        INCLUDES DESTINATION include
    )

    install(
        EXPORT ${TARGET_NAME}
        FILE ${TARGET_NAME}.cmake
        NAMESPACE ${PROJ_NAMESPACE}::
        DESTINATION ${PROJ_CMAKE_DIR}
    )

    include(CMakePackageConfigHelpers)

    # create config file
    configure_package_config_file(
        "${CMAKE_CURRENT_SOURCE_DIR}/${PROJECT_NAME}-config.cmake.in"
        "${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}-config.cmake"
        INSTALL_DESTINATION "cmake"
        NO_SET_AND_CHECK_MACRO
        #NO_CHECK_REQUIRED_COMPONENTS_MACRO
        # PATH_VARS
        # INCLUDE_INSTALL_DIR
        # SYSCONFIG_INSTALL_DIR
        #PATH_VARS cmake
    )
    
    # generate the version file for the config file
    write_basic_package_version_file(
        "${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}-configversion.cmake"
        VERSION "${PROJECT_NAME}_version"
        COMPATIBILITY AnyNewerVersion
    )

    # install config files
    install(
        FILES
        "${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}-config.cmake"
        "${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}-configversion.cmake"
        #DESTINATION lib/cmake/${LIB_CMAKE_DIR}
        DESTINATION ${PROJ_CMAKE_DIR}
    )

endmacro()

###############################################################################
#
macro(offcenter_libs_install)
    #message(STATUS "offcenter_libs_install before: PROJ_LIB_NAMES: ${PROJ_LIB_NAMES} LIB_NAMES: ${LIB_NAMES}")
    set(PROJ_LIB_NAMES ${PROJ_LIB_NAMES} ${LIB_NAMES} PARENT_SCOPE)
    #message(STATUS "offcenter_libs_install after: PROJ_LIB_NAMES: ${PROJ_LIB_NAMES} LIB_NAMES: ${LIB_NAMES}")
    message(STATUS "offcenter_libs_install: LIB_NAMES: ${LIB_NAMES}")
endmacro()

###############################################################################
#
macro(offcenter_libs_install_no_lib_dir)
    #message(STATUS "offcenter_libs_install before: PROJ_LIB_NAMES: ${PROJ_LIB_NAMES} LIB_NAMES: ${LIB_NAMES}")
    set(PROJ_LIB_NAMES ${PROJ_LIB_NAMES} ${LIB_NAMES})
    #message(STATUS "offcenter_libs_install after: PROJ_LIB_NAMES: ${PROJ_LIB_NAMES} LIB_NAMES: ${LIB_NAMES}")
    message(STATUS "offcenter_libs_install: LIB_NAMES: ${LIB_NAMES}")
endmacro()

###############################################################################
#
macro(offcenter_lib_install)
    #message(STATUS "offcenter_lib_install before: LIB_NAMES: ${LIB_NAMES} LIB_NAME: ${LIB_NAME}")
    set(LIB_NAMES ${LIB_NAMES} ${LIB_NAME} PARENT_SCOPE)
    #message(STATUS "offcenter_lib_install after: LIB_NAMES: ${LIB_NAMES} LIB_NAME: ${LIB_NAME}")
    message(STATUS "offcenter_lib_install: LIB_NAME: ${LIB_NAME}")

    install (
        DIRECTORY ${CMAKE_CURRENT_LIST_DIR}/include/
        DESTINATION include
        FILES_MATCHING PATTERN "*.h*"
    )

endmacro()

###############################################################################
#
macro(offcenter_exe_install)
    message(STATUS "offcenter_exe_install: EXE_NAME: ${EXE_NAME}")

    install(
        TARGETS ${EXE_NAME}
        LIBRARY DESTINATION lib
        ARCHIVE DESTINATION lib
        RUNTIME DESTINATION bin
        INCLUDES DESTINATION include
    )

endmacro()

###############################################################################
# offcenter_exe_config_file
# Copy a config file to bin
macro(offcenter_exe_config_file config_file)
    file(COPY ${config_file} DESTINATION ${CMAKE_BINARY_DIR}/bin)
    message(STATUS "COPY ${config_file} DESTINATION ${CMAKE_BINARY_DIR}/bin")
endmacro()