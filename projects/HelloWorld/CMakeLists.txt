
cmake_minimum_required (VERSION 3.8)

project("HelloWorld")

# Add source to this project's executable.
add_executable (HelloWorld "src/main.cpp" "inc/Application.h" "src/Application.cpp")

include_directories("inc;")

if(EMSCRIPTEN)
	set(CMAKE_EXECUTABLE_SUFFIX ".html")
endif()

set(CMAKE_BINARY_DIR "${CMAKE_HOME_DIRECTORY}/bin/${CMAKE_BUILD_TYPE}/${PROJECT_NAME}/")
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR})