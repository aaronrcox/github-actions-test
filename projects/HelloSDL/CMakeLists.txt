
cmake_minimum_required (VERSION 3.8)

# Add source to this project's executable.
add_executable (HelloSDL "src/main.cpp"   "inc/Application.h" "src/Application.cpp")

include_directories("inc;")

# DEFINE OUTPUT DIRECTORY
# =============================================================================
if (EMSCRIPTEN)

    set(USE_FLAGS "-s USE_SDL=2 --preload-file ${CMAKE_HOME_DIRECTORY}/projects/HelloSDL/HelloSDLAssets/@/HelloSDLAssets/")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${USE_FLAGS}")
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${USE_FLAGS}")
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} ${USE_FLAGS}")

	set(CMAKE_EXECUTABLE_SUFFIX ".html")
    set(CMAKE_BINARY_DIR "${CMAKE_HOME_DIRECTORY}/bin/Emscripten/${OUTPUT_NAME}")
    set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR})
else()
    set(CMAKE_BINARY_DIR "${CMAKE_HOME_DIRECTORY}/bin/${CMAKE_BUILD_TYPE}/${OUTPUT_NAME}")
    set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR})
endif()
# =============================================================================


# Reference 3rd Party Libraries
# =============================================================================
if (EMSCRIPTEN)
    # Do we need to do anything for emscripten?
    # Emscripten includes SDL2 by default
elseif(MSVC)
    include_directories("${SDL2_INCLUDE_DIR};")
    target_link_libraries(HelloSDL "${SDL2_LIBRARIES}")
endif()
# =============================================================================

# BUILD STEPS - Copy assets
# =============================================================================
if (EMSCRIPTEN)
    
elseif(MSVC)
    
    # copy SDL2.dll to output directory
    add_custom_command(TARGET HelloSDL POST_BUILD   
        COMMAND ${CMAKE_COMMAND} -E copy_if_different 
        "${SDL2_LIBRARY_DIR}/SDL2.dll" ${EXECUTABLE_OUTPUT_PATH})

    # copy asset directory to output folder
    add_custom_command(TARGET HelloSDL POST_BUILD   
        COMMAND ${CMAKE_COMMAND} -E copy_directory 
        "${CMAKE_HOME_DIRECTORY}/projects/HelloSDL/HelloSDLAssets" "${EXECUTABLE_OUTPUT_PATH}/HelloSDLAssets")
endif()