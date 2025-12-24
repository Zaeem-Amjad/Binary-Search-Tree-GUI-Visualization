cmake_minimum_required(VERSION 3.16)

project(BinarySTProject VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

# Set Qt path for MSVC 143 (Visual Studio 2022)
# Adjust this path to match your Qt installation
set(CMAKE_PREFIX_PATH "C:/Qt/6.10.1/msvc2022_64" CACHE PATH "Qt installation path")

# Find Qt components
find_package(Qt6 REQUIRED COMPONENTS Core Quick Gui Qml)

qt_add_executable(BinarySTProject
    main.cpp
    TreeManager.h
    TreeManager.cpp
    BST.h
    BST.cpp
    AVL.h
    AVL.cpp
    RBTree.h
    RBTree.cpp
)

qt_add_qml_module(BinarySTProject
    URI BinarySTApp
    VERSION 1.0
    QML_FILES
        qml/main.qml
        qml/WelcomePage.qml
        qml/TreeOperationsPage.qml
        qml/TreeCanvas.qml
    RESOURCES
        qml.qrc
)

target_link_libraries(BinarySTProject PRIVATE
    Qt6::Core
    Qt6::Quick
    Qt6::Gui
    Qt6::Qml
)

set_target_properties(BinarySTProject PROPERTIES
    WIN32_EXECUTABLE TRUE
    MACOSX_BUNDLE TRUE
)