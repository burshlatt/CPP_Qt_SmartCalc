#ifndef DEPOSITWINDOW_H
#define DEPOSITWINDOW_H

#include <QComboBox>
#include <QDateEdit>
#include <QDialog>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QScrollArea>
#include <QVBoxLayout>

#include <string>

extern "C" {
#include "../CFiles/s21_calculator.h"
}

namespace Ui {
class DepositWindow;
}

class DepositWindow : public QDialog {
  Q_OBJECT

public:
  explicit DepositWindow(QWidget *parent = nullptr);
  ~DepositWindow();

private slots:
  void today_is();
  void check_types();
  void check_correct_data();
  void on_addWaste_clicked();
  void on_calculator_clicked();
  void on_showResult_clicked();
  void on_addPayment_clicked();
  void on_deleteWaste_clicked();
  void on_deletePayment_clicked();
  void check_correct_sum(QString sum);
  void additional_payment(double *add_sum);
  void additional_waste(double *waste_sum);

signals:
  void firstWindow();

private:
  Ui::DepositWindow *ui;

  char *date_end;

  int error = 0;
  int error_dop = 0;
  int time_type = 0;
  int period_type = 0;
  int capitalization = 0;
  int count_of_elem_add = 0;
  int count_of_elem_waste = 0;

  QDate date_qdate;
  QDate date_qdate_max;

  QVBoxLayout *addVbox;
  QVBoxLayout *wasteVbox;

  QVector<QDateEdit *> dateEditsAdd;
  QVector<QLineEdit *> lineEditsAdd;
  QVector<QComboBox *> comboBoxesAdd;

  QVector<QDateEdit *> dateEditsWaste;
  QVector<QLineEdit *> lineEditsWaste;
  QVector<QComboBox *> comboBoxesWaste;
};

#endif // DEPOSITWINDOW_H
