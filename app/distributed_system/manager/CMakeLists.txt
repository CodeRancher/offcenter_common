
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_STANDARD_REQUIRED ON)


add_compile_definitions(ELPP_THREAD_SAFE)

add_executable(distributed_system_manager "")

target_sources(distributed_system_manager
	PRIVATE
		${CMAKE_CURRENT_LIST_DIR}/src/distributed_system_manager.cpp
)