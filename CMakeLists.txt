cmake_minimum_required(VERSION 3.16)

project(BoomEdit VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets)

set(PROJECT_SOURCES
        main.cpp
        BoomEditWindow.cpp
        BoomEditWindow.h
        boomeditwindow.ui
)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(BoomEdit
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
        include/views/blueprint/BlueprintCanvas.h
        include/views/blueprint/BlueprintCanvas.h src/views/blueprint/BlueprintCanvas.cpp
        PerspectiveView.h
        PerspectiveView.h PerspectiveView.cpp
        include/models/Vertex.h
        include/models/Wall.h
        include/models/Sector.h
        include/models/Level.h
        include/AppState.h
        include/AppState.h AppState.cpp
        include/views/blueprint/BlueprintCanvasController.h
        include/views/blueprint/BlueprintCanvasController.h src/views/blueprint/BlueprintCanvasController.cpp
        include/views/blueprint/BlueprintModel.h src/views/blueprint/BlueprintModel.cpp
        include/views/blueprint/BlueprintCanvasRenderer.h src/views/blueprint/BlueprintCanvasRenderer.cpp
        include/views/blueprint/BlueprintView.h src/views/blueprint/BlueprintView.cpp
        src/views/blueprint/BlueprintView.cpp
        include/views/blueprint/BlueprintToolBar.h
        src/views/blueprint/BlueprintToolBar.cpp
        include/views/blueprint/BlueprintInspector.h
        src/views/blueprint/BlueprintInspector.cpp

    )
# Define target properties for Android with Qt 6 as:
#    set_property(TARGET BoomEdit APPEND PROPERTY QT_ANDROID_PACKAGE_SOURCE_DIR
#                 ${CMAKE_CURRENT_SOURCE_DIR}/android)
# For more information, see https://doc.qt.io/qt-6/qt-add-executable.html#target-creation
else()
    if(ANDROID)
        add_library(BoomEdit SHARED
            ${PROJECT_SOURCES}
        )
# Define properties for Android with Qt 5 after find_package() calls as:
#    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
    else()
        add_executable(BoomEdit
            ${PROJECT_SOURCES}
        )
    endif()
endif()

target_link_libraries(BoomEdit PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)

# Qt for iOS sets MACOSX_BUNDLE_GUI_IDENTIFIER automatically since Qt 6.1.
# If you are developing for iOS or macOS you should consider setting an
# explicit, fixed bundle identifier manually though.
if(${QT_VERSION} VERSION_LESS 6.1.0)
  set(BUNDLE_ID_OPTION MACOSX_BUNDLE_GUI_IDENTIFIER com.example.BoomEdit)
endif()
set_target_properties(BoomEdit PROPERTIES
    ${BUNDLE_ID_OPTION}
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

include(GNUInstallDirs)
install(TARGETS BoomEdit
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(BoomEdit)
endif()

target_include_directories(BoomEdit PRIVATE
    ${CMAKE_SOURCE_DIR}/include
)
