cmake_minimum_required(VERSION 3.0.0...3.5.0)
project(
  OpenGL-Ping-Pong
  VERSION 1.0.0.0
  DESCRIPTION ""
  HOMEPAGE_URL ""
  LANGUAGES C CXX)

set(CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/CMake")

set(PONG_DEPENDENCIES_DIR "${CMAKE_CURRENT_LIST_DIR}/Dependencies")
set(PONG_DEPENDENCIES_BUILD_DIR "${CMAKE_CURRENT_BINARY_DIR}/Dependencies")
set(PONG_DEPENDENCIES_LIB_DIR "${CMAKE_CURRENT_BINARY_DIR}/Shared")

include(BuildSDL2)
include(BuildGLEW)
include(Buildcglm)

set(PONG_TARGET "Pong")

set(PONG_SOURCE_DIR "${CMAKE_CURRENT_LIST_DIR}/Source")
set(PONG_INCLUDE_DIR "${CMAKE_CURRENT_LIST_DIR}/Include")

set(PONG_SOURCES "${PONG_SOURCE_DIR}/Game.c")


add_executable(${PONG_TARGET})
target_sources(${PONG_TARGET} PRIVATE ${PONG_SOURCES})
target_include_directories(${PONG_TARGET} PRIVATE ${PONG_INCLUDE_DIR})
target_link_libraries(${PONG_TARGET} PRIVATE SDL2::SDL2 libglew_shared cglm)
add_definitions(-DSDL_MAIN_HANDLED)

if(APPLE)
  include(MakeAppBundle)
endif()

if (WIN32)
file(GLOB_RECURSE BINARIES "${PONG_DEPENDENCIES_LIB_DIR}/*.dll")
add_custom_command(
  TARGET ${PONG_TARGET}
  POST_BUILD
  COMMAND ${CMAKE_COMMAND} -E copy_if_different ${BINARIES} "${CMAKE_CURRENT_BINARY_DIR}"
)
endif()