
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(Threads REQUIRED)

cmake_policy(SET CMP0074 NEW)

#set(OPENSSL_USE_STATIC_LIBS TRUE)
#find_package(OpenSSL REQUIRED)

add_compile_definitions(ELPP_THREAD_SAFE)
add_compile_definitions(ELPP_FRESH_LOG_FILE)
add_compile_definitions(ELPP_NO_DEFAULT_LOG_FILE)

set(APP_NAME waitfor_sigint)

###############################################################################
# Example Consumer
add_executable (${APP_NAME}
    ${CMAKE_CURRENT_LIST_DIR}/src/waitfor_sigint.cpp
    ${CMAKE_CURRENT_LIST_DIR}/src/WaitforSigintApp.cpp
)

target_link_libraries(${APP_NAME}
	offcenter_common_framework
	offcenter_common
	offcenter_common_threading
	offcenter_common_program_options
	Boost::program_options
	${EASYLOGGINGPP_LIBRARY}
	Threads::Threads
#	OpenSSL::SSL
)

target_include_directories(${APP_NAME}
	BEFORE PUBLIC
		${CMAKE_CURRENT_LIST_DIR}/include
	SYSTEM
		${EASYLOGGINGPP_INCLUDE_DIR}
)


