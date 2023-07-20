#ifndef SRC_CONTROLLER_CONTROLLER_CALCULATOR_H_
#define SRC_CONTROLLER_CONTROLLER_CALCULATOR_H_

#include <QtGui>
#include <string>
#include <iostream>
#include <unordered_map>

#include "../model/model_calculator.h"

namespace s21 {
class ControllerCalculator {
 public:
  ControllerCalculator() {}
  ~ControllerCalculator() {}

  void set_rad(const bool &is_rad) noexcept;

  bool IsInteger(const double &res) noexcept;

  void GraphEnd() noexcept;
  double Graph(const double &x) noexcept;
  void GraphStart(const std::string &str) noexcept;
  
  QString Calculator(const std::string &str) noexcept;

 private:
  s21::ModelCalculator model_;
};
}  // namespace s21

#endif  // SRC_CONTROLLER_CONTROLLER_CALCULATOR_H_
