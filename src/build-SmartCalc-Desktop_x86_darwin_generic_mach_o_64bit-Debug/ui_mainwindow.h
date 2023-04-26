/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.2.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>
#include "qcustomplot.h"

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QLineEdit *inputOutput;
    QPushButton *cosFunc;
    QPushButton *sinFunc;
    QPushButton *tanFunc;
    QPushButton *sqrtFunc;
    QPushButton *lnFunc;
    QPushButton *acosFunc;
    QPushButton *powFunc;
    QPushButton *asinFunc;
    QPushButton *atanFunc;
    QPushButton *logFunc;
    QPushButton *modFunc;
    QPushButton *num_7;
    QPushButton *num_4;
    QPushButton *num_1;
    QPushButton *xSym;
    QPushButton *num_2;
    QPushButton *num_0;
    QPushButton *leftBracket;
    QPushButton *num_5;
    QPushButton *num_8;
    QPushButton *num_3;
    QPushButton *dotSym;
    QPushButton *rightBracket;
    QPushButton *num_6;
    QPushButton *num_9;
    QPushButton *addFunc;
    QPushButton *divFunc;
    QPushButton *subFunc;
    QPushButton *mulFunc;
    QPushButton *delElem;
    QPushButton *delAll;
    QPushButton *resultFunc;
    QPushButton *showGraph;
    QPushButton *credCalc;
    QPushButton *deposCalc;
    QCustomPlot *functionGraph;
    QLineEdit *xMinCord;
    QLineEdit *xMaxCord;
    QLineEdit *yMinCord;
    QLineEdit *yMaxCord;
    QLineEdit *xValue;
    QPushButton *pushButton;
    QPushButton *num_pi;
    QPushButton *absFunc;
    QLineEdit *xStart;
    QLineEdit *xEnd;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(960, 380);
        MainWindow->setMinimumSize(QSize(480, 380));
        MainWindow->setMaximumSize(QSize(960, 380));
        MainWindow->setSizeIncrement(QSize(0, 0));
        MainWindow->setBaseSize(QSize(100, 100));
        MainWindow->setStyleSheet(QString::fromUtf8("QMainWindow {\n"
"	background-color: rgb(255, 219, 139);\n"
"}"));
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        inputOutput = new QLineEdit(centralwidget);
        inputOutput->setObjectName(QString::fromUtf8("inputOutput"));
        inputOutput->setGeometry(QRect(0, 0, 460, 60));
        QFont font;
        font.setPointSize(25);
        inputOutput->setFont(font);
        inputOutput->setStyleSheet(QString::fromUtf8("QLineEdit{\n"
"	qproperty-alignment: 'AlignVCenter | AlignRight';\n"
"	border: 1px solid gray;\n"
"}\n"
"\n"
"background-color : gray;\n"
""));
        inputOutput->setReadOnly(true);
        cosFunc = new QPushButton(centralwidget);
        cosFunc->setObjectName(QString::fromUtf8("cosFunc"));
        cosFunc->setGeometry(QRect(0, 60, 80, 60));
        cosFunc->setBaseSize(QSize(0, 0));
        QFont font1;
        font1.setPointSize(17);
        cosFunc->setFont(font1);
        cosFunc->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"  background-color: rgb(255, 219, 139);\n"
"  color: black; \n"
"  border: 1px solid gray;\n"
"}\n"
"\n"
"QPushButton:pressed {\n"
"    background-color: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1,\n"
"                                      stop: 0 #FF7832, stop: 1 #FF9739);\n"
"}"));
        sinFunc = new QPushButton(centralwidget);
        sinFunc->setObjectName(QString::fromUtf8("sinFunc"));
        sinFunc->setGeometry(QRect(0, 120, 80, 60));
        sinFunc->setBaseSize(QSize(0, 0));
        sinFunc->setFont(font1);
        sinFunc->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"  background-color: rgb(255, 219, 139);\n"
"  color: black; \n"
"  border: 1px solid gray;\n"
"}\n"
"\n"
"QPushButton:pressed {\n"
"    background-color: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1,\n"
"                                      stop: 0 #FF7832, stop: 1 #FF9739);\n"
"}"));
        tanFunc = new QPushButton(centralwidget);
        tanFunc->setObjectName(QString::fromUtf8("tanFunc"));
        tanFunc->setGeometry(QRect(0, 180, 80, 60));
        tanFunc->setBaseSize(QSize(0, 0));
        tanFunc->setFont(font1);
        tanFunc->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"  background-color: rgb(255, 219, 139);\n"
"  color: black; \n"
"  border: 1px solid gray;\n"
"}\n"
"\n"
"QPushButton:pressed {\n"
"    background-color: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1,\n"
"                                      stop: 0 #FF7832, stop: 1 #FF9739);\n"
"}"));
        sqrtFunc = new QPushButton(centralwidget);
        sqrtFunc->setObjectName(QString::fromUtf8("sqrtFunc"));
        sqrtFunc->setGeometry(QRect(0, 240, 80, 60));
        sqrtFunc->setBaseSize(QSize(0, 0));
        sqrtFunc->setFont(font1);
        sqrtFunc->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"  background-color: rgb(255, 219, 139);\n"
"  color: black; \n"
"  border: 1px solid gray;\n"
"}\n"
"\n"
"QPushButton:pressed {\n"
"    background-color: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1,\n"
"                                      stop: 0 #FF7832, stop: 1 #FF9739);\n"
"}"));
        lnFunc = new QPushButton(centralwidget);
        lnFunc->setObjectName(QString::fromUtf8("lnFunc"));
        lnFunc->setGeometry(QRect(0, 300, 80, 60));
        lnFunc->setBaseSize(QSize(0, 0));
        lnFunc->setFont(font1);
        lnFunc->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"  background-color: rgb(255, 219, 139);\n"
"  color: black; \n"
"  border: 1px solid gray;\n"
"}\n"
"\n"
"QPushButton:pressed {\n"
"    background-color: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1,\n"
"                                      stop: 0 #FF7832, stop: 1 #FF9739);\n"
"}"));
        acosFunc = new QPushButton(centralwidget);
        acosFunc->setObjectName(QString::fromUtf8("acosFunc"));
        acosFunc->setGeometry(QRect(80, 60, 80, 60));
        acosFunc->setBaseSize(QSize(0, 0));
        acosFunc->setFont(font1);
        acosFunc->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"  background-color: rgb(255, 219, 139);\n"
"  color: black; \n"
"  border: 1px solid gray;\n"
"}\n"
"\n"
"QPushButton:pressed {\n"
"    background-color: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1,\n"
"                                      stop: 0 #FF7832, stop: 1 #FF9739);\n"
"}"));
        powFunc = new QPushButton(centralwidget);
        powFunc->setObjectName(QString::fromUtf8("powFunc"));
        powFunc->setGeometry(QRect(160, 60, 60, 60));
        powFunc->setBaseSize(QSize(0, 0));
        powFunc->setFont(font1);
        powFunc->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"  background-color: rgb(255, 219, 139);\n"
"  color: black; \n"
"  border: 1px solid gray;\n"
"}\n"
"\n"
"QPushButton:pressed {\n"
"    background-color: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1,\n"
"                                      stop: 0 #FF7832, stop: 1 #FF9739);\n"
"}"));
        asinFunc = new QPushButton(centralwidget);
        asinFunc->setObjectName(QString::fromUtf8("asinFunc"));
        asinFunc->setGeometry(QRect(80, 120, 80, 60));
        asinFunc->setBaseSize(QSize(0, 0));
        asinFunc->setFont(font1);
        asinFunc->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"  background-color: rgb(255, 219, 139);\n"
"  color: black; \n"
"  border: 1px solid gray;\n"
"}\n"
"\n"
"QPushButton:pressed {\n"
"    background-color: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1,\n"
"                                      stop: 0 #FF7832, stop: 1 #FF9739);\n"
"}"));
        atanFunc = new QPushButton(centralwidget);
        atanFunc->setObjectName(QString::fromUtf8("atanFunc"));
        atanFunc->setGeometry(QRect(80, 180, 80, 60));
        atanFunc->setBaseSize(QSize(0, 0));
        atanFunc->setFont(font1);
        atanFunc->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"  background-color: rgb(255, 219, 139);\n"
"  color: black; \n"
"  border: 1px solid gray;\n"
"}\n"
"\n"
"QPushButton:pressed {\n"
"    background-color: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1,\n"
"                                      stop: 0 #FF7832, stop: 1 #FF9739);\n"
"}"));
        logFunc = new QPushButton(centralwidget);
        logFunc->setObjectName(QString::fromUtf8("logFunc"));
        logFunc->setGeometry(QRect(80, 300, 80, 60));
        logFunc->setBaseSize(QSize(0, 0));
        logFunc->setFont(font1);
        logFunc->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"  background-color: rgb(255, 219, 139);\n"
"  color: black; \n"
"  border: 1px solid gray;\n"
"}\n"
"\n"
"QPushButton:pressed {\n"
"    background-color: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1,\n"
"                                      stop: 0 #FF7832, stop: 1 #FF9739);\n"
"}"));
        modFunc = new QPushButton(centralwidget);
        modFunc->setObjectName(QString::fromUtf8("modFunc"));
        modFunc->setGeometry(QRect(340, 120, 60, 60));
        modFunc->setFont(font1);
        modFunc->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"  background-color: rgb(255, 219, 139);\n"
"  color: black; \n"
"  border: 1px solid gray;\n"
"}\n"
"\n"
"QPushButton:pressed {\n"
"    background-color: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1,\n"
"                                      stop: 0 #FF7832, stop: 1 #FF9739);\n"
"}"));
        num_7 = new QPushButton(centralwidget);
        num_7->setObjectName(QString::fromUtf8("num_7"));
        num_7->setGeometry(QRect(160, 120, 60, 60));
        num_7->setFont(font1);
        num_7->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"	background-color: rgb(59, 60, 54);\n"
"	color: white;\n"
"	border: 1px solid gray;\n"
"}\n"
"QPushButton:pressed {\n"
"    background-color: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1,\n"
"                                      stop: 0 #dadbde, stop: 1 #f6f7fa);\n"
"}"));
        num_4 = new QPushButton(centralwidget);
        num_4->setObjectName(QString::fromUtf8("num_4"));
        num_4->setGeometry(QRect(160, 180, 60, 60));
        num_4->setFont(font1);
        num_4->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"	background-color: rgb(59, 60, 54);\n"
"	color: white;\n"
"	border: 1px solid gray;\n"
"}\n"
"\n"
"QPushButton:pressed {\n"
"    background-color: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1,\n"
"                                      stop: 0 #dadbde, stop: 1 #f6f7fa);\n"
"}"));
        num_1 = new QPushButton(centralwidget);
        num_1->setObjectName(QString::fromUtf8("num_1"));
        num_1->setGeometry(QRect(160, 240, 60, 60));
        num_1->setFont(font1);
        num_1->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"	background-color: rgb(59, 60, 54);\n"
"	color: white;\n"
"	border: 1px solid gray;\n"
"}\n"
"\n"
"QPushButton:pressed {\n"
"    background-color: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1,\n"
"                                      stop: 0 #dadbde, stop: 1 #f6f7fa);\n"
"}"));
        xSym = new QPushButton(centralwidget);
        xSym->setObjectName(QString::fromUtf8("xSym"));
        xSym->setGeometry(QRect(160, 300, 60, 60));
        xSym->setFont(font1);
        xSym->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"	background-color: rgb(59, 60, 54);\n"
"	color: white;\n"
"	border: 1px solid gray;\n"
"}\n"
"\n"
"QPushButton:pressed {\n"
"    background-color: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1,\n"
"                                      stop: 0 #dadbde, stop: 1 #f6f7fa);\n"
"}"));
        num_2 = new QPushButton(centralwidget);
        num_2->setObjectName(QString::fromUtf8("num_2"));
        num_2->setGeometry(QRect(220, 240, 60, 60));
        num_2->setFont(font1);
        num_2->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"	background-color: rgb(59, 60, 54);\n"
"	color: white;\n"
"	border: 1px solid gray;\n"
"}\n"
"\n"
"QPushButton:pressed {\n"
"    background-color: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1,\n"
"                                      stop: 0 #dadbde, stop: 1 #f6f7fa);\n"
"}"));
        num_0 = new QPushButton(centralwidget);
        num_0->setObjectName(QString::fromUtf8("num_0"));
        num_0->setGeometry(QRect(220, 300, 60, 60));
        num_0->setFont(font1);
        num_0->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"	background-color: rgb(59, 60, 54);\n"
"	color: white;\n"
"	border: 1px solid gray;\n"
"}\n"
"\n"
"QPushButton:pressed {\n"
"    background-color: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1,\n"
"                                      stop: 0 #dadbde, stop: 1 #f6f7fa);\n"
"}"));
        leftBracket = new QPushButton(centralwidget);
        leftBracket->setObjectName(QString::fromUtf8("leftBracket"));
        leftBracket->setGeometry(QRect(220, 60, 60, 60));
        leftBracket->setFont(font1);
        leftBracket->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"  background-color: rgb(255, 219, 139);\n"
"  color: black; \n"
"  border: 1px solid gray;\n"
"}\n"
"\n"
"QPushButton:pressed {\n"
"    background-color: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1,\n"
"                                      stop: 0 #FF7832, stop: 1 #FF9739);\n"
"}"));
        num_5 = new QPushButton(centralwidget);
        num_5->setObjectName(QString::fromUtf8("num_5"));
        num_5->setGeometry(QRect(220, 180, 60, 60));
        num_5->setFont(font1);
        num_5->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"	background-color: rgb(59, 60, 54);\n"
"	color: white;\n"
"	border: 1px solid gray;\n"
"}\n"
"\n"
"QPushButton:pressed {\n"
"    background-color: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1,\n"
"                                      stop: 0 #dadbde, stop: 1 #f6f7fa);\n"
"}"));
        num_8 = new QPushButton(centralwidget);
        num_8->setObjectName(QString::fromUtf8("num_8"));
        num_8->setGeometry(QRect(220, 120, 60, 60));
        num_8->setFont(font1);
        num_8->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"	background-color: rgb(59, 60, 54);\n"
"	color: white;\n"
"	border: 1px solid gray;\n"
"}\n"
"\n"
"QPushButton:pressed {\n"
"    background-color: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1,\n"
"                                      stop: 0 #dadbde, stop: 1 #f6f7fa);\n"
"}"));
        num_3 = new QPushButton(centralwidget);
        num_3->setObjectName(QString::fromUtf8("num_3"));
        num_3->setGeometry(QRect(280, 240, 60, 60));
        num_3->setFont(font1);
        num_3->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"	background-color: rgb(59, 60, 54);\n"
"	color: white;\n"
"	border: 1px solid gray;\n"
"}\n"
"\n"
"QPushButton:pressed {\n"
"    background-color: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1,\n"
"                                      stop: 0 #dadbde, stop: 1 #f6f7fa);\n"
"}"));
        dotSym = new QPushButton(centralwidget);
        dotSym->setObjectName(QString::fromUtf8("dotSym"));
        dotSym->setGeometry(QRect(280, 300, 60, 60));
        dotSym->setFont(font1);
        dotSym->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"	background-color: rgb(59, 60, 54);\n"
"	color: white;\n"
"	border: 1px solid gray;\n"
"}\n"
"\n"
"QPushButton:pressed {\n"
"    background-color: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1,\n"
"                                      stop: 0 #dadbde, stop: 1 #f6f7fa);\n"
"}"));
        rightBracket = new QPushButton(centralwidget);
        rightBracket->setObjectName(QString::fromUtf8("rightBracket"));
        rightBracket->setGeometry(QRect(280, 60, 60, 60));
        rightBracket->setFont(font1);
        rightBracket->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"  background-color: rgb(255, 219, 139);\n"
"  color: black; \n"
"  border: 1px solid gray;\n"
"}\n"
"\n"
"QPushButton:pressed {\n"
"    background-color: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1,\n"
"                                      stop: 0 #FF7832, stop: 1 #FF9739);\n"
"}"));
        num_6 = new QPushButton(centralwidget);
        num_6->setObjectName(QString::fromUtf8("num_6"));
        num_6->setGeometry(QRect(280, 180, 60, 60));
        num_6->setFont(font1);
        num_6->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"	background-color: rgb(59, 60, 54);\n"
"	color: white;\n"
"	border: 1px solid gray;\n"
"}\n"
"\n"
"QPushButton:pressed {\n"
"    background-color: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1,\n"
"                                      stop: 0 #dadbde, stop: 1 #f6f7fa);\n"
"}"));
        num_9 = new QPushButton(centralwidget);
        num_9->setObjectName(QString::fromUtf8("num_9"));
        num_9->setGeometry(QRect(280, 120, 60, 60));
        num_9->setFont(font1);
        num_9->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"	background-color: rgb(59, 60, 54);\n"
"	color: white;\n"
"	border: 1px solid gray;\n"
"}\n"
"\n"
"QPushButton:pressed {\n"
"    background-color: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1,\n"
"                                      stop: 0 #dadbde, stop: 1 #f6f7fa);\n"
"}"));
        addFunc = new QPushButton(centralwidget);
        addFunc->setObjectName(QString::fromUtf8("addFunc"));
        addFunc->setGeometry(QRect(340, 240, 60, 60));
        addFunc->setFont(font1);
        addFunc->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"  background-color: rgb(255, 219, 139);\n"
"  color: black; \n"
"  border: 1px solid gray;\n"
"}\n"
"\n"
"QPushButton:pressed {\n"
"    background-color: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1,\n"
"                                      stop: 0 #FF7832, stop: 1 #FF9739);\n"
"}"));
        divFunc = new QPushButton(centralwidget);
        divFunc->setObjectName(QString::fromUtf8("divFunc"));
        divFunc->setGeometry(QRect(400, 180, 60, 60));
        divFunc->setFont(font1);
        divFunc->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"  background-color: rgb(255, 219, 139);\n"
"  color: black; \n"
"  border: 1px solid gray;\n"
"}\n"
"\n"
"QPushButton:pressed {\n"
"    background-color: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1,\n"
"                                      stop: 0 #FF7832, stop: 1 #FF9739);\n"
"}"));
        subFunc = new QPushButton(centralwidget);
        subFunc->setObjectName(QString::fromUtf8("subFunc"));
        subFunc->setGeometry(QRect(340, 180, 60, 60));
        subFunc->setFont(font1);
        subFunc->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"  background-color: rgb(255, 219, 139);\n"
"  color: black; \n"
"  border: 1px solid gray;\n"
"}\n"
"\n"
"QPushButton:pressed {\n"
"    background-color: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1,\n"
"                                      stop: 0 #FF7832, stop: 1 #FF9739);\n"
"}"));
        mulFunc = new QPushButton(centralwidget);
        mulFunc->setObjectName(QString::fromUtf8("mulFunc"));
        mulFunc->setGeometry(QRect(400, 240, 60, 60));
        mulFunc->setFont(font1);
        mulFunc->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"  background-color: rgb(255, 219, 139);\n"
"  color: black; \n"
"  border: 1px solid gray;\n"
"}\n"
"\n"
"QPushButton:pressed {\n"
"    background-color: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1,\n"
"                                      stop: 0 #FF7832, stop: 1 #FF9739);\n"
"}"));
        delElem = new QPushButton(centralwidget);
        delElem->setObjectName(QString::fromUtf8("delElem"));
        delElem->setGeometry(QRect(340, 60, 60, 60));
        delElem->setFont(font1);
        delElem->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"  background-color: rgb(244, 169, 0);\n"
"  color: black; \n"
"  border: 1px solid gray;\n"
"}\n"
"\n"
"QPushButton:pressed {\n"
"    background-color: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1,\n"
"                                      stop: 0 #FF7832, stop: 1 #FF9739);\n"
"}"));
        delAll = new QPushButton(centralwidget);
        delAll->setObjectName(QString::fromUtf8("delAll"));
        delAll->setGeometry(QRect(400, 60, 60, 60));
        delAll->setFont(font1);
        delAll->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"  background-color: rgb(244, 169, 0);\n"
"  color: black; \n"
"  border: 1px solid gray;\n"
"}\n"
"\n"
"QPushButton:pressed {\n"
"    background-color: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1,\n"
"                                      stop: 0 #FF7832, stop: 1 #FF9739);\n"
"}"));
        resultFunc = new QPushButton(centralwidget);
        resultFunc->setObjectName(QString::fromUtf8("resultFunc"));
        resultFunc->setGeometry(QRect(340, 300, 120, 60));
        resultFunc->setBaseSize(QSize(0, 0));
        resultFunc->setFont(font1);
        resultFunc->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"  background-color: rgb(244, 169, 0);\n"
"  color: black; \n"
"  border: 1px solid gray;\n"
"}\n"
"\n"
"QPushButton:pressed {\n"
"    background-color: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1,\n"
"                                      stop: 0 #FF7832, stop: 1 #FF9739);\n"
"}"));
        showGraph = new QPushButton(centralwidget);
        showGraph->setObjectName(QString::fromUtf8("showGraph"));
        showGraph->setGeometry(QRect(460, -5, 20, 365));
        showGraph->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"  background-color: rgb(255, 160, 122);\n"
"  color: black; \n"
"  border: 1px solid gray;\n"
"}\n"
"\n"
"QPushButton:pressed {\n"
"    background-color: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1,\n"
"                                      stop: 0 #FF7832, stop: 1 #FF9739);\n"
"}"));
        credCalc = new QPushButton(centralwidget);
        credCalc->setObjectName(QString::fromUtf8("credCalc"));
        credCalc->setGeometry(QRect(0, 360, 230, 20));
        credCalc->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"  background-color: rgb(255, 160, 122);\n"
"  color: black; \n"
"  border: 1px solid gray;\n"
"}\n"
"\n"
"QPushButton:pressed {\n"
"    background-color: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1,\n"
"                                      stop: 0 #FF7832, stop: 1 #FF9739);\n"
"}"));
        deposCalc = new QPushButton(centralwidget);
        deposCalc->setObjectName(QString::fromUtf8("deposCalc"));
        deposCalc->setGeometry(QRect(230, 360, 230, 20));
        deposCalc->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"  background-color: rgb(255, 160, 122);\n"
"  color: black; \n"
"  border: 1px solid gray;\n"
"}\n"
"\n"
"QPushButton:pressed {\n"
"    background-color: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1,\n"
"                                      stop: 0 #FF7832, stop: 1 #FF9739);\n"
"}"));
        functionGraph = new QCustomPlot(centralwidget);
        functionGraph->setObjectName(QString::fromUtf8("functionGraph"));
        functionGraph->setGeometry(QRect(480, 0, 480, 290));
        functionGraph->setStyleSheet(QString::fromUtf8(""));
        xMinCord = new QLineEdit(centralwidget);
        xMinCord->setObjectName(QString::fromUtf8("xMinCord"));
        xMinCord->setGeometry(QRect(660, 325, 120, 25));
        xMinCord->setFont(font1);
        xMaxCord = new QLineEdit(centralwidget);
        xMaxCord->setObjectName(QString::fromUtf8("xMaxCord"));
        xMaxCord->setGeometry(QRect(660, 350, 120, 25));
        xMaxCord->setFont(font1);
        yMinCord = new QLineEdit(centralwidget);
        yMinCord->setObjectName(QString::fromUtf8("yMinCord"));
        yMinCord->setGeometry(QRect(820, 325, 120, 25));
        yMinCord->setFont(font1);
        yMaxCord = new QLineEdit(centralwidget);
        yMaxCord->setObjectName(QString::fromUtf8("yMaxCord"));
        yMaxCord->setGeometry(QRect(820, 350, 120, 25));
        yMaxCord->setFont(font1);
        xValue = new QLineEdit(centralwidget);
        xValue->setObjectName(QString::fromUtf8("xValue"));
        xValue->setGeometry(QRect(660, 300, 120, 25));
        xValue->setFont(font1);
        pushButton = new QPushButton(centralwidget);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));
        pushButton->setGeometry(QRect(460, 360, 20, 20));
        pushButton->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"  background-color: rgb(255, 160, 122);\n"
"  color: black; \n"
"  border: 1px solid gray;\n"
"}\n"
"\n"
"QPushButton:pressed {\n"
"    background-color: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1,\n"
"                                      stop: 0 #FF7832, stop: 1 #FF9739);\n"
"}"));
        num_pi = new QPushButton(centralwidget);
        num_pi->setObjectName(QString::fromUtf8("num_pi"));
        num_pi->setGeometry(QRect(400, 120, 60, 60));
        num_pi->setFont(font1);
        num_pi->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"  background-color: rgb(255, 219, 139);\n"
"  color: black; \n"
"  border: 1px solid gray;\n"
"}\n"
"\n"
"QPushButton:pressed {\n"
"    background-color: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1,\n"
"                                      stop: 0 #FF7832, stop: 1 #FF9739);\n"
"}"));
        absFunc = new QPushButton(centralwidget);
        absFunc->setObjectName(QString::fromUtf8("absFunc"));
        absFunc->setGeometry(QRect(80, 240, 80, 60));
        absFunc->setFont(font1);
        absFunc->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"  background-color: rgb(255, 219, 139);\n"
"  color: black; \n"
"  border: 1px solid gray;\n"
"}\n"
"\n"
"QPushButton:pressed {\n"
"    background-color: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1,\n"
"                                      stop: 0 #FF7832, stop: 1 #FF9739);\n"
"}"));
        xStart = new QLineEdit(centralwidget);
        xStart->setObjectName(QString::fromUtf8("xStart"));
        xStart->setGeometry(QRect(500, 325, 120, 25));
        xStart->setFont(font1);
        xEnd = new QLineEdit(centralwidget);
        xEnd->setObjectName(QString::fromUtf8("xEnd"));
        xEnd->setGeometry(QRect(500, 350, 120, 25));
        xEnd->setFont(font1);
        MainWindow->setCentralWidget(centralwidget);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "SmartCalc v.1.0 (by Stephank)", nullptr));
        cosFunc->setText(QCoreApplication::translate("MainWindow", "cos", nullptr));
        sinFunc->setText(QCoreApplication::translate("MainWindow", "sin", nullptr));
        tanFunc->setText(QCoreApplication::translate("MainWindow", "tan", nullptr));
        sqrtFunc->setText(QCoreApplication::translate("MainWindow", "sqrt", nullptr));
        lnFunc->setText(QCoreApplication::translate("MainWindow", "ln", nullptr));
        acosFunc->setText(QCoreApplication::translate("MainWindow", "acos", nullptr));
        powFunc->setText(QCoreApplication::translate("MainWindow", "^", nullptr));
        asinFunc->setText(QCoreApplication::translate("MainWindow", "asin", nullptr));
        atanFunc->setText(QCoreApplication::translate("MainWindow", "atan", nullptr));
        logFunc->setText(QCoreApplication::translate("MainWindow", "log", nullptr));
        modFunc->setText(QCoreApplication::translate("MainWindow", "mod", nullptr));
        num_7->setText(QCoreApplication::translate("MainWindow", "7", nullptr));
        num_4->setText(QCoreApplication::translate("MainWindow", "4", nullptr));
        num_1->setText(QCoreApplication::translate("MainWindow", "1", nullptr));
        xSym->setText(QCoreApplication::translate("MainWindow", "x", nullptr));
        num_2->setText(QCoreApplication::translate("MainWindow", "2", nullptr));
        num_0->setText(QCoreApplication::translate("MainWindow", "0", nullptr));
        leftBracket->setText(QCoreApplication::translate("MainWindow", "(", nullptr));
        num_5->setText(QCoreApplication::translate("MainWindow", "5", nullptr));
        num_8->setText(QCoreApplication::translate("MainWindow", "8", nullptr));
        num_3->setText(QCoreApplication::translate("MainWindow", "3", nullptr));
        dotSym->setText(QCoreApplication::translate("MainWindow", ".", nullptr));
        rightBracket->setText(QCoreApplication::translate("MainWindow", ")", nullptr));
        num_6->setText(QCoreApplication::translate("MainWindow", "6", nullptr));
        num_9->setText(QCoreApplication::translate("MainWindow", "9", nullptr));
        addFunc->setText(QCoreApplication::translate("MainWindow", "+", nullptr));
        divFunc->setText(QCoreApplication::translate("MainWindow", "/", nullptr));
        subFunc->setText(QCoreApplication::translate("MainWindow", "-", nullptr));
        mulFunc->setText(QCoreApplication::translate("MainWindow", "*", nullptr));
        delElem->setText(QCoreApplication::translate("MainWindow", "del", nullptr));
        delAll->setText(QCoreApplication::translate("MainWindow", "AC", nullptr));
        resultFunc->setText(QCoreApplication::translate("MainWindow", "=", nullptr));
        showGraph->setText(QCoreApplication::translate("MainWindow", ">", nullptr));
        credCalc->setText(QCoreApplication::translate("MainWindow", "\320\232\321\200\320\265\320\264\320\270\321\202\320\275\321\213\320\271 \320\272\320\260\320\273\321\214\320\272\321\203\320\273\321\217\321\202\320\276\321\200", nullptr));
        deposCalc->setText(QCoreApplication::translate("MainWindow", "\320\224\320\265\320\277\320\276\320\267\320\270\321\202\320\275\321\213\320\271 \320\272\320\260\320\273\321\214\320\272\321\203\320\273\321\217\321\202\320\276\321\200", nullptr));
        xMinCord->setText(QString());
        xMaxCord->setText(QString());
        yMinCord->setText(QString());
        yMaxCord->setText(QString());
        xValue->setText(QString());
        pushButton->setText(QString());
        num_pi->setText(QCoreApplication::translate("MainWindow", "Pi", nullptr));
        absFunc->setText(QCoreApplication::translate("MainWindow", "abs", nullptr));
        xStart->setText(QString());
        xEnd->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
