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
# @date   09-15-2021
#


set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(offcenter_common_threading_single_thread_example
	${CMAKE_CURRENT_LIST_DIR}/src/single_thread_example.cpp
)

target_link_libraries(offcenter_common_threading_single_thread_example
	offcenter_common_threading
	${EASYLOGGINGPP_LIBRARY}
	Threads::Threads
)

target_include_directories(offcenter_common_threading_single_thread_example
	PUBLIC
		${CMAKE_CURRENT_LIST_DIR}/../../include
)

add_executable(offcenter_common_threading_multi_thread_example
	${CMAKE_CURRENT_LIST_DIR}/src/multi_thread_example.cpp
)

target_link_libraries(offcenter_common_threading_multi_thread_example
	offcenter_common_threading
	${EASYLOGGINGPP_LIBRARY}
	Threads::Threads
)

target_include_directories(offcenter_common_threading_multi_thread_example
	PUBLIC
		${CMAKE_CURRENT_LIST_DIR}/../../include
)

add_executable(offcenter_common_threading_thread_array_example
	${CMAKE_CURRENT_LIST_DIR}/src/thread_array_example.cpp
)

target_link_libraries(offcenter_common_threading_thread_array_example
	offcenter_common_threading
	${EASYLOGGINGPP_LIBRARY}
	Threads::Threads
)

target_include_directories(offcenter_common_threading_thread_array_example
	PUBLIC
		${CMAKE_CURRENT_LIST_DIR}/../../include
)

add_executable(offcenter_common_threading_blockable_thread
	${CMAKE_CURRENT_LIST_DIR}/src/blocked_thread_example.cpp
)

target_link_libraries(offcenter_common_threading_blockable_thread
	offcenter_common_threading
	${EASYLOGGINGPP_LIBRARY}
	Threads::Threads
)

target_include_directories(offcenter_common_threading_blockable_thread
	PUBLIC
		${CMAKE_CURRENT_LIST_DIR}/../../include
)

add_executable(offcenter_common_threading_data_monitor_thread
	${CMAKE_CURRENT_LIST_DIR}/src/data_monitor_example.cpp
)

target_link_libraries(offcenter_common_threading_data_monitor_thread
	offcenter_common_threading
	${EASYLOGGINGPP_LIBRARY}
	Threads::Threads
)

target_include_directories(offcenter_common_threading_data_monitor_thread
	PUBLIC
		${CMAKE_CURRENT_LIST_DIR}/../../include
)
