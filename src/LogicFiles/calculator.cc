#include "calculator.h"

s21::calculator::~calculator() {
  str_ = "";
  result_ = 0.0;
  x_value_ = 0.0;
  is_graph_ = false;
  is_error_ = false;
}

double s21::calculator::get_res() const noexcept {
  return result_;
}

void s21::calculator::set_x(double num) noexcept {
  x_value_ = num;
}

void s21::calculator::set_graph(bool status) noexcept {
  is_graph_ = status;
}

void s21::calculator::set_str(const std::string other) noexcept {
  str_ = other;
}

bool s21::calculator::CustomIsDigit(const std::string other) const noexcept {
  return (other.front() >= '0' && other.front() <= '9') ? true : false;
}

bool s21::calculator::IsNegative(const std::string other) const noexcept {
  return other.back() == '-'  ? true : false;
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
  if (isdigit(str_[index]) || str_[index] == 'x') {
    bool is_negative_ = false;
    if (str_[index - 1] == '-' && str_[index - 2] == '(') {
      is_negative_ = true;
    }
    char char_str_[255] = {'\0'};
    for (auto i = 0; isdigit(str_[index]) || str_[index] == '.' || str_[index] == 'x'; i++) {
      char_str_[i] = str_[index++];
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

void s21::calculator::PushFunctions(size_t &index, const int variant) noexcept {
  if (variant == 1) {
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
  } else if (variant == 2) {
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
        if (str_[index - 1] != '(' || !isdigit(str_[index + 1])) {
          PushLogic("-");
        }
        break;
    }
  }
}

void s21::calculator::PopFunctions(const int variant) noexcept {
  if (variant == 1) {
    while (!stack_.empty() && stack_.top() != "(") {
      output_.push_back(stack_.top());
      stack_.pop();
    }
    if (stack_.empty()) {
      is_error_ = true;
    } else {
      stack_.pop();
      for (size_t i = 0; i < functions_.size() && !stack_.empty(); i++) {
        if (stack_.top() == functions_[i]) {
          output_.push_back(stack_.top());
          stack_.pop();
        }
      }
    }
  } else if (variant == 2) {
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
        PushFunctions(i, 1);
        break;
      case 'm':
      case '*':
      case '/':
      case '+':
      case '-':
        PushFunctions(i, 2);
        break;
      case ')':
        PopFunctions(1);
        break;
      case '=':
        PopFunctions(2);
        break;
    }
  }
  output_.shrink_to_fit();
  Calculations();
}

void s21::calculator::DoCalculations(const std::string other, const int variant) noexcept {
  double x_ = 0.0, y_ = 0.0;
  if (variant == 1) {
    GetNums(x_);
  } else if (variant == 2) {
    GetNums(x_, y_);
  } else if (variant == 3) {
    GetNums(x_);
    x_ = is_graph_ ? x_ * M_PI / 180 : x_;
  } else if (variant == 4) {
    double n_num_ = num_buffer_.top();
    num_buffer_.pop();
    num_buffer_.push(-n_num_);
  }
  if (other == "+") {
    num_buffer_.push(y_ + x_);
  } else if (other == "-") {
    num_buffer_.push(y_ - x_);
  } else if (other == "*") {
    num_buffer_.push(y_ * x_);
  } else if (other == "/") {
    num_buffer_.push(y_ / x_);
  } else if (other == "ln") {
    num_buffer_.push(log(x_));
  } else if (other == "log") {
    num_buffer_.push(log10(x_));
  } else if (other == "abs") {
    num_buffer_.push(fabs(x_));
  } else if (other == "cos") {
    num_buffer_.push(cos(x_));
  } else if (other == "sin") {
    num_buffer_.push(sin(x_));
  } else if (other == "tan") {
    num_buffer_.push(tan(x_));
  } else if (other == "acos") {
    num_buffer_.push(acos(x_));
  } else if (other == "asin") {
    num_buffer_.push(asin(x_));
  } else if (other == "atan") {
    num_buffer_.push(atan(x_));
  } else if (other == "sqrt") {
    num_buffer_.push(sqrt(x_));
  } else if (other == "^") {
    num_buffer_.push(pow(y_, x_));
  } else if (other == "mod") {
    num_buffer_.push(fmod(y_, x_));
  }
}

void s21::calculator::Calculations() noexcept {
  double num_ = 0.0;
  for (size_t i = 0; i < output_.size(); i++) {
    if (CustomIsDigit(output_[i]) || output_[i] == "x") {
      if (output_[i] == "x" && is_graph_) {
        num_ = x_value_;
      } else {
        num_ = atof(output_[i].c_str());
      }
      if (IsNegative(output_[i])) {
        num_ = -num_;
      }
      num_buffer_.push(num_);
    } else {
      switch (output_[i].front()) {
        case '+':
          DoCalculations("+", 2);
          break;
        case '-':
          if (!CustomIsDigit(output_[i - 1])) {
            DoCalculations("", 4);
          } else {
            DoCalculations("-", 2);
          }
          break;
        case '*':
          DoCalculations("*", 2);
          break;
        case '/':
          DoCalculations("/", 2);
          break;
        case '^':
          DoCalculations("^", 2);
          break;
        case 'm':
          DoCalculations("mod", 2);
          break;
        case 'c':
          DoCalculations("cos", 3);
          break;
        case 's':
          if (output_[i][1] == 'i') {
            DoCalculations("sin", 3);
          } else {
            DoCalculations("sqrt", 1);
          }
          break;
        case 't':
          DoCalculations("tan", 3);
          break;
        case 'a':
          if (output_[i][1] == 'b') {
            DoCalculations("abs", 1);
          } else if (output_[i][1] == 'c') {
            DoCalculations("acos", 3);
          } else if (output_[i][1] == 's') {
            DoCalculations("asin", 3);
          } else if (output_[i][1] == 't') {
            DoCalculations("atan", 3);
          }
          break;
        case 'l':
          if (output_[i][1] == 'n') {
            DoCalculations("ln", 1);
          } else {
            DoCalculations("log", 1);
          }
          break;
      }
    }
  }
  result_ = num_buffer_.top();
}

int main () {
  s21::calculator test_;
  test_.set_graph(true);
  test_.set_x(2);
  test_.set_str("-abs(-(-sin(3)+cos(4)))*sqrt(9)mod2*2*x=");
  // test_.set_str("cos(56.33)*sin(87)+(-(-3+5))/tan(66)+cos(22)-sin(55)*(tan(99)/log(77)+ln(66))^(2+3)/sqrt(9)*abs(-99)=");
  test_.Notation();
  cout << "\nРезультат: " << test_.get_res() << endl << endl;
  return 0;
}
