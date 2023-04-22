QT       += core gui printsupport

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

ICON = ../icon/smartcalc.png

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    ../CFiles/help_functions.c \
    ../CFiles/s21_calculator.c \
    ../CFiles/s21_credit_calculator.c \
    ../CFiles/s21_deposit_calculator.c \
    creditwindow.cpp \
    depositwindow.cpp \
    main.cpp \
    mainwindow.cpp \
    qcustomplot.cpp

HEADERS += \
    ../CFiles/s21_calculator.h \
    creditwindow.h \
    depositwindow.h \
    mainwindow.h \
    qcustomplot.h

FORMS += \
    creditwindow.ui \
    depositwindow.ui \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
