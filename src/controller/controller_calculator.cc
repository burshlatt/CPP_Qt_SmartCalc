#include "controller_calculator.h"

namespace s21 {
/*
  ============================ V A L I D A T O R S ============================
*/
bool ControllerCalculator::IsGraph(const std::string &str) noexcept {
  for (size_t i = 0; i < str.size(); i++) {
    if (str[i] == 'x') {
      return true;
    }
  }
  return false;
}

bool ControllerCalculator::IsCorrect(const std::string &str) noexcept {
  if (str.back() != ')' && (str.back() < '0' || str.back() > '9') &&
      str.back() != 'x' && str.back() != 'i')
    return false;
  int l_bracket = 0, r_bracket = 0;
  for (size_t i = 0; i < str.size(); i++) {
    if (str[i] == '(') l_bracket++;
    if (str[i] == ')') r_bracket++;
  }
  if (l_bracket != r_bracket) return false;
  return true;
}

bool ControllerCalculator::IsError() noexcept { return model_.get_error(); }

bool ControllerCalculator::IsInteger(const double &res) noexcept {
  if (std::fabs(res - (int)res) < std::numeric_limits<double>::epsilon())
    return true;
  else
    return false;
}
/*
  ============================ V A L I D A T O R S ============================
*/

/*
  ============================== M U T A T O R S ==============================
*/
void ControllerCalculator::set_rad(const bool &is_rad) noexcept { model_.set_rad(is_rad); }
/*
  ============================== M U T A T O R S ==============================
*/

/*
  ============================ C A L C U L A T O R ============================
*/
QString ControllerCalculator::Calculator(const std::string &str) noexcept {
  model_.Notation(str);
  model_.Calculations();
  model_.ClearOutput();
  double res_ = model_.get_res();
  return QString::number(res_, 'f', IsInteger(res_) ? 0 : 7);
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
