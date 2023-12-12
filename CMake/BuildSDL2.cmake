set(SDL2_DISABLE_INSTALL
    ON
    CACHE BOOL "" FORCE)
set(SDL2_DISABLE_UNINSTALL
    ON
    CACHE BOOL "" FORCE)
set(SDL2_DISABLE_MAIN
    ON
    CACHE BOOL "" FORCE)
set(SDL_SHARED
    ON
    CACHE BOOL "" FORCE)
set(SDL_STATIC
    OFF
    CACHE BOOL "" FORCE)
set(SDL_STATIC_PIC
    OFF
    CACHE BOOL "" FORCE)

add_subdirectory("${PONG_DEPENDENCIES_DIR}/SDL-2.28.x"
                 "${PONG_DEPENDENCIES_BUILD_DIR}/SDL2")
#CMAKE_RUNTIME_OUTPUT_DIRECTORY


if (WIN32)
set_target_properties(
    SDL2 PROPERTIES 
    RUNTIME_OUTPUT_DIRECTORY "${PONG_DEPENDENCIES_LIB_DIR}")
else()
set_target_properties(
  SDL2 PROPERTIES ARCHIVE_OUTPUT_DIRECTORY "${PONG_DEPENDENCIES_LIB_DIR}"
                  LIBRARY_OUTPUT_DIRECTORY "${PONG_DEPENDENCIES_LIB_DIR}")
endif()