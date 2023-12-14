set(CGLM_SHARED
    ON
    CACHE BOOL "" FORCE)
set(CGLM_STATIC
    OFF
    CACHE BOOL "" FORCE)
set(CGLM_USE_C99
    ON
    CACHE BOOL "" FORCE)
set(CGLM_USE_TEST
    OFF
    CACHE BOOL "" FORCE)

add_subdirectory("${PONG_DEPENDENCIES_DIR}/cglm-0.9.1"
                 "${PONG_DEPENDENCIES_BUILD_DIR}/cglm")
