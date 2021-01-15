cmake_minimum_required(VERSION 3.0)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -Wall")

project(bufio VERSION 1 LANGUAGES C CXX)

set(SRC_FILES main.cpp src/quene.cpp src/bufio.cpp)
add_executable(${PROJECT_NAME} ${SRC_FILES})

set_target_properties(${PROJECT_NAME}
	PROPERTIES
	RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/debug"
)

include_directories("include/")
add_definitions(-DDEBUG)

