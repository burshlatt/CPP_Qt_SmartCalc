#ifndef SRC_VALIDATOR_VALIDATOR_CALCULATOR_H_
#define SRC_VALIDATOR_VALIDATOR_CALCULATOR_H_

#include <QtGui>
#include <limits>
#include <string>
#include <iostream>
#include <QPushButton>
#include <unordered_map>

namespace s21 {
class ValidatorCalculator {
 public:
  ValidatorCalculator() {}
  ~ValidatorCalculator() {}

  bool IsGraph(const std::string &str) const noexcept;
  bool IsCorrect(const std::string &str) const noexcept;
  bool IsCorrectDec(const QString &str) const noexcept;
  bool IsOperator(const std::string &str) const noexcept;
  bool IsCorrectOperator(const std::string &str) const noexcept;

  void GetBrackets(const std::string &str, int &l_br, int &r_br) const noexcept;

  QString FormatDel(const std::string &str, bool &is_dot_) const noexcept;
  QString FormatDot(const std::string &str, bool &is_dot_) const noexcept;
  QString FormatSubtract(const std::string &str, bool &is_dot_) const noexcept;
  QString FormatSymbols(const char &last, const QPushButton *btn, bool &is_dot_) const noexcept;
  QString FormatOperators(std::string &str, const QPushButton *btn, bool &is_dot_) const noexcept;
  QString FormatBrackets(const std::string &str, const QPushButton *btn, bool &is_dot_) const noexcept;
  QString FormatFunctions(const std::string &str, const QPushButton *btn, bool &is_dot_) const noexcept;

 private:
  const std::unordered_map<char, bool> oper_skip_ {
    { '+', true },
    { '-', true },
    { '*', true },
    { '/', true },
    { '^', true },
    { 'd', true },
    { '(', true }
  };
};
}  // namespace s21

#endif  // SRC_VALIDATOR_VALIDATOR_CALCULATOR_H_
