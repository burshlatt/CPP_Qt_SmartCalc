#ifndef SRC_SMARTCALC_CALCULATOR_H_
#define SRC_SMARTCALC_CALCULATOR_H_

#include <cmath>
#include <stack>
#include <array>
#include <vector>
#include <string>
#include <iostream>

using std::cout;
using std::endl;

namespace s21 {
  class calculator {
    public:
      calculator() {}
      
      double get_res() const noexcept;

      void set_x(double num) noexcept;
      void set_graph(bool status) noexcept;
      void set_str(const std::string other) noexcept;

      void Notation() noexcept;
      void Calculations() noexcept;
      void GetNums(double &x) noexcept;
      void GetNums(double &x, double &y) noexcept;
      void InsertNumOutput(size_t &index) noexcept;
      void PopFunctions(const int variant) noexcept;
      void PushLogic(const std::string other) noexcept;
      bool IsNegative(const std::string other) const noexcept;
      bool CustomIsDigit(const std::string other) const noexcept;
      void PushFunctions(size_t &index, const int variant) noexcept;
      void DoCalculations(const std::string other, const int variant) noexcept;

    private:
      std::string str_;
      double result_ = 0.0;
      double x_value_ = 0.0;
      bool is_graph_ = false;
      bool is_error_ = false;
      std::stack<double> num_buffer_;
      std::stack<std::string> stack_;
      std::vector<std::string> output_;
      std::array<std::string, 11> functions_ = {"cos", "sin", "tan", "acos", "asin", "atan", "ln", "log", "sqrt", "abs", "^"};
  };
}

#endif // SRC_SMARTCALC_CALCULATOR_H_
