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

offcenter_cxx()
offcenter_elpp()

offcenter_exe_constants(distributed_system_manager)

add_executable(${EXE_NAME} "")

target_sources(${EXE_NAME}
	PRIVATE
		${CMAKE_CURRENT_LIST_DIR}/src/distributed_system_manager.cpp
)