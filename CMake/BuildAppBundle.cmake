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
             XCODE_ATTRIBUTE_CODE_SIGN_IDENTITY ""
             XCODE_ATTRIBUTE_CODE_SIGNING_REQUIRED NO
             XCODE_ATTRIBUTE_DEBUG_INFORMATION_FORMAT dwarf
             XCODE_ATTRIBUTE_GCC_INLINES_ARE_PRIVATE_EXTERN YES
             XCODE_ATTRIBUTE_CLANG_LINK_OBJC_RUNTIME NO
             INSTALL_RPATH "@executable_path/../Frameworks")

set_target_properties(
  libglew_shared SDL2 cglm PROPERTIES LIBRARY_OUTPUT_DIRECTORY
                                      "${PONG_RUN_DIRECTORY}")
