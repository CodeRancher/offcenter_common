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
# @date   05-02-2019
#

include(OffcenterBuild)

offcenter_cxx()
offcenter_elpp()
offcenter_lib_setup(offcenter_common_framework common_framework)
set(version 0.0.1)

add_library(${LIB_NAME} STATIC)

target_sources(${LIB_NAME}
	PRIVATE
		#${CMAKE_CURRENT_LIST_DIR}/src/BasicAppFoundation.cpp
		#${CMAKE_CURRENT_LIST_DIR}/src/AMQPApp.cpp
		#${CMAKE_CURRENT_LIST_DIR}/src/DistributedLoggingApp.cpp
		#${CMAKE_CURRENT_LIST_DIR}/src/DistributedStatusApp.cpp
		#${CMAKE_CURRENT_LIST_DIR}/src/SOCIApp.cpp
		${CMAKE_CURRENT_LIST_DIR}/src/Utility.cpp
		${CMAKE_CURRENT_LIST_DIR}/src/AdminStatusProducer.cpp
		${CMAKE_CURRENT_LIST_DIR}/src/AdminStatusMessage.cpp
#		${CMAKE_CURRENT_LIST_DIR}/src/AdminStatusConsumer.cpp
		${CMAKE_CURRENT_LIST_DIR}/src/AdminControlProducer.cpp
		${CMAKE_CURRENT_LIST_DIR}/src/AdminControlMessage.cpp
#		${CMAKE_CURRENT_LIST_DIR}/src/AdminControlConsumer.cpp
		
	PUBLIC
		$<BUILD_INTERFACE:${CMAKE_CURRENT_LIST_DIR}/include/offcenter/common/framework/application/BasicApp.hpp>
		$<INSTALL_INTERFACE:include/offcenter/common/framework/application/BasicApp.hpp>
		
		$<BUILD_INTERFACE:${CMAKE_CURRENT_LIST_DIR}/include/offcenter/common/framework/application/AMQPApp.hpp>
		$<INSTALL_INTERFACE:include/offcenter/common/framework/application/AMQPApp.hpp>
		
		$<BUILD_INTERFACE:${CMAKE_CURRENT_LIST_DIR}/include/offcenter/common/framework/application/DistributedLoggingApp.hpp>
		$<INSTALL_INTERFACE:include/offcenter/common/framework/application/DistributedLoggingApp.hpp>
		
		$<BUILD_INTERFACE:${CMAKE_CURRENT_LIST_DIR}/include/offcenter/common/framework/application/DistributedStatusApp.hpp>
		$<INSTALL_INTERFACE:include/offcenter/common/framework/application/DistributedStatusApp.hpp>
		
		$<BUILD_INTERFACE:${CMAKE_CURRENT_LIST_DIR}/include/offcenter/common/framework/application/IBasicApp.hpp>
		$<INSTALL_INTERFACE:include/offcenter/common/framework/application/IBasicApp.hpp>
		
		$<BUILD_INTERFACE:${CMAKE_CURRENT_LIST_DIR}/include/offcenter/common/framework/application/BasicAppConfig.hpp>
		$<INSTALL_INTERFACE:include/offcenter/common/framework/application/BasicAppConfig.hpp>
		
		$<BUILD_INTERFACE:${CMAKE_CURRENT_LIST_DIR}/include/offcenter/common/framework/application/Utility.hpp>
		$<INSTALL_INTERFACE:include/offcenter/common/framework/application/Utility.hpp>
		
		$<BUILD_INTERFACE:${CMAKE_CURRENT_LIST_DIR}/include/offcenter/common/framework/program_options/BasicAppProgramOptions.hpp>
		$<INSTALL_INTERFACE:include/offcenter/common/framework/program_options/BasicAppProgramOptions.hpp>
		
		$<BUILD_INTERFACE:${CMAKE_CURRENT_LIST_DIR}/include/offcenter/common/framework/admin/AdminStatusMessage.hpp>
		$<INSTALL_INTERFACE:include/offcenter/common/framework/admin/AdminStatusMessage.hpp>
		
		$<BUILD_INTERFACE:${CMAKE_CURRENT_LIST_DIR}/include/offcenter/common/framework/admin/AdminStatusProducer.hpp>
		$<INSTALL_INTERFACE:include/offcenter/common/framework/admin/AdminStatusProducer.hpp>
		
		$<BUILD_INTERFACE:${CMAKE_CURRENT_LIST_DIR}/include/offcenter/common/framework/admin/AdminControlProducer.hpp>
		$<INSTALL_INTERFACE:include/offcenter/common/framework/admin/AdminControlProducer.hpp>
		
		$<BUILD_INTERFACE:${CMAKE_CURRENT_LIST_DIR}/include/offcenter/common/framework/admin/AdminControlMessage.hpp>
		$<INSTALL_INTERFACE:include/offcenter/common/framework/admin/AdminControlMessage.hpp>
		
		$<BUILD_INTERFACE:${CMAKE_CURRENT_LIST_DIR}/include/offcenter/common/framework/admin/AdminControlConsumer.hpp>
		$<INSTALL_INTERFACE:include/offcenter/common/framework/admin/AdminControlConsumer.hpp>
		
		$<BUILD_INTERFACE:${CMAKE_CURRENT_LIST_DIR}/include/offcenter/common/framework/application/AppManager.hpp>
		$<INSTALL_INTERFACE:include/offcenter/common/framework/application/AppManager.hpp>
)

target_include_directories(${LIB_NAME}
	PUBLIC
		"$<BUILD_INTERFACE:${CMAKE_CURRENT_LIST_DIR}/include>"
		"$<BUILD_INTERFACE:${CMAKE_CURRENT_LIST_DIR}/../common/include>"
		"$<BUILD_INTERFACE:${CMAKE_CURRENT_LIST_DIR}/../amqp/include>"
		"$<BUILD_INTERFACE:${CMAKE_CURRENT_LIST_DIR}/../program_options/include>"
		"$<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>"
)

target_include_directories(${LIB_NAME}
	SYSTEM PUBLIC
		${ACTIVEMQCPP_INCLUDE_DIR}
		${APR_INCLUDE_DIR}
		${EASYLOGGINGPP_INCLUDE_DIR}
)

include(OffcenterInstall)
offcenter_lib_install()

if(ENABLE_UNIT_TESTS)
	add_subdirectory(test)
endif()

add_subdirectory(example)

