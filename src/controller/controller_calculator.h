#ifndef SRC_CONTROLLER_CONTROLLER_CALCULATOR_H_
#define SRC_CONTROLLER_CONTROLLER_CALCULATOR_H_

#include <QtGui>
#include <limits>
#include <string>
#include <iostream>

#include "../model/model_calculator.h"

namespace s21 {
class ControllerCalculator {
 public:
  ControllerCalculator() {}
  ~ControllerCalculator() {}

  void set_rad(const bool &is_rad) noexcept;

  bool IsError() noexcept;
  bool IsInteger(const double &res) noexcept;
  bool IsGraph(const std::string &str) noexcept;
  bool IsCorrect(const std::string &str) noexcept;

  void GraphEnd() noexcept;
  double Graph(const double &x) noexcept;
  void GraphStart(const std::string &str) noexcept;

  QString Calculator(const std::string &str) noexcept;

 private:
  s21::ModelCaclulator model_;
};
}  // namespace s21

#endif  // SRC_CONTROLLER_CONTROLLER_CALCULATOR_H_
