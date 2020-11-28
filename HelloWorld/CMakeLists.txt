# CMakeList.txt : CMake project for IntroToOpenGL, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)

# Add source to this project's executable.
add_executable (HelloWorld "main.cpp")

# TODO: Add tests and install targets if needed.

if (EMSCRIPTEN)
	set(CMAKE_EXECUTABLE_SUFFIX ".html")
    set(CMAKE_BINARY_DIR "${CMAKE_HOME_DIRECTORY}/bin/${PROJECT_NAME}/Emscripten")
    set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR})
else()
    set(CMAKE_BINARY_DIR "${CMAKE_HOME_DIRECTORY}/bin/${PROJECT_NAME}/${CMAKE_BUILD_TYPE}")
    set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR})
endif()
