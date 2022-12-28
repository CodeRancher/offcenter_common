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

include(OffcenterBuild)

offcenter_cxx()
offcenter_elpp()
offcenter_lib_setup(offcenter_common_imgui common_imgui)
set(version 0.0.1)

set(IMGUI_DIR "." CACHE STRING "ImGui source directory")
message(STATUS "IMGUI_DIR       ${IMGUI_DIR}")

add_library(${LIB_NAME} "")

target_sources(${LIB_NAME}
	PRIVATE
		${IMGUI_DIR}/imgui.cpp
		${IMGUI_DIR}/imgui_draw.cpp
		${IMGUI_DIR}/imgui_tables.cpp
		${IMGUI_DIR}/imgui_widgets.cpp
		${IMGUI_DIR}/backends/imgui_impl_glfw.cpp
		${IMGUI_DIR}/backends/imgui_impl_opengl3.cpp
		${IMPLOT_DIR}/implot.cpp
		${IMPLOT_DIR}/implot_items.cpp
)

target_link_libraries(${LIB_NAME}
	offcenter_common_framework
	offcenter_common
	offcenter_common_program_options
	Boost::program_options
	Boost::system
	${EASYLOGGINGPP_LIBRARY}
	Threads::Threads
)

target_include_directories(${LIB_NAME}
	PUBLIC
		"$<BUILD_INTERFACE:${CMAKE_CURRENT_LIST_DIR}/include>"
		"$<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>"
)

target_include_directories(${LIB_NAME}
	SYSTEM PUBLIC
		${EASYLOGGINGPP_INCLUDE_DIR}
		${IMGUI_DIR}
		${IMGUI_DIR}/backends
)

include(OffcenterInstall)
offcenter_lib_install()

if(ENABLE_UNIT_TESTS)
#	add_subdirectory(test)
endif()

add_subdirectory(example)
