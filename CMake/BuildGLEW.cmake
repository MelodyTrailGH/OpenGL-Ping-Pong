set(ONLY_LIBS
    ON
    CACHE BOOL "" FORCE)
set(USE_GLU
    ON
    CACHE BOOL "" FORCE)
set(glew-cmake_BUILD_SHARED
    ON
    CACHE BOOL "" FORCE)
set(glew-cmake_BUILD_STATIC
    OFF
    CACHE BOOL "" FORCE)
add_subdirectory("${PONG_DEPENDENCIES_DIR}/glew-cmake-stable"
                 "${PONG_DEPENDENCIES_BUILD_DIR}/glew")

if (WIN32)
set_target_properties(
    libglew_shared PROPERTIES 
    RUNTIME_OUTPUT_DIRECTORY "${PONG_DEPENDENCIES_LIB_DIR}")
else()
set_target_properties(
  libglew_shared
  PROPERTIES ARCHIVE_OUTPUT_DIRECTORY "${PONG_DEPENDENCIES_LIB_DIR}"
             LIBRARY_OUTPUT_DIRECTORY "${PONG_DEPENDENCIES_LIB_DIR}")
endif()