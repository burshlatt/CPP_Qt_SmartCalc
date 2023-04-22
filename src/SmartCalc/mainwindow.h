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
#include "../CFiles/s21_calculator.h"
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
  void check_fields();
  void func_clicked();
  void decompose_func();
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

  int is_x = 0;
  int is_dot = 0;
  int string_size = 0;
  int error_status = 0;
  int graph_is_open = 0;
  int count_of_left_bracket = 0;
  int count_of_right_bracket = 0;

  char last_symbol = '\0';
  char operators[6] = {'-', '+', '*', '/', '^', 'd'};

  QPushButton *button;
  std::string input_string;
};
#endif // MAINWINDOW_H
