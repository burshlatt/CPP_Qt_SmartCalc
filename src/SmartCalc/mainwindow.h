#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QApplication>
#include <QDialog>
#include <QLineEdit>
#include <QMainWindow>
#include <QPushButton>
#include <QScreen>
#include <QVector>
#include <QtMath>

#include <iostream>
#include <math.h>
#include <string>

#include "creditwindow.h"
#include "depositwindow.h"

extern "C" {
#include "../LogicFiles/calculator.h"
}

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
  Q_OBJECT

public:
  MainWindow(QWidget *parent = nullptr);
  ~MainWindow();

private slots:
  void GetInfo();
  void check_fields();
  void func_clicked();
  void symbols_clicked();
  void brackets_clicked();
  void operators_clicked();
  void on_dotSym_clicked();
  void on_delAll_clicked();
  void on_subFunc_clicked();
  void on_delElem_clicked();
  void on_credCalc_clicked();
  void on_deposCalc_clicked();
  void on_showGraph_clicked();
  void on_resultFunc_clicked();
  void print_graph(char *chars_array);

private:
  Ui::MainWindow *ui;
  CreditWindow *secondWindow;
  DepositWindow *thirdWindow;

  std::string str_;
  QPushButton *button_;

  bool is_dot_ = false;
  bool graph_open_ = false;

  size_t size_ = 0;
  int l_brackets_ = 0;
  int r_brackets_ = 0;

  char last_symbol_ = str_.back();
  char operators[6] = {'-', '+', '*', '/', '^', 'd'};
};
#endif // MAINWINDOW_H
