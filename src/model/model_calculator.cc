#include "model_calculator.h"

namespace s21 {
/*
  ================================= ACCESSORS =================================
*/
double ModelCalculator::get_res() const noexcept { return result_; }
bool ModelCalculator::get_error() const noexcept { return is_error_; }
/*
  ================================= ACCESSORS =================================
*/

/*
  ================================= MUTATORS ==================================
*/
void ModelCalculator::set_x(const double &num) noexcept { x_value_ = num; }
void ModelCalculator::set_rad(const bool &graph) noexcept { is_rad_ = graph; }
/*
  ================================= MUTATORS ==================================
*/

/*
  ============================ C A L C U L A T O R ============================
*/
void ModelCalculator::GetNums(double &x) noexcept {
  x = num_buffer_.top();
  num_buffer_.pop();
}

void ModelCalculator::GetNums(double &x, double &y) noexcept {
  x = num_buffer_.top();
  num_buffer_.pop();
  y = num_buffer_.top();
  num_buffer_.pop();
}

void ModelCalculator::GetNums() noexcept {
  if (option_ == 1) {
    GetNums(x_);
  } else if (option_ == 2) {
    GetNums(x_, y_);
  } else if (option_ == 3) {
    GetNums(x_);
    x_ = is_rad_ ? x_ : x_ * M_PI / 180;
  } else if (option_ == 4) {
    const double n_num_ = num_buffer_.top();
    num_buffer_.pop();
    num_buffer_.push(-n_num_);
  }
}

void ModelCalculator::InsertNumOutput(size_t &index) noexcept {
  if (isdigit(str_[index]) || str_[index] == 'x' || str_[index] == 'P') {
    int i = 0;
    bool is_negative_ = false;
    char char_str_[255] = {'\0'};
    if (str_[index - 1] == '-' && str_[index - 2] == '(') is_negative_ = true;
    while (isdigit(str_[index]) || str_[index] == '.' || str_[index] == 'x' || str_[index] == 'P' || str_[index] == 'i') {
      char_str_[i++] = str_[index++];
    }
    output_[pos_++] = is_negative_ ? std::string(char_str_) + "-" : std::string(char_str_);
  }
}

void ModelCalculator::PushLogic(const std::string &str) noexcept {
  if (str == "mod" || str == "*" || str == "/") {
    while (!stack_.empty() && (stack_.top() == "mod" || stack_.top() == "*"
    || stack_.top() == "/" || stack_.top() == "^" || stack_.top() == "!")) {
      output_[pos_++] = stack_.top();
      stack_.pop();
    }
  } else if (str == "+" || str == "-") {
    while (!stack_.empty() && (stack_.top() == "mod" || stack_.top() == "*"
    || stack_.top() == "/" || stack_.top() == "+" || stack_.top() == "-"
    || stack_.top() == "^" || stack_.top() == "!")) {
      output_[pos_++] = stack_.top();
      stack_.pop();
    }
  }
  stack_.push(str);
}

void ModelCalculator::PushFunctions(size_t &index) noexcept {
  if (option_ == 1) {
    if (str_[index] == '^') {
      stack_.push("^");
    } else {
      char buffer_[255] = {'\0'};
      for (size_t i = 0; str_[index] != '('; i++) buffer_[i] = str_[index++];
      if (std::string(buffer_).size()) stack_.push(std::string(buffer_));
      stack_.push("(");
    }
  } else if (option_ == 2) {
    if (str_[index] == 'm') {
      PushLogic("mod");
      index += 2;
    } else if (str_[index] == '*') {
      PushLogic("*");
    } else if (str_[index] == '/') {
      PushLogic("/");
    } else if (str_[index] == '+') {
      PushLogic("+");
    } else if (str_[index] == '-') {
      if (str_[index - 1] == '(' && !isdigit(str_[index + 1]) &&
          str_[index + 1] != 'P' && str_[index + 1] != 'x')
        PushLogic("!");
      else if (str_[index - 1] != '(')
        PushLogic("-");
    }
  }
}

void ModelCalculator::PopFunctions() noexcept {
  if (option_ == 1) {
    while (!stack_.empty() && stack_.top() != "(") {
      output_[pos_++] = stack_.top();
      stack_.pop();
    }
    if (stack_.empty()) {
      is_error_ = true;
    } else {
      stack_.pop();
      auto it_ = func_map_.find(stack_.top());
      if ((it_ != func_map_.end() || stack_.top() == "^") && !stack_.empty()) {
        output_[pos_++] = stack_.top();
        stack_.pop();
      }
    }
  } else if (option_ == 2) {
    while (!stack_.empty() && !is_error_) {
      if (stack_.top() == "(") {
        is_error_ = true;
      } else {
        output_[pos_++] = stack_.top();
        stack_.pop();
      }
    }
  }
}

bool ModelCalculator::ConvertNums(const size_t &i) noexcept {
  double num_ = 0.0;
  if (isdigit(output_[i].front()) || output_[i].front() == 'x' ||
      output_[i].front() == 'P') {
    if (output_[i].front() == 'x')
      num_ = x_value_;
    else if (output_[i].front() == 'P')
      num_ = M_PI;
    else
      num_ = atof(output_[i].c_str());
    if (output_[i].back() == '-') num_ = -num_;
    num_buffer_.push(num_);
    return true;
  }
  return false;
}

void ModelCalculator::Notation(const std::string &str) noexcept {
  str_ = str;
  for (size_t i = 0; i < str_.size() && !is_error_; i++) {
    InsertNumOutput(i);
    switch (str_[i]) {
      case 'c':
      case 's':
      case 't':
      case 'a':
      case 'l':
      case '^':
      case '(':
        option_ = 1;
        PushFunctions(i);
        break;
      case 'm':
      case '*':
      case '/':
      case '+':
      case '-':
        option_ = 2;
        PushFunctions(i);
        break;
      case ')':
        option_ = 1;
        PopFunctions();
        break;
      case '=':
        option_ = 2;
        PopFunctions();
        break;
    }
  }
}

void ModelCalculator::Calculations() noexcept {
  for (int i = 0; i < pos_; i++) {
    if (!ConvertNums(i)) {
      switch (output_[i].front()) {
        case '+':
        case '-':
        case '*':
        case '/':
        case '^':
        case 'm':
          option_ = 2;
          break;
        case 'c':
        case 's':
        case 't':
        case 'a':
          option_ = output_[i] == "sqrt" || output_[i] == "abs" ? 1 : 3;
          break;
        case 'l':
          option_ = 1;
          break;
        case '!':
          option_ = 4;
          break;
      }
      GetNums();
      auto o_it_ = oper_map_.find(output_[i]);
      auto f_it_ = func_map_.find(output_[i]);
      if (o_it_ != oper_map_.end())
        num_buffer_.push(o_it_->second(x_, y_));
      if (f_it_ != func_map_.end())
        num_buffer_.push(f_it_->second(x_));
    }
  }
  result_ = num_buffer_.top();
  num_buffer_.pop();
}

void ModelCalculator::ClearOutput() noexcept { pos_ = 0; }

/*
  ============================ C A L C U L A T O R ============================
*/
}  // namespace s21
