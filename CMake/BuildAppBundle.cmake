set(PONG_BUNDLE_NAME "Ping Pong")
set_target_properties(
  "${PONG_TARGET}"
  PROPERTIES MACOSX_BUNDLE_NAME "${PONG_BUNDLE_NAME}"
             MACOSX_BUNDLE_VERSION "${PROJECT_VERSION}"
             MACOSX_BUNDLE_GUI_IDENTIFIER "org.melodytrail.${PONG_TARGET}"
             MACOSX_BUNDLE_ICON_FILE ""
             MACOSX_BUNDLE_INFO_PLIST
             "${CMAKE_CURRENT_LIST_DIR}/../CMake/info.plist.in"
             MACOSX_BUNDLE "TRUE"
             # MACHO_COMPATIBILITY_VERSION                  "12.0.0"
             RESOURCE "${RESOURCE_FILES}"
             XCODE_ATTRIBUTE_CODE_SIGN_IDENTITY ""
             XCODE_ATTRIBUTE_CODE_SIGNING_REQUIRED NO
             XCODE_ATTRIBUTE_DEBUG_INFORMATION_FORMAT dwarf
             XCODE_ATTRIBUTE_GCC_INLINES_ARE_PRIVATE_EXTERN YES
             XCODE_ATTRIBUTE_CLANG_LINK_OBJC_RUNTIME NO
             INSTALL_RPATH "@executable_path/../Frameworks")
# include(GNUInstallDirs)

# $<TARGET_FILE_DIR:${PONG_TARGET}>../

add_custom_command(
  TARGET ${PONG_TARGET}
  POST_BUILD
  COMMAND ${CMAKE_COMMAND} -E copy_directory ${RESOURCES_DIR}
          $<TARGET_FILE_DIR:${PONG_TARGET}>/../Resources)

add_custom_command(
  TARGET ${PONG_TARGET}
  POST_BUILD
  COMMAND ${CMAKE_COMMAND} -E copy_directory ${PONG_DEPENDENCIES_LIB_DIR}
          $<TARGET_FILE_DIR:${PONG_TARGET}>/../Frameworks)
