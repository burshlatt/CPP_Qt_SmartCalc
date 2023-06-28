#ifndef CREDITWINDOW_H
#define CREDITWINDOW_H

#include <QDialog>
#include <QScreen>
#include "../controller/controller.h"

#include <QComboBox>
#include <QDateEdit>
#include <QDialog>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QScrollArea>
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
  void DelRow();
  bool IsCorrect();
  void AddRow(QString str);
  void on_showResult_clicked();
  void on_calculator_clicked();

signals:
  void firstWindow();

private:
  int count_ = 0;
  Ui::credit *ui;
  QVBoxLayout *addVbox;
  s21::controller calc_;
//  QVector<QLabel *> labels_;
};

#endif // CREDITWINDOW_H
