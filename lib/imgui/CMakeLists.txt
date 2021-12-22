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

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(IMGUI_DIR "." CACHE STRING "ImGui source directory")
message(STATUS "IMGUI_DIR       ${IMGUI_DIR}")

add_library(offcenter_common_imgui "")

target_sources(offcenter_common_imgui
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

target_include_directories(offcenter_common_imgui
	BEFORE PUBLIC
		${CMAKE_CURRENT_LIST_DIR}/include
	SYSTEM
		${IMGUI_DIR}
		${IMGUI_DIR}/backends
)

target_link_libraries(offcenter_common_imgui
	offcenter_common_framework
	offcenter_common
	offcenter_common_program_options
	Boost::program_options
	Boost::system
	${EASYLOGGINGPP_LIBRARY}
	Threads::Threads
)


#install(TARGETS offcenter_common_framework EXPORT offcenter_common_framework DESTINATION lib)
#install (
#	DIRECTORY ${CMAKE_CURRENT_LIST_DIR}/include/
#	DESTINATION include
#	FILES_MATCHING PATTERN "*.h*"
#)

add_subdirectory(example)
if(ENABLE_UNIT_TESTS)
#	add_subdirectory(test)
endif()


