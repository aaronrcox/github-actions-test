# CMakeList.txt : Top-level CMake project file, do global configuration
# and include sub-projects here.

cmake_minimum_required (VERSION 3.8)

project ("EmscriptenProjects")

if(EMSCRIPTEN)
	set(CMAKE_BUILD_TYPE "Emscripten")
endif()

# LOCATE SDL2 LIBRARY
# =============================================================================
set(SDL2_DIR "${CMAKE_HOME_DIRECTORY}/libs/vc/SDL2-2.0.12")
set(SDL2_INCLUDE_DIR "${SDL2_DIR}/include")
set(SDL2_LIBRARY_DIR  "${SDL2_DIR}/lib/x64")
set(SDL2_LIBRARIES "${SDL2_LIBRARY_DIR}/SDL2.lib;${SDL2_LIBRARY_DIR}/SDL2main.lib;")
# =============================================================================


# Include sub-projects.
# =============================================================================
add_subdirectory ("projects/HelloWorld")
add_subdirectory ("projects/HelloSDL")
add_subdirectory ("projects/HelloOpenGL")
# =============================================================================




