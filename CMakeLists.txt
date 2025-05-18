cmake_minimum_required(VERSION 3.19)
project(ChatGPT LANGUAGES CXX)

find_package(Qt6 6.5 REQUIRED COMPONENTS Core Widgets LinguistTools WebEngineWidgets)

qt_standard_project_setup()

qt_add_executable(ChatGPT
    WIN32 MACOSX_BUNDLE
    main.cpp
    mainwindow.cpp
    mainwindow.h
    mainwindow.ui
    resources.qrc
)

qt_add_translations(
    TARGETS ChatGPT
    TS_FILES ChatGPT_en_US.ts
)

target_link_libraries(ChatGPT
    PRIVATE
        Qt::Core
        Qt::Widgets
        Qt6::WebEngineWidgets
)

include(GNUInstallDirs)

install(TARGETS ChatGPT
    BUNDLE  DESTINATION .
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
)

qt_generate_deploy_app_script(
    TARGET ChatGPT
    OUTPUT_SCRIPT deploy_script
    NO_UNSUPPORTED_PLATFORM_ERROR
)
install(SCRIPT ${deploy_script})

include(InstallRequiredSystemLibraries)

set(CPACK_PACKAGE_NAME "ChatGPT")
set(CPACK_PACKAGE_VENDOR "KellenSoft")
set(CPACK_PACKAGE_DESCRIPTION_SUMMARY "Desktop wrapper for ChatGPT")
set(CPACK_PACKAGE_VERSION_MAJOR "1")
set(CPACK_PACKAGE_VERSION_MINOR "0")
set(CPACK_PACKAGE_VERSION_PATCH "0")
set(CPACK_PACKAGE_VERSION "${CPACK_PACKAGE_VERSION_MAJOR}.${CPACK_PACKAGE_VERSION_MINOR}.${CPACK_PACKAGE_VERSION_PATCH}")
set(CPACK_PACKAGE_INSTALL_DIRECTORY "ChatGPT")
set(CPACK_PACKAGE_CONTACT "support@kellensoft.com")

set(CPACK_RESOURCE_FILE_ICON "${CMAKE_SOURCE_DIR}/icons/chatgpt.ico")

set(CPACK_GENERATOR "WIX")
set(CPACK_WIX_UPGRADE_GUID "68D10E3B-5CB3-4EF8-93C6-DAB65875147D")
set(CPACK_WIX_PRODUCT_GUID "9A81F78D-D77C-4E41-805D-3ED907A0FAEC")

set(CPACK_CREATE_DESKTOP_LINKS ChatGPT)

include(CPack)
