project(DirMonitorExt)
cmake_minimum_required(VERSION 3.7)

include(conan_include.cmake)

add_library(${PROJECT_NAME}
	INTERFACE
)

target_include_directories(${PROJECT_NAME}
	INTERFACE
		${PROJECT_SOURCE_DIR}/include
)

target_link_libraries(${PROJECT_NAME}
	INTERFACE
		CONAN_PKG::dir_monitor
		CONAN_PKG::Boost
)


add_executable(${PROJECT_NAME}_impl
	${PROJECT_SOURCE_DIR}/src/main_impl.cpp
)

target_link_libraries(${PROJECT_NAME}_impl
	CONAN_PKG::dir_monitor
	CONAN_PKG::Boost
	CONAN_PKG::jsonformoderncpp
	${PROJECT_NAME}
)
