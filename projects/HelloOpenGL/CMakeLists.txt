
cmake_minimum_required (VERSION 3.8)

project("HelloOpenGL")

# Add source to this project's executable.
add_executable ("${PROJECT_NAME}" 
    "src/main.cpp"   
    "inc/Application.h" 
    "src/Application.cpp" 
    "inc/HelloOpenGLApp.h" 
    "src/HelloOpenGLApp.cpp"
)

include_directories("inc;")

# DEFINE OUTPUT DIRECTORY
# =============================================================================
if (EMSCRIPTEN)
    
    set(USE_FLAGS "-s FULL_ES2=1 -s USE_SDL=2 --preload-file ${CMAKE_HOME_DIRECTORY}/projects/${PROJECT_NAME}/assets/@/assets/")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${USE_FLAGS}")
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${USE_FLAGS}")
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} ${USE_FLAGS}")

	set(CMAKE_EXECUTABLE_SUFFIX ".html")
endif()

set(CMAKE_BINARY_DIR "${CMAKE_HOME_DIRECTORY}/bin/${CMAKE_BUILD_TYPE}/${PROJECT_NAME}/")
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR})

# =============================================================================


# Reference 3rd Party Libraries
# =============================================================================
if (EMSCRIPTEN)
    # SDL2 library suppoerted via USE_SDL=2 from emscripten ports.
    # 
elseif(MSVC)

    add_compile_definitions(GLEW_STATIC)

    include_directories("${SDL2_INCLUDE_DIR};")
    include_directories("${GLEW_INCLUDE_DIR};")

    target_link_libraries(${PROJECT_NAME} "${SDL2_LIBRARIES}")
    target_link_libraries(${PROJECT_NAME} "${GLEW_LIBRARIES}")
    target_link_libraries(${PROJECT_NAME} "OpenGL32.lib")

    message("GLEW LIBS: ${GLEW_LIBRARIES}")

endif()
# =============================================================================

# BUILD STEPS - Copy assets
# =============================================================================
if (EMSCRIPTEN)
    
elseif(MSVC)
    # copy SDL2.dll to output directory
    add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD   
        COMMAND ${CMAKE_COMMAND} -E copy_if_different 
        "${SDL2_LIBRARY_DIR}/SDL2.dll" ${EXECUTABLE_OUTPUT_PATH})

    # copy asset directory to output folder
    add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD   
        COMMAND ${CMAKE_COMMAND} -E copy_directory 
        "${CMAKE_HOME_DIRECTORY}/projects/${PROJECT_NAME}/assets" "${EXECUTABLE_OUTPUT_PATH}/assets")
endif()