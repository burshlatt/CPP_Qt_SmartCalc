#ifndef DEPOSIT_H
#define DEPOSIT_H

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
  void add_waste() noexcept;
  void CheckTypes() noexcept;
  void add_payment() noexcept;
  bool DataIsCorrect() noexcept;
  void on_addWaste_clicked() noexcept;
  void on_calculator_clicked() noexcept;
  void on_showResult_clicked() noexcept;
  void on_addPayment_clicked() noexcept;
  void on_deleteWaste_clicked() noexcept;
  void on_deletePayment_clicked() noexcept;

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

  bool is_cap_ = false;
  bool is_error_ = false;

  QString sum_;
  QString term_;
  QString percent_;
  QString tax_rate_;

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
