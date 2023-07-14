#include "controller.h"

namespace s21 {
/*
  ============================ V A L I D A T O R S ============================
*/
bool Controller::IsGraph(const std::string &str) noexcept {
  bool status_ = false;
  for (size_t i = 0; i < str.size(); i++) {
    if (str[i] == 'x') {
      status_ = true;
    }
  }
  return status_;
}

bool Controller::IsCorrect(const std::string &str) noexcept {
  bool status_ = true;
  if (str.back() != ')' && (str.back() < '0' || str.back() > '9') &&
      str.back() != 'x' && str.back() != 'i')
    status_ = false;
  int l_bracket = 0, r_bracket = 0;
  for (size_t i = 0; i < str.size(); i++) {
    if (str[i] == '(') l_bracket++;
    if (str[i] == ')') r_bracket++;
  }
  if (l_bracket != r_bracket) status_ = false;
  return status_;
}

bool Controller::IsError() noexcept { return model_.get_error(); }

bool Controller::IsInteger(const double &res) noexcept {
  if (std::fabs(res - (int)res) < std::numeric_limits<double>::epsilon())
    return true;
  else
    return false;
}

bool Controller::IsCorrectInt(const QString &str) const noexcept {
  for (int i = 0; i < str.size(); i++) {
    if (str[i] < '0' || str[i] > '9') {
      return false;
    }
  }
  return true;
}

bool Controller::IsCorrectDec(const QString &str) const noexcept {
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
void Controller::set_cap(const bool &cap) noexcept { model_.set_cap(cap); }
void Controller::set_sum(const double &sum) noexcept { model_.set_sum(sum); }
void Controller::set_term(const double &term) noexcept {
  model_.set_term(term);
}
void Controller::set_rad(const bool &is_rad) noexcept {
  model_.set_rad(is_rad);
}
void Controller::set_period(const int &period) noexcept {
  model_.set_period(period);
}
void Controller::set_tax(const QString &tax) noexcept {
  model_.set_tax(tax.toDouble());
}
void Controller::set_percent(const QString &percent) noexcept {
  model_.set_percent(percent.toDouble());
}
/*
  ============================== M U T A T O R S ==============================
*/

/*
  ============================ C A L C U L A T O R ============================
*/
QString Controller::Calculator(const std::string &str) noexcept {
  model_.Notation(str);
  model_.Calculations();
  model_.ClearOutput();
  double res_ = model_.get_res();
  return QString::number(res_, 'f', IsInteger(res_) ? 0 : 7);
}

void Controller::GraphStart(const std::string &str) noexcept {
  model_.Notation(str);
}

double Controller::Graph(const double &x) noexcept {
  model_.set_x(x);
  model_.Calculations();
  return model_.get_res();
}

void Controller::GraphEnd() noexcept { model_.ClearOutput(); }
/*
  ============================ C A L C U L A T O R ============================
*/

/*
  ===================== C R E D I T - C A L C U L A T O R =====================
*/
QVector<QString> Controller::AnnuCred() noexcept {
  model_.AnnuCred();
  std::vector<double> result_ = model_.get_cred();
  QVector<QString> format_result_;
  for (size_t i = 0; i < result_.size(); i++) {
    format_result_.push_back(QString::number(result_[i], 'f', 2));
  }
  return format_result_;
}

QVector<QString> Controller::DifferCred() noexcept {
  model_.DifferCred();
  std::vector<double> result_ = model_.get_cred();
  QVector<QString> format_result_;
  for (size_t i = 0; i < result_.size(); i++) {
    format_result_.push_back(QString::number(result_[i], 'f', 2));
  }
  return format_result_;
}

double Controller::AddSum(const double &sum, const int &time) const noexcept {
  return model_.AddSum(sum, time);
}
/*
  ===================== C R E D I T - C A L C U L A T O R =====================
*/

/*
  ==================== D E P O S I T - C A L C U L A T O R ====================
*/
QVector<QString> Controller::Deposit() noexcept {
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
