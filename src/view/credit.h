#ifndef CREDITWINDOW_H
#define CREDITWINDOW_H

#include <QDialog>
#include <QScreen>
#include "../controller/controller.h"

namespace Ui {
class credit;
}

class credit : public QDialog {
  Q_OBJECT

public:
  explicit credit(QWidget *parent = nullptr);
  ~credit();

private slots:
  bool IsCorrect();
  void on_showResult_clicked();
  void on_calculator_clicked();

signals:
  void firstWindow();

private:
  Ui::credit *ui;
  s21::controller calc_;
};

#endif // CREDITWINDOW_H
