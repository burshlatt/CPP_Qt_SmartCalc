#ifndef SRC_MODEL_MODEL_CALCULATOR_H_
#define SRC_MODEL_MODEL_CALCULATOR_H_

#include <cmath>
#include <array>
#include <stack>
#include <string>
#include <iostream>
#include <functional>
#include <unordered_map>

namespace s21 {
class ModelCalculator {
 public:
  ModelCalculator() {}
  ~ModelCalculator() {}

  bool get_error() const noexcept;
  double get_res() const noexcept;

  void set_x(const double &num) noexcept;
  void set_rad(const bool &graph) noexcept;

  void ClearOutput() noexcept;
  void Calculations() noexcept;
  void GetNum(double &x) noexcept;
  void GetNums(const int &opt) noexcept;
  void PopFunctions(const int &opt) noexcept;
  bool ConvertNums(const size_t &i) noexcept;
  void GetNums(double &x, double &y) noexcept;
  void InsertNumOutput(size_t &index) noexcept;
  void Notation(const std::string &str) noexcept;
  void PushLogic(const std::string &str) noexcept;
  void PushFunctions(size_t &index, const int &opt) noexcept;

 private:
  int pos_ = 0;
  std::string str_;
  bool is_rad_ = false;
  bool is_error_ = false;
  double result_ = 0.0;
  double x_value_ = 0.0;
  double x_ = 0.0, y_ = 0.0;
  std::stack<double> num_buffer_;
  std::stack<std::string> stack_;
  std::array<std::string, 256> output_;
  const std::unordered_map<std::string, std::function<double(double)>> func_map_ {
    { "ln", [](double x){ return std::log(x); } },
    { "cos", [](double x){ return std::cos(x); } },
    { "sin", [](double x){ return std::sin(x); } },
    { "tan", [](double x){ return std::tan(x); } },
    { "abs", [](double x){ return std::fabs(x); } },
    { "acos", [](double x){ return std::acos(x); } },
    { "asin", [](double x){ return std::asin(x); } },
    { "atan", [](double x){ return std::atan(x); } },
    { "sqrt", [](double x){ return std::sqrt(x); } },
    { "log", [](double x){ return std::log10(x); } }
  };
  const std::unordered_map<std::string, std::function<double(double, double)>> oper_map_ {
    { "+", [](double x, double y){ return x + y; } },
    { "-", [](double x, double y){ return x - y; } },
    { "*", [](double x, double y){ return x * y; } },
    { "/", [](double x, double y){ return x / y; } },
    { "^", [](double x, double y){ return std::pow(x, y); } },
    { "mod", [](double x, double y){ return std::fmod(x, y); } }
  };
};
}  // namespace s21

#endif  // SRC_MODEL_MODEL_CALCULATOR_H_
