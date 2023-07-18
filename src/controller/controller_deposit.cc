#include "controller_deposit.h"

namespace s21 {
/*
  ============================ V A L I D A T O R S ============================
*/
bool ControllerDeposit::IsCorrectInt(const QString &str) const noexcept {
  for (int i = 0; i < str.size(); i++) {
    if (str[i] < '0' || str[i] > '9') {
      return false;
    }
  }
  return true;
}

bool ControllerDeposit::IsCorrectDec(const QString &str) const noexcept {
  for (int i = 0; i < str.size(); i++) {
    if (((str[i] < '0' || str[i] > '9') && str[i] != '.') || str.front() == '.' || str.back() == '.') {
      return false;
    }
  }
  return true;
}
/*
  ============================ V A L I D A T O R S ============================
*/

/*
  ============================== M U T A T O R S ==============================
*/
void ControllerDeposit::set_cap(const bool &cap) noexcept { model_.set_cap(cap); }
void ControllerDeposit::set_sum(const double &sum) noexcept { model_.set_sum(sum); }
void ControllerDeposit::set_term(const double &term) noexcept { model_.set_term(term); }
void ControllerDeposit::set_period(const int &period) noexcept { model_.set_period(period); }
void ControllerDeposit::set_tax(const QString &tax) noexcept { model_.set_tax(tax.toDouble()); }
void ControllerDeposit::set_add_days(const std::vector<int> &days) noexcept { model_.set_add_days(days); }
void ControllerDeposit::set_waste_days(const std::vector<int> &days) noexcept { model_.set_waste_days(days); }
void ControllerDeposit::set_percent(const QString &percent) noexcept { model_.set_percent(percent.toDouble()); }
void ControllerDeposit::set_period_add(const std::vector<int> &period) noexcept { model_.set_period_add(period); }
void ControllerDeposit::set_period_waste(const std::vector<int> &period) noexcept { model_.set_period_waste(period); }

void ControllerDeposit::set_add(const QVector<QString> &add) noexcept {
  std::vector<double> buffer_;
  for (qsizetype i = 0; i < add.size(); i++) {
    buffer_.push_back(add[i].toDouble());
  }
  model_.set_add(buffer_);
}

void ControllerDeposit::set_waste(const QVector<QString> &waste) noexcept {
  std::vector<double> buffer_;
  for (qsizetype i = 0; i < waste.size(); i++) {
    buffer_.push_back(waste[i].toDouble());
  }
  model_.set_waste(buffer_);
}
/*
  ============================== M U T A T O R S ==============================
*/

/*
  ==================== D E P O S I T - C A L C U L A T O R ====================
*/
QVector<QString> ControllerDeposit::Deposit() noexcept {
  model_.Deposit();
  std::array<double, 4> result_ = model_.get_depos();
  QVector<QString> format_result_;
  for (size_t i = 0; i < result_.size(); i++) {
    format_result_.push_back(QString::number(result_[i], 'f', 2));
  }
  return format_result_;
}
/*
  ==================== D E P O S I T - C A L C U L A T O R ====================
*/
}  // namespace s21
