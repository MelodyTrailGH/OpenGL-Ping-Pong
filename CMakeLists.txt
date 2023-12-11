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

if(APPLE)
  set(PONG_BUNDLE_NAME "Ping Pong")
  set_target_properties(
    "${PONG_TARGET}"
    PROPERTIES MACOSX_BUNDLE_NAME "${PONG_BUNDLE_NAME}"
               MACOSX_BUNDLE_VERSION "${PROJECT_VERSION}"
               MACOSX_BUNDLE_GUI_IDENTIFIER "org.melodytrail.${PONG_TARGET}"
               MACOSX_BUNDLE_ICON_FILE ""
               MACOSX_BUNDLE_INFO_PLIST
               "${CMAKE_CURRENT_LIST_DIR}/Cmake/info.plist.in"
               MACOSX_BUNDLE "TRUE"
               # MACHO_COMPATIBILITY_VERSION                  "12.0.0"
               RESOURCE "${RESOURCE_FILES}"
               XCODE_ATTRIBUTE_CODE_SIGN_IDENTITY ""
               XCODE_ATTRIBUTE_CODE_SIGNING_REQUIRED NO
               XCODE_ATTRIBUTE_DEBUG_INFORMATION_FORMAT dwarf
               XCODE_ATTRIBUTE_GCC_INLINES_ARE_PRIVATE_EXTERN YES
               XCODE_ATTRIBUTE_CLANG_LINK_OBJC_RUNTIME NO
               INSTALL_RPATH "@executable_path/../Frameworks")

  add_custom_command(
    TARGET ${PONG_TARGET}
    PRE_BUILD
    COMMAND ${CMAKE_COMMAND} -E make_directory
            "${CMAKE_CURRENT_BINARY_DIR}/${PONG_TARGET}.app/Contents/Frameworks"
  )

  add_custom_command(
    TARGET ${PONG_TARGET}
    POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy "${PONG_DEPENDENCIES_LIB_DIR}/*.dylib"
            "${CMAKE_CURRENT_BINARY_DIR}/${PONG_TARGET}.app/Contents/Frameworks"
  )
endif()
