#ifndef SRC_MODEL_MODEL_H_
#define SRC_MODEL_MODEL_H_

#include <cmath>
#include <stack>
#include <vector>
#include <string>
#include <iostream>

namespace s21 {
  class model {
    public:
      model() {}
      ~model() {}
      
      double get_res() const noexcept { return result_; }
      bool get_error() const noexcept { return is_error_; }
      std::string get_str() const noexcept { return str_; }
      double get_overpay() const noexcept { return overpay_; }
      double get_month_pay() const noexcept { return month_pay_; }
      double get_f_payment() const noexcept { return f_payment_; }
      double get_l_payment() const noexcept { return l_payment_; }
      double get_result_sum() const noexcept { return result_sum_; }
      
      void set_x(const double num) noexcept { x_value_ = num; }
      void set_rad(const bool graph) noexcept { is_rad_ = graph; }

      void GetNums() noexcept;
      void ClearCredit() noexcept;
      void ClearOutput() noexcept;
      void Calculations() noexcept;
      void PopFunctions() noexcept;
      void DoCalculations() noexcept;
      void GetNums(double &x) noexcept;
      bool ConvertNums(size_t i) noexcept;
      void PushFunctions(size_t &index) noexcept;
      void GetNums(double &x, double &y) noexcept;
      void InsertNumOutput(size_t &index) noexcept;
      void Notation(const std::string str) noexcept;
      void PushLogic(const std::string str) noexcept;
      void AnnuityCredit(double sum, int term, double percent) noexcept;
      void DifferentiatedCredit(double sum, int term, double percent) noexcept;
      bool CustomIsDigit(const std::string str) const noexcept { return str.front() >= '0' && str.front() <= '9'; }

    private:
      int option_ = 0;
      std::string str_;
      std::string func_;
      bool is_rad_ = false;
      bool is_error_ = false;
      double result_ = 0.0;
      double x_value_ = 0.0;
      double overpay_ = 0.0;
      double month_pay_ = 0.0;
      double f_payment_ = 0.0;
      double l_payment_ = 0.0;
      double result_sum_ = 0.0;
      double x_ = 0.0, y_ = 0.0;
      const size_t array_size_ = 11;
      std::stack<double> num_buffer_;
      std::stack<std::string> stack_;
      std::vector<std::string> output_;
      std::string functions_[11]{"cos", "sin", "tan", "acos", "asin", "atan", "ln", "log", "sqrt", "abs", "^"};
  };
}

#endif // SRC_MODEL_MODEL_H_
