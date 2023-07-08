#ifndef CREDITWINDOW_H
#define CREDITWINDOW_H

#include "../controller/controller.h"

#include <QDate>
#include <QLabel>
#include <QScreen>
#include <QDialog>
#include <QLineEdit>
#include <QDateEdit>
#include <QComboBox>
#include <QPushButton>
#include <QScrollArea>
#include <QMessageBox>
#include <QVBoxLayout>

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

  void DelRow();
  void on_showResult_clicked();
  void on_calculator_clicked();
  void AddRow(int term, std::vector<double> res_arr, bool is_annu);

signals:
  void firstWindow();

private:
  int count_ = 0;
  Ui::credit *ui;
  QVBoxLayout *addVbox;
  s21::controller calc_;
};

#endif // CREDITWINDOW_H
