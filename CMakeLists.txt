project(DirMonitorExt)
cmake_minimum_required(VERSION 3.7)

include(conan_include.cmake)

add_library(dir_monitor_ext_lib
	INTERFACE
)

target_include_directories(dir_monitor_ext_lib
	INTERFACE
		${PROJECT_SOURCE_DIR}/include
)

target_link_libraries(dir_monitor_ext_lib
	INTERFACE
		CONAN_PKG::dir_monitor
		CONAN_PKG::Boost.Asio
)


add_executable(dir_monitor_ext_example
	${PROJECT_SOURCE_DIR}/example/example.cpp
)

target_link_libraries(dir_monitor_ext_example
	CONAN_PKG::dir_monitor
	CONAN_PKG::Boost.Asio
	dir_monitor_ext_lib
)

add_executable(file_trigger_tests 
	${PROJECT_SOURCE_DIR}/test/file_trigger_tests.cpp
)

target_link_libraries(file_trigger_tests
	CONAN_PKG::dir_monitor
	CONAN_PKG::Boost.Asio
	dir_monitor_ext_lib
)

add_executable(file_monitor_tests
	${PROJECT_SOURCE_DIR}/test/file_monitor_tests.cpp
)

target_link_libraries(file_monitor_tests
	CONAN_PKG::dir_monitor
	CONAN_PKG::Boost.Asio
	dir_monitor_ext_lib
)

# https://cmake.org/cmake/help/v3.4/command/add_test.html 
# add_test(<name> <command> [<arg>...])
enable_testing()
add_test(NAME file_trigger_tests COMMAND file_trigger_tests)
add_test(NAME file_monitor_tests COMMAND file_monitor_tests)
