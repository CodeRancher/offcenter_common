# require C++14
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON)

add_compile_definitions(ELPP_THREAD_SAFE)

add_executable(distributed_system_monitor "")

target_sources(distributed_system_monitor
	PRIVATE
		${CMAKE_CURRENT_LIST_DIR}/src/distributed_system_monitor.cpp
)