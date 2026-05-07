cmake_minimum_required(VERSION 3.16)

project(monapp VERSION 0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

find_package(Qt6 REQUIRED COMPONENTS Quick QuickControls2)

#nom de l'exécutable
qt_add_executable(app_exec
    main.cpp
    Backend.h
    Backend.cpp
    Personne.h
    Personne.cpp
)

find_package(Qt6 REQUIRED COMPONENTS
    Quick
    Widgets
)
target_link_libraries(app_exec
    PRIVATE Qt6::Quick
    Qt6::Widgets
)

#ON LAISSE monapp ICI (module QML)
qt_add_qml_module(app_exec
    URI monapp
    VERSION 1.0
    QML_FILES main.qml
)

target_link_libraries(app_exec
    PRIVATE Qt6::Quick Qt6::QuickControls2
)
