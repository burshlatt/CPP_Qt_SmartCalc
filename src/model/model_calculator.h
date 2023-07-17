#ifndef SRC_MODEL_MODEL_CALCULATOR_H_
#define SRC_MODEL_MODEL_CALCULATOR_H_

#include <cmath>
#include <array>
#include <stack>
#include <string>
#include <iostream>

namespace s21 {
class ModelCalculator {
 public:
  ModelCalculator() {}
  ~ModelCalculator() {}

  bool get_error() const noexcept;
  double get_res() const noexcept;

  void set_x(const double &num) noexcept;
  void set_rad(const bool &graph) noexcept;

  void GetNums() noexcept;
  void ClearOutput() noexcept;
  void Calculations() noexcept;
  void PopFunctions() noexcept;
  void DoCalculations() noexcept;
  void GetNums(double &x) noexcept;
  bool ConvertNums(const size_t &i) noexcept;
  void PushFunctions(size_t &index) noexcept;
  void GetNums(double &x, double &y) noexcept;
  void InsertNumOutput(size_t &index) noexcept;
  void Notation(const std::string &str) noexcept;
  void PushLogic(const std::string &str) noexcept;

 private:
  int pos_ = 0;
  int option_ = 0;
  std::string str_;
  std::string func_;
  bool is_rad_ = false;
  bool is_error_ = false;
  double result_ = 0.0;
  double x_value_ = 0.0;
  double x_ = 0.0, y_ = 0.0;
  std::stack<double> num_buffer_;
  std::stack<std::string> stack_;
  std::array<std::string, 256> output_;
  const std::array<std::string, 11> functions_ = {"cos",  "sin",  "tan", "acos",
                                                  "asin", "atan", "ln",  "log",
                                                  "sqrt", "abs",  "^"};
};
}  // namespace s21

#endif  // SRC_MODEL_MODEL_CALCULATOR_H_
