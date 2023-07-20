#include "controller_calculator.h"

namespace s21 {
/*
  ============================ C A L C U L A T O R ============================
*/
void ControllerCalculator::set_rad(const bool &is_rad) noexcept { model_.set_rad(is_rad); }

bool ControllerCalculator::IsInteger(const double &res) noexcept {
  if (std::fabs(res - (int)res) < std::numeric_limits<double>::epsilon())
    return true;
  else
    return false;
}

QString ControllerCalculator::Calculator(const std::string &str) noexcept {
  model_.Notation(str);
  model_.Calculations();
  model_.ClearOutput();
  double res_ = model_.get_res();
  QString err_ = "ERROR: Incorrect data!";
  return !model_.get_error() ? QString::number(res_, 'f', IsInteger(res_) ? 0 : 7) : err_;
}

void ControllerCalculator::GraphStart(const std::string &str) noexcept {
  model_.Notation(str);
}

double ControllerCalculator::Graph(const double &x) noexcept {
  model_.set_x(x);
  model_.Calculations();
  return model_.get_res();
}

void ControllerCalculator::GraphEnd() noexcept { model_.ClearOutput(); }
/*
  ============================ C A L C U L A T O R ============================
*/
}  // namespace s21
