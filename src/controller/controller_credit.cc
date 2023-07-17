#include "controller_credit.h"

namespace s21 {
/*
  ============================ V A L I D A T O R S ============================
*/
bool ControllerCredit::IsCorrectInt(const QString &str) const noexcept {
  for (int i = 0; i < str.size(); i++) {
    if (str[i] < '0' || str[i] > '9') {
      return false;
    }
  }
  return true;
}

bool ControllerCredit::IsCorrectDec(const QString &str) const noexcept {
  for (int i = 0; i < str.size(); i++) {
    if ((str[i] < '0' || str[i] > '9') && str[i] != '.') {
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
void ControllerCredit::set_sum(const double &sum) noexcept { model_.set_sum(sum); }
void ControllerCredit::set_term(const double &term) noexcept { model_.set_term(term); }
void ControllerCredit::set_percent(const QString &percent) noexcept { model_.set_percent(percent.toDouble()); }
/*
  ============================== M U T A T O R S ==============================
*/

/*
  ===================== C R E D I T - C A L C U L A T O R =====================
*/
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
