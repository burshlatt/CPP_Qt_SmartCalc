#ifndef SRC_SMARTCALC_CALCULATOR_H_
#define SRC_SMARTCALC_CALCULATOR_H_

#include <cmath>
#include <stack>
#include <vector>
#include <string>
#include <iostream>

namespace s21 {
  class calculator {
    public:
      calculator() {}
      ~calculator() {};
      
      double get_res() const noexcept;
      bool get_error() const noexcept;

      void set_graph() noexcept;
      void set_x(double num) noexcept;
      void set_str(const std::string other) noexcept;

      void Notation() noexcept;
      void Calculations() noexcept;
      void ClearContainers() noexcept;
      void GetNums(double &x) noexcept;
      bool ConvertNums(size_t i) noexcept;
      void GetNums(double &x, double &y) noexcept;
      void InsertNumOutput(size_t &index) noexcept;
      void PopFunctions(const int variant) noexcept;
      void PushLogic(const std::string other) noexcept;
      bool CustomIsDigit(const std::string other) const noexcept;
      void PushFunctions(size_t &index, const int variant) noexcept;
      void DoCalculations(const std::string other, const int variant) noexcept;

    private:
      std::string str_;
      double result_ = 0.0;
      double x_value_ = 0.0;
      bool is_graph_ = false;
      bool is_error_ = false;
      const size_t array_size_ = 11;
      std::stack<double> num_buffer_;
      std::stack<std::string> stack_;
      std::vector<std::string> output_;
      std::string functions_[11]{"cos", "sin", "tan", "acos", "asin", "atan", "ln", "log", "sqrt", "abs", "^"};
  };
}

#endif // SRC_SMARTCALC_CALCULATOR_H_
