cmake_minimum_required(VERSION 3.0.0...3.5.0)
project(
  OpenGL-Ping-Pong
  VERSION 1.0.0.0
  DESCRIPTION ""
  HOMEPAGE_URL ""
  LANGUAGES C CXX)

set(CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/CMake")

find_package(OpenGL REQUIRED)

set(PONG_DEPENDENCIES_DIR "${CMAKE_CURRENT_LIST_DIR}/Dependencies")
set(PONG_DEPENDENCIES_BUILD_DIR "${CMAKE_CURRENT_BINARY_DIR}/Dependencies")
set(PONG_DEPENDENCIES_LIB_DIR "${CMAKE_CURRENT_BINARY_DIR}/Shared")

include(BuildSDL2)
include(BuildGLEW)
include(Buildcglm)

set(PONG_TARGET "Pong")

set(PONG_SOURCE_DIR "${CMAKE_CURRENT_LIST_DIR}/Source")
set(PONG_INCLUDE_DIR "${CMAKE_CURRENT_LIST_DIR}/Include")

set(PONG_SOURCES
    "${PONG_SOURCE_DIR}/whereami.c" "${PONG_SOURCE_DIR}/Utility.c"
    "${PONG_SOURCE_DIR}/Graphics.c" "${PONG_SOURCE_DIR}/Keyboard.c"
    "${PONG_SOURCE_DIR}/Paddle.c" "${PONG_SOURCE_DIR}/Game.c")

add_executable(${PONG_TARGET})
target_sources(${PONG_TARGET} PRIVATE ${PONG_SOURCES})
target_include_directories(${PONG_TARGET} PRIVATE ${PONG_INCLUDE_DIR})
target_link_libraries(${PONG_TARGET} PRIVATE SDL2::SDL2 libglew_shared cglm)

set(RESOURCES_DIR "${CMAKE_CURRENT_LIST_DIR}/Resources")

if(APPLE)
  include(BuildAppBundle)
endif()

if(WIN32)
  file(GLOB_RECURSE RUNTIME_LIBRARES "${PONG_DEPENDENCIES_LIB_DIR}/*.dll")
  add_custom_command(
    TARGET ${PONG_TARGET}
    POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory ${RESOURCES_DIR}
            $<TARGET_FILE_DIR:${PONG_TARGET}>/Resources)

  add_custom_command(
    TARGET ${PONG_TARGET}
    POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different ${RUNTIME_LIBRARES}
            $<TARGET_FILE_DIR:${PONG_TARGET}>)
endif()
