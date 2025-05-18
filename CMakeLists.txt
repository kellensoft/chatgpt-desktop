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
