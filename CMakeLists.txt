cmake_minimum_required(VERSION 3.0.0...3.5.0)
project(
  OpenGL-Ping-Pong
  VERSION 1.0.0.0
  DESCRIPTION ""
  HOMEPAGE_URL ""
  LANGUAGES C CXX)

set(CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/CMake")

find_package(OpenGL REQUIRED)

include("${CMAKE_CURRENT_LIST_DIR}/CMakeOptions.cmake")

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
    "${PONG_SOURCE_DIR}/Game.c")

add_executable(${PONG_TARGET})
target_sources(${PONG_TARGET} PRIVATE ${PONG_SOURCES})
target_include_directories(${PONG_TARGET} PRIVATE ${PONG_INCLUDE_DIR})
target_link_libraries(${PONG_TARGET} PRIVATE SDL2::SDL2 libglew_shared cglm)

set(RESOURCES_DIR "${CMAKE_CURRENT_LIST_DIR}/Resources")

if(${PONG_BUILD_PACKAGE})
  target_compile_definitions(-DPACKAGED=1)
  if(APPLE)
    include(BuildAppBundle)
  endif()
else()
  set(PONG_RUN_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}/${CMAKE_BUILD_TYPE}/Game")

  set_target_properties(${PONG_TARGET} PROPERTIES RUNTIME_OUTPUT_DIRECTORY
                                                  "${PONG_RUN_DIRECTORY}")
  file(COPY ${RESOURCES_DIR} DESTINATION ${PONG_RUN_DIRECTORY})
  if(WIN32)
    set_target_properties(
      libglew_shared SDL2 cglm PROPERTIES RUNTIME_OUTPUT_DIRECTORY
                                          "${PONG_RUN_DIRECTORY}")
  else()
    set_target_properties(
      libglew_shared SDL2 cglm PROPERTIES LIBRARY_OUTPUT_DIRECTORY
                                          "${PONG_RUN_DIRECTORY}")
  endif()
endif()
