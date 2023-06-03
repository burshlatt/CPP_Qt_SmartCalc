QT       += core gui printsupport

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

ICON = ../icon/smartcalc.png

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    ../controller/controller.cc \
    ../model/model.cc \
    creditwindow.cpp \
    main.cpp \
    qcustomplot.cpp \
    view.cpp

HEADERS += \
    ../controller/controller.h \
    ../model/model.h \
    creditwindow.h \
    qcustomplot.h \
    view.h

FORMS += \
    creditwindow.ui \
    view.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
