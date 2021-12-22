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

add_compile_definitions(ELPP_THREAD_SAFE)
add_compile_definitions(ELPP_FRESH_LOG_FILE)
add_compile_definitions(ELPP_NO_DEFAULT_LOG_FILE)

###############################################################################
# Copy config file
#configure_file(${CMAKE_CURRENT_LIST_DIR}/config.ini config.ini COPYONLY)
#file(COPY ${CMAKE_CURRENT_LIST_DIR}/config.ini DESTINATION ${CMAKE_BINARY_DIR}/bin)
#message(STATUS "COPY ${CMAKE_CURRENT_LIST_DIR}/config.ini DESTINATION ${CMAKE_BINARY_DIR}/bin")

#add_compile_definitions(IMGUI_IMPL_OPENGL_LOADER_GL3W)
add_compile_definitions(IMGUI_IMPL_OPENGL_ES2)
#add_compile_definitions(IMGUI_IMPL_OPENGL_LOADER_GLEW)

find_package(OpenGL REQUIRED)
find_package(glfw3 REQUIRED)
#find_package(glew REQUIRED)

set(IMPLOT_DIR "." CACHE STRING "ImPlot source directory")
message(STATUS "IMPLOT_DIR       ${IMPLOT_DIR}")

###############################################################################
# ImGui Example
add_executable (offcenter_common_imgui_example
	${IMGUI_DIR}/imgui_demo.cpp
    ${CMAKE_CURRENT_LIST_DIR}/src/imgui_example.cpp
    ${CMAKE_CURRENT_LIST_DIR}/src/ImGuiExampleApp.cpp
)

target_link_libraries(offcenter_common_imgui_example
	offcenter_common_imgui
	Boost::program_options
	${EASYLOGGINGPP_LIBRARY}
	Threads::Threads
	OpenSSL::SSL
	glfw
	OpenGL::GL
	${CMAKE_DL_LIBS} 
)

target_include_directories(offcenter_common_imgui_example
	BEFORE PUBLIC
		${CMAKE_CURRENT_LIST_DIR}/include
	SYSTEM
		${IMGUI_DIR}
		${IMGUI_DIR}/backends
		${IMPLOT_DIR}
		${EASYLOGGINGPP_INCLUDE_DIR}
)

###############################################################################
# ImPlot Graph Example
add_executable (offcenter_common_implot_graph_example
	${IMPLOT_DIR}/implot_demo.cpp
	${IMGUI_DIR}/imgui_demo.cpp
    ${CMAKE_CURRENT_LIST_DIR}/src/implot_graph_example.cpp
    ${CMAKE_CURRENT_LIST_DIR}/src/ImPlotGraphExampleApp.cpp
)

target_link_libraries(offcenter_common_implot_graph_example
	offcenter_common_imgui
	Boost::program_options
	${EASYLOGGINGPP_LIBRARY}
	Threads::Threads
	OpenSSL::SSL
	glfw
	OpenGL::GL
	${CMAKE_DL_LIBS} 
)

target_include_directories(offcenter_common_implot_graph_example
	BEFORE PUBLIC
		${CMAKE_CURRENT_LIST_DIR}/include
	SYSTEM
		${IMGUI_DIR}
		${IMGUI_DIR}/backends
		${IMPLOT_DIR}
		${EASYLOGGINGPP_INCLUDE_DIR}
)

###############################################################################
# ImPlot Graph Example
add_executable (offcenter_common_implot_line_example
    ${CMAKE_CURRENT_LIST_DIR}/src/implot_line_example.cpp
    ${CMAKE_CURRENT_LIST_DIR}/src/ImPlotLineExampleApp.cpp
)

target_link_libraries(offcenter_common_implot_line_example
	offcenter_common_imgui
	Boost::program_options
	${EASYLOGGINGPP_LIBRARY}
	Threads::Threads
	OpenSSL::SSL
	glfw
	OpenGL::GL
	${CMAKE_DL_LIBS} 
)

target_include_directories(offcenter_common_implot_line_example
	BEFORE PUBLIC
		${CMAKE_CURRENT_LIST_DIR}/include
	SYSTEM
		${IMGUI_DIR}
		${IMGUI_DIR}/backends
		${IMPLOT_DIR}
		${EASYLOGGINGPP_INCLUDE_DIR}
)