QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17
QT += printsupport
ICON = icon/smartcalc.png

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    QCustomPlot/qcustomplot.cc \
    controller/controller.cc \
    main.cc \
    model/model.cc \
    view/credit.cc \
    view/deposit.cc \
    view/view.cc

HEADERS += \
    QCustomPlot/qcustomplot.h \
    controller/controller.h \
    model/model.h \
    view/credit.h \
    view/deposit.h \
    view/view.h

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

FORMS += \
    view/credit.ui \
    view/deposit.ui \
    view/view.ui
