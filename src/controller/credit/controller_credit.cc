#include "controller_credit.h"

namespace s21 {
/*
  ===================== C R E D I T - C A L C U L A T O R =====================
*/
void ControllerCredit::set_sum(const double &sum) noexcept { model_.set_sum(sum); }
void ControllerCredit::set_term(const double &term) noexcept { model_.set_term(term); }
void ControllerCredit::set_percent(const QString &percent) noexcept { model_.set_percent(percent.toDouble()); }

QVector<QString> ControllerCredit::AnnuCred() noexcept {
  model_.AnnuCred();
  std::vector<double> result_ = model_.get_cred();
  QVector<QString> format_result_;
  for (size_t i = 0; i < result_.size(); i++) {
    format_result_.push_back(QString::number(result_[i], 'f', 2));
  }
  return format_result_;
}

QVector<QString> ControllerCredit::DifferCred() noexcept {
  model_.DifferCred();
  std::vector<double> result_ = model_.get_cred();
  QVector<QString> format_result_;
  for (size_t i = 0; i < result_.size(); i++) {
    format_result_.push_back(QString::number(result_[i], 'f', 2));
  }
  return format_result_;
}
/*
  ===================== C R E D I T - C A L C U L A T O R =====================
*/
}  // namespace s21
