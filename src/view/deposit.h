#ifndef DEPOSIT_H
#define DEPOSIT_H

#include "calculator.h"
#include "../controller/controller.h"

namespace Ui {
class deposit;
}

class deposit : public QDialog {
  Q_OBJECT

public:
  explicit deposit(QWidget *parent = nullptr);
  ~deposit();

private slots:
  void CheckTypes();
  bool DataIsCorrect();
  void additional_waste();
  void additional_payment();
  void on_addWaste_clicked();
  bool IsCorrect(QString sum);
  void on_calculator_clicked();
  void on_showResult_clicked();
  void on_addPayment_clicked();
  void on_deleteWaste_clicked();
  void on_deletePayment_clicked();

signals:
  void firstWindow();

private:
  Ui::deposit *ui;
  s21::controller calc_;

  int time_type_ = 0;
  int add_count_ = 0;
  int period_type_ = 0;
  int waste_count_ = 0;

  double add_sum_ = 0.0;
  double waste_sum_ = 0.0;

  bool is_error_ = false;
  bool is_capitalization_ = false;

  QDate last_date_;

  QVBoxLayout *add_box_;
  QVBoxLayout *waste_box_;

  QVector<QDateEdit *> date_edits_add_;
  QVector<QLineEdit *> line_edits_add_;
  QVector<QComboBox *> combo_boxes_add_;

  QVector<QDateEdit *> date_edits_waste_;
  QVector<QLineEdit *> line_edits_waste_;
  QVector<QComboBox *> combo_boxes_waste_;
};

#endif // DEPOSIT_H
