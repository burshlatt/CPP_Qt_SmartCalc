#ifndef SRC_SMARTCALC_CALCULATOR_H_
#define SRC_SMARTCALC_CALCULATOR_H_

#include <cmath>
// #include <ctime>
#include <stack>
#include <vector>
#include <string>
#include <iostream>
// #include <algorithm>

using std::cout;
using std::endl;

namespace s21 {
  class calculator {
    public:
      calculator() {}

      std::string get_str() const noexcept;
      void set_str(const std::string other) noexcept;

      void Notation();
      void Calculations();
      void PopFunctions(size_t *index);
      void InsertNumOutput(size_t *index);
      void PushFunctions(size_t *index, const int variant);

      void print();
      void test();

    private:
      std::string str_;
      // std::string output_;
      double result_ = 0.0;
      double x_value_ = 0.0;
      bool is_graph_ = false;
      bool is_error_ = false;
      std::stack<double> buffer_;
      std::stack<std::string> stack_;
      std::stack<std::string> output_;
  };
}

#endif // SRC_SMARTCALC_CALCULATOR_H_
