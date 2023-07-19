#include "validator_calculator.h"

namespace s21 {
/*
  ============================ V A L I D A T O R S ============================
*/

void ValidatorCalculator::GetBrackets(const std::string &str, int &l_br, int &r_br) const noexcept {
  for (size_t i = 0; i < str.size(); i++) {
    if (str[i] == '(') l_br++;
    if (str[i] == ')') r_br++;
  }
}

bool ValidatorCalculator::IsGraph(const std::string &str) const noexcept {
  for (size_t i = 0; i < str.size(); i++) {
    if (str[i] == 'x') {
      return true;
    }
  }
  return false;
}

bool ValidatorCalculator::IsCorrect(const std::string &str) const noexcept {
  if (str.back() != ')' && (str.back() < '0' || str.back() > '9') &&
      str.back() != 'x' && str.back() != 'i')
    return false;
  int l_bracket_ = 0, r_bracket_ = 0;
  GetBrackets(str, l_bracket_, r_bracket_);
  if (l_bracket_ != r_bracket_) return false;
  return true;
}

bool ValidatorCalculator::IsCorrectDec(const QString &str) const noexcept {
  if (str.toDouble() > 1000000 || str.toDouble() < -1000000 || !str.size()) {
    return false;
  }
  if (str[0] == '-' || (str[0] >= '0' && str[0] <= '9')) {
    for (int i = 1; i < str.size(); i++) {
      if (((str[i] < '0' || str[i] > '9') && str[i] != '.') || str.back() == '.' || (str[i] == '.' && str[i - 1] == '-')) {
        return false;
      }
    }
  } else {
    return false;
  }
  return true;
}

bool ValidatorCalculator::IsCorrectOperator(const std::string &str) const noexcept {
  size_t size_ = str.size();
  char last_ = str.back();
  if ((size_ > 0 && size_ < 255 && last_ != '(' && last_ != '.') && ((last_ == '-' && str[size_ - 2] != '(') || last_ != '-'))
    return true;
  return false;
}

bool ValidatorCalculator::IsOperator(const std::string &str) const noexcept {
  char last_ = str.back();
  auto it_ = oper_skip_.find(last_);
  if (it_ != oper_skip_.end() && (last_ != '-' || str[str.size() - 2] != '('))
    return it_->second;
  return false;
}

QString ValidatorCalculator::FormatSymbols(const char &last, const QPushButton *btn, bool &is_dot_) const noexcept {
  QString result_;
  QString btn_text_ = btn->text();
  if (last == 'x' || last == ')' || last == 'i') {
    result_ += "*";
  }
  if (btn_text_ == "Pi" && last != '.') {
    if (last >= '0' && last <= '9') {
      result_ += "*";
    }
    result_ += btn_text_;
    is_dot_ = false;
  } else if (btn_text_ == 'x' && last != '.') {
    if (last >= '0' && last <= '9') {
      result_ += "*";
    }
    result_ += "x";
    is_dot_ = false;
  } else if (btn_text_ >= '0' && btn_text_ <= '9') {
    result_ += btn_text_;
  }
  return result_;
}

QString ValidatorCalculator::FormatFunc(const std::string &str, const QPushButton *btn, bool &is_dot_) const noexcept {
  QString result_;
  char last_ = str.back();
  QString btn_text_ = btn->text();
  if (str.size() < 255 && last_ != '.') {
    if ((last_ >= '0' && last_ <= '9') || last_ == ')' || last_ == 'i') {
      result_ += "*";
    }
    result_ += btn->text() + "(";
    is_dot_ = false;
  }
  return result_;
}

QString ValidatorCalculator::FormatBrackets(const std::string &str, const QPushButton *btn, bool &is_dot_) const noexcept {
  QString result_;
  char last_ = str.back();
  size_t size_ = str.size();
  QString btn_text_ = btn->text();
  int l_bracket_ = 0, r_bracket_ = 0;
  if (last_ != '.') {
    GetBrackets(str, l_bracket_, r_bracket_);
    if (size_ < 255) {
      if (btn->text() == '(') {
        if ((last_ >= '0' && last_ <= '9') || last_ == 'x' || last_ == ')') {
          result_ += "*";
        }
        result_ += "(";
        is_dot_ = false;
      } else if (btn->text() == ')' && r_bracket_ < l_bracket_) {
        auto it_ = oper_skip_.find(last_);
        if (it_ == oper_skip_.end()) {
          result_ += ")";
          is_dot_ = false;
        }
      }
    }
  }
  return result_;
}
/*
  ============================ V A L I D A T O R S ============================
*/
}  // namespace s21
