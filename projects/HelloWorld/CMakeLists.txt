
cmake_minimum_required (VERSION 3.8)

# Add source to this project's executable.
add_executable (HelloWorld "src/main.cpp" "inc/Application.h" "src/Application.cpp")

include_directories("inc;")

# TODO: Add tests and install targets if needed.

if (EMSCRIPTEN)
	set(CMAKE_EXECUTABLE_SUFFIX ".html")
    set(CMAKE_BINARY_DIR "${CMAKE_HOME_DIRECTORY}/bin/Emscripten/")
    set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR})
elseif(MSVC)
    set(CMAKE_BINARY_DIR "${CMAKE_HOME_DIRECTORY}/bin/${CMAKE_BUILD_TYPE}/")
    set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR})
endif()
