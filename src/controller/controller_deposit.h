#ifndef SRC_CONTROLLER_CONTROLLER_DEPOSIT_H_
#define SRC_CONTROLLER_CONTROLLER_DEPOSIT_H_

#include <QtGui>
#include <array>
#include <vector>
#include <iostream>

#include "../model/model_deposit.h"

namespace s21 {
class ControllerDeposit {
 public:
  ControllerDeposit() {}
  ~ControllerDeposit() {}

  void set_cap(const bool &cap) noexcept;
  void set_sum(const double &sum) noexcept;
  void set_tax(const QString &tax) noexcept;
  void set_term(const double &term) noexcept;
  void set_period(const int &period) noexcept;
  void set_percent(const QString &percent) noexcept;
  void set_add(const QVector<QString> &add) noexcept;
  void set_waste(const QVector<QString> &waste) noexcept;
  void set_add_days(const std::vector<int> &count) noexcept;
  void set_waste_days(const std::vector<int> &count) noexcept;
  void set_period_add(const std::vector<int> &period) noexcept;
  void set_period_waste(const std::vector<int> &period) noexcept;

  bool IsCorrectInt(const QString &str) const noexcept;
  bool IsCorrectDec(const QString &str) const noexcept;

  QVector<QString> Deposit() noexcept;

 private:
  s21::ModelDeposit model_;
};
}  // namespace s21

#endif  // SRC_CONTROLLER_CONTROLLER_DEPOSIT_H_
