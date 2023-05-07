#include "calculator.h"

double s21::calculator::get_res() const noexcept {
  return result_;
}

bool s21::calculator::get_error() const noexcept {
  return is_error_;
}

void s21::calculator::set_x(double num) noexcept {
  x_value_ = num;
}

void s21::calculator::set_str(const std::string other) noexcept {
  str_ = other;
}

void s21::calculator::set_graph() noexcept {
  is_graph_ = false;
  for (size_t i = 0; i < str_.size() && !is_graph_; i++) {
    if (str_[i] == 'x') {
      is_graph_ = true;
    }
  }
}

bool s21::calculator::CustomIsDigit(const std::string other) const noexcept {
  return (other.front() >= '0' && other.front() <= '9') ? true : false;
}

void s21::calculator::GetNums(double &x) noexcept {
  x = num_buffer_.top();
  num_buffer_.pop();
}

void s21::calculator::GetNums(double &x, double &y) noexcept {
  x = num_buffer_.top();
  num_buffer_.pop();
  y = num_buffer_.top();
  num_buffer_.pop();
}

void s21::calculator::InsertNumOutput(size_t &index) noexcept {
  if (isdigit(str_[index]) || str_[index] == 'x' || str_[index] == 'P') {
    bool is_negative_ = false;
    if (str_[index - 1] == '-' && str_[index - 2] == '(') {
      is_negative_ = true;
    }
    char char_str_[255] = {'\0'};
    int i = 0;
    while (isdigit(str_[index]) || str_[index] == '.' || str_[index] == 'x' 
    || str_[index] == 'P' || str_[index] == 'i') {
      char_str_[i++] = str_[index++];
    }
    if (is_negative_) {
      output_.push_back(std::string(char_str_) + "-");
    } else {
      output_.push_back(std::string(char_str_));
    }
  }
}

void s21::calculator::PushLogic(const std::string other) noexcept {
  if (other == "mod" || other == "*" || other == "/") {
    while (!stack_.empty() && (stack_.top() == "mod" 
    || stack_.top() == "*" || stack_.top() == "/")) {
      output_.push_back(stack_.top());
      stack_.pop();
    }
  } else if (other == "+" || other == "-") {
    while (!stack_.empty() && (stack_.top() == "mod" || stack_.top() == "*" 
    || stack_.top() == "/" || stack_.top() == "+" || stack_.top() == "-")) {
      output_.push_back(stack_.top());
      stack_.pop();
    }
  }
  stack_.push(other);
}

void s21::calculator::PushFunctions(size_t &index) noexcept {
  if (option_ == 1) {
    if (str_[index] == '^') {
      stack_.push("^");
    } else {
      char buffer[255] = {'\0'};
      for (size_t i = 0; str_[index] != '('; i++) {
        buffer[i] = str_[index++];
      }
      if (std::string(buffer).size()) {
        stack_.push(std::string(buffer));
      }
      stack_.push("(");
    }
  } else if (option_ == 2) {
    switch (str_[index]) {
      case 'm':
        PushLogic("mod");
        index += 2;
        break;
      case '*':
        PushLogic("*");
        break;
      case '/':
        PushLogic("/");
        break;
      case '+':
        PushLogic("+");
        break;
      case '-':
        if (str_[index - 1] == '(' && !isdigit(str_[index + 1])) {
          PushLogic("!");
        } else if (str_[index - 1] != '(') {
          PushLogic("-");
        }
        break;
    }
  }
}

void s21::calculator::PopFunctions() noexcept {
  if (option_ == 1) {
    while (!stack_.empty() && stack_.top() != "(") {
      output_.push_back(stack_.top());
      stack_.pop();
    }
    if (stack_.empty()) {
      is_error_ = true;
    } else {
      stack_.pop();
      for (size_t i = 0; i < array_size_ && !stack_.empty(); i++) {
        if (stack_.top() == functions_[i]) {
          output_.push_back(stack_.top());
          stack_.pop();
        }
      }
    }
  } else if (option_ == 2) {
    while (!stack_.empty() && !is_error_) {
      if (stack_.top() == "(") {
        is_error_ = true;
      } else {
        output_.push_back(stack_.top());
        stack_.pop();
      }
    }
  }
}

bool s21::calculator::ConvertNums(size_t i) noexcept {
  bool status = false;
  double num_ = 0.0;
  if (CustomIsDigit(output_[i]) || output_[i] == "x" || output_[i] == "Pi") {
    if (output_[i] == "x" && is_graph_) {
      num_ = x_value_;
    } else if (output_[i] == "Pi") {
      num_ = M_PI;
    } else {
      num_ = atof(output_[i].c_str());
    }
    if (output_[i].back() == '-') {
      num_ = -num_;
    }
    num_buffer_.push(num_);
    status = true;
  }
  return status;
}

void s21::calculator::Notation() noexcept {
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
  is_error_ ? (void)0 : Calculations();
}

void s21::calculator::DoCalculations() noexcept {
  double x_ = 0.0, y_ = 0.0;
  if (option_ == 1) {
    GetNums(x_);
  } else if (option_ == 2) {
    GetNums(x_, y_);
  } else if (option_ == 3) {
    GetNums(x_);
    x_ = is_graph_ ? x_ * M_PI / 180 : x_;
  } else if (option_ == 4) {
    double n_num_ = num_buffer_.top();
    num_buffer_.pop();
    num_buffer_.push(-n_num_);
  }
  if (func_ == "+") {
    num_buffer_.push(y_ + x_);
  } else if (func_ == "-") {
    num_buffer_.push(y_ - x_);
  } else if (func_ == "*") {
    num_buffer_.push(y_ * x_);
  } else if (func_ == "/") {
    num_buffer_.push(y_ / x_);
  } else if (func_ == "ln") {
    num_buffer_.push(log(x_));
  } else if (func_ == "log") {
    num_buffer_.push(log10(x_));
  } else if (func_ == "abs") {
    num_buffer_.push(fabs(x_));
  } else if (func_ == "cos") {
    num_buffer_.push(cos(x_));
  } else if (func_ == "sin") {
    num_buffer_.push(sin(x_));
  } else if (func_ == "tan") {
    num_buffer_.push(tan(x_));
  } else if (func_ == "acos") {
    num_buffer_.push(acos(x_));
  } else if (func_ == "asin") {
    num_buffer_.push(asin(x_));
  } else if (func_ == "atan") {
    num_buffer_.push(atan(x_));
  } else if (func_ == "sqrt") {
    num_buffer_.push(sqrt(x_));
  } else if (func_ == "^") {
    num_buffer_.push(pow(y_, x_));
  } else if (func_ == "mod") {
    num_buffer_.push(fmod(y_, x_));
  }
}

void s21::calculator::Calculations() noexcept {
  for (size_t i = 0; i < output_.size(); i++) {
    std::cout << output_[i] << " ";
    if (!ConvertNums(i)) {
      switch (output_[i].front()) {
        case '!':
          output_[i] = "";
          option_ = 4;
          break;
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
          option_ = (output_[i] == "sqrt" || output_[i] == "abs") ? 1 : 3;
          break;
        case 'l':
          option_ = 1;
          break;
      }
      func_ = output_[i];
      DoCalculations();
    }
  }
  result_ = num_buffer_.top();
  ClearContainers();
}

void s21::calculator::ClearContainers() noexcept {
  while (!stack_.empty()) {
    stack_.pop();
  }
  while (!num_buffer_.empty()) {
    num_buffer_.pop();
  }
  while (!output_.empty()) {
    output_.pop_back();
  }
}

int main () {
  s21::calculator test_;
  test_.set_str("(-(2*3)-(-3*3)^2)=");
  test_.set_graph();
  test_.Notation();
  std::cout << std::endl << std::endl << test_.get_error() << std::endl;
  std::cout << std::endl << "Результат: " << test_.get_res() << std::endl << std::endl;
  return 0;
}
