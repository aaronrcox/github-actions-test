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
set(SDL2_LIBRARY_DIR "${SDL2_DIR}/lib/x64")
set(SDL2_LIBRARIES "${SDL2_LIBRARY_DIR}/SDL2.lib;${SDL2_LIBRARY_DIR}/SDL2main.lib;")
# =============================================================================

# LOCATE GLEW LIBRARY
# =============================================================================
set(GLEW_DIR "${CMAKE_HOME_DIRECTORY}/libs/vc/glew-2.1.0")
set(GLEW_INCLUDE_DIR "${GLEW_DIR}/include")
set(GLEW_LIBRARY_DIR "${GLEW_DIR}/lib/Release/x64")
set(GLEW_LIBRARIES "${GLEW_LIBRARY_DIR}/glew32s.lib;")
# =============================================================================

# Include sub-projects.
# =============================================================================
add_subdirectory ("projects/HelloWorld")
add_subdirectory ("projects/HelloSDL")
add_subdirectory ("projects/HelloOpenGL")
# =============================================================================




