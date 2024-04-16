#ifndef VIEW_DEPOSIT_H
#define VIEW_DEPOSIT_H

#include <QComboBox>
#include <QDateEdit>
#include <QMessageBox>
#include <QVBoxLayout>

#include "controller_deposit.hpp"

namespace Ui {
class ViewDeposit;
}

class ViewDeposit : public QDialog {
  Q_OBJECT

 public:
  explicit ViewDeposit(QWidget *parent = nullptr);
  ~ViewDeposit();

 private slots:
  void GetTypes() noexcept;
  void AddWaste() noexcept;
  void AddPayment() noexcept;
  void AddWasteClicked() noexcept;
  void CalculatorClicked() noexcept;
  void ShowResultClicked() noexcept;
  void AddPaymentClicked() noexcept;
  void DeleteWasteClicked() noexcept;
  void DeletePaymentClicked() noexcept;
  void Add(const bool &is_waste) noexcept;
  void keyPressEvent(QKeyEvent *event) override;

 signals:
  void firstWindow();

 private:
  Ui::ViewDeposit *ui_;
  s21::ControllerDeposit calc_;

  int period_ = 0;
  int time_type_ = 0;
  int add_count_ = 0;
  int waste_count_ = 0;
  bool is_cap_ = false;

  QString sum_;
  QString term_;
  QString percent_;
  QString tax_rate_;
  QDate last_date_;
  QDateEdit *date_;
  QLineEdit *line_;
  QComboBox *combo_box_;
  QVBoxLayout *add_box_;
  QVBoxLayout *waste_box_;
  QVector<QString> add_;
  QVector<QString> waste_;
  std::vector<int> add_days_;
  std::vector<int> waste_days_;
  std::vector<int> add_period_;
  std::vector<int> waste_period_;
  QVector<QDateEdit *> date_edits_add_;
  QVector<QLineEdit *> line_edits_add_;
  QVector<QComboBox *> combo_boxes_add_;
  QVector<QDateEdit *> date_edits_waste_;
  QVector<QLineEdit *> line_edits_waste_;
  QVector<QComboBox *> combo_boxes_waste_;
};

#endif  // VIEW_DEPOSIT_H
