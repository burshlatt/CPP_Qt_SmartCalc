cmake_minimum_required(VERSION 3.5)

project(SmartCalc VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra")

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets PrintSupport)

set(PROJECT_SOURCES
    src/main.cpp
    
    src/view/calc/view_calc.cc
    src/view/calc/view_calc.hpp
    src/view/calc/view_calc.ui

    src/view/credit/view_credit.cc
    src/view/credit/view_credit.hpp
    src/view/credit/view_credit.ui

    src/third_party/qcustomplot/qcustomplot.h
    src/third_party/qcustomplot/qcustomplot.cpp
)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(SmartCalc
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
        resources/resources.qrc
        src/model/calc/model_calc.cc
        src/model/calc/model_calc.hpp
        src/model/credit/model_credit.cc
        src/model/credit/model_credit.hpp
        src/view/credit/view_credit.ui
        src/view/credit/view_credit.cc
        src/view/credit/view_credit.hpp
        src/controller/ccalc/controller_calc.hpp
        src/controller/credit/controller_credit.hpp
        src/third_party/qcustomplot/qcustomplot.h
        src/third_party/qcustomplot/qcustomplot.cpp
    )
    qt_finalize_executable(SmartCalc)
else()
    add_executable(SmartCalc
        ${PROJECT_SOURCES}
        resources/resources.qrc
        src/model/calc/model_calc.cc
        src/model/calc/model_calc.hpp
        src/model/credit/model_credit.cc
        src/model/credit/model_credit.hpp
        src/view/credit/view_credit.ui
        src/view/credit/view_credit.cc
        src/view/credit/view_credit.hpp
        src/controller/calc/controller_calc.hpp
        src/controller/credit/controller_credit.hpp
        src/third_party/qcustomplot/qcustomplot.h
        src/third_party/qcustomplot/qcustomplot.cpp
    )
endif()

target_link_libraries(SmartCalc PRIVATE Qt${QT_VERSION_MAJOR}::Widgets Qt${QT_VERSION_MAJOR}::PrintSupport)

include_directories(
    src/view/calc
    src/view/credit
    src/model/calc
    src/model/credit
    src/controller/calc
    src/controller/credit
    src/third_party/qcustomplot
)

if(${QT_VERSION_MAJOR} VERSION_LESS 6.1.0)
    set(BUNDLE_ID_OPTION MACOSX_BUNDLE_GUI_IDENTIFIER com.example.SmartCalc)
endif()

set_target_properties(SmartCalc PROPERTIES
    ${BUNDLE_ID_OPTION}
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

include(GNUInstallDirs)

install(TARGETS SmartCalc
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
