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
    controller/controller_calculator.cc \
    controller/controller_credit.cc \
    controller/controller_deposit.cc \
    main.cc \
    model/model_calculator.cc \
    model/model_credit.cc \
    model/model_deposit.cc \
    view/view_calculator.cc \
    view/view_credit.cc \
    view/view_deposit.cc

HEADERS += \
    QCustomPlot/qcustomplot.h \
    controller/controller_calculator.h \
    controller/controller_credit.h \
    controller/controller_deposit.h \
    model/model_calculator.h \
    model/model_credit.h \
    model/model_deposit.h \
    view/view_calculator.h \
    view/view_credit.h \
    view/view_deposit.h

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

FORMS += \
    view/view_calculator.ui \
    view/view_credit.ui \
    view/view_deposit.ui
