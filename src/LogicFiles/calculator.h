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

      void GetNums() noexcept;
      void Notation() noexcept;
      void Calculations() noexcept;
      void PopFunctions() noexcept;
      void DoCalculations() noexcept;
      void ClearContainers() noexcept;
      void GetNums(double &x) noexcept;
      bool ConvertNums(size_t i) noexcept;
      void PushFunctions(size_t &index) noexcept;
      void GetNums(double &x, double &y) noexcept;
      void InsertNumOutput(size_t &index) noexcept;
      void PushLogic(const std::string other) noexcept;
      bool CustomIsDigit(const std::string other) const noexcept;

    private:
      int option_ = 0;
      std::string str_;
      std::string func_;
      double result_ = 0.0;
      double x_value_ = 0.0;
      bool is_graph_ = false;
      bool is_error_ = false;
      double x_ = 0.0, y_ = 0.0;
      const size_t array_size_ = 11;
      std::stack<double> num_buffer_;
      std::stack<std::string> stack_;
      std::vector<std::string> output_;
      std::string functions_[11]{"cos", "sin", "tan", "acos", "asin", "atan", "ln", "log", "sqrt", "abs", "^"};
  };
}

#endif // SRC_SMARTCALC_CALCULATOR_H_
