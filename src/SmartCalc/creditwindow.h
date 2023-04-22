#ifndef CREDITWINDOW_H
#define CREDITWINDOW_H

#include <QApplication>
#include <QDialog>
#include <QScreen>

extern "C" {
#include "../CFiles/s21_calculator.h"
}

namespace Ui {
class CreditWindow;
}

class CreditWindow : public QDialog {
  Q_OBJECT

public:
  explicit CreditWindow(QWidget *parent = nullptr);
  ~CreditWindow();

private slots:
  void check_correct_data();
  void on_showResult_clicked();
  void on_calculator_clicked();

signals:
  void firstWindow();

private:
  Ui::CreditWindow *ui;

  int error = 0;
};

#endif // CREDITWINDOW_H
