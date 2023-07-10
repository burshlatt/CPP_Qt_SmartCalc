#include "model.h"

/*
  ==================== CALCULATOR ACCESSORS ====================
*/
double s21::model::get_res() const noexcept { return result_; }
bool s21::model::get_error() const noexcept { return is_error_; }
/*
  ==================== CALCULATOR ACCESSORS ====================
*/

/*
  ==================== CREDIT && DEPOSIT ACCESSORS ====================
*/
std::vector<double> s21::model::get_cred() const noexcept { return cred_arr_; }
std::array<double, 4> s21::model::get_depos() const noexcept { return depos_arr_; }
/*
  ==================== CREDIT && DEPOSIT ACCESSORS ====================
*/

/*
  ==================== CALCULATOR MUTATORS ====================
*/
void s21::model::set_x(const double &num) noexcept { x_value_ = num; }
void s21::model::set_rad(const bool &graph) noexcept { is_rad_ = graph; }
/*
  ==================== CALCULATOR MUTATORS ====================
*/

/*
  ==================== CREDIT && DEPOSIT MUTATORS ====================
*/
void s21::model::set_sum(const double &sum) noexcept { sum_ = sum; }
void s21::model::set_tax(const double &tax) noexcept { tax_ = tax; }
void s21::model::set_cap(const bool &cap) noexcept { is_cap_ = cap; }
void s21::model::set_term(const double &term) noexcept { term_ = term; }
void s21::model::set_period(const double &period) noexcept { period_ = period; }
void s21::model::set_percent(const double &percent) noexcept { percent_ = percent; }
/*
  ==================== CREDIT && DEPOSIT MUTATORS ====================
*/

/*
  ==================== C A L C U L A T O R ====================
*/
void s21::model::GetNums(double &x) noexcept {
  x = num_buffer_.top();
  num_buffer_.pop();
}

void s21::model::GetNums(double &x, double &y) noexcept {
  x = num_buffer_.top();
  num_buffer_.pop();
  y = num_buffer_.top();
  num_buffer_.pop();
}

void s21::model::GetNums() noexcept {
  if (option_ == 1) {
    GetNums(x_);
  } else if (option_ == 2) {
    GetNums(x_, y_);
  } else if (option_ == 3) {
    GetNums(x_);
    x_ = is_rad_ ? x_ : x_ * M_PI / 180;
  } else if (option_ == 4) {
    double n_num_ = num_buffer_.top();
    num_buffer_.pop();
    num_buffer_.push(-n_num_);
  }
}

void s21::model::InsertNumOutput(size_t &index) noexcept {
  if (isdigit(str_[index]) || str_[index] == 'x' || str_[index] == 'P') {
    int i = 0;
    bool is_negative_ = false;
    char char_str_[255] = {'\0'};
    if (str_[index - 1] == '-' && str_[index - 2] == '(') is_negative_ = true;
    while (isdigit(str_[index]) || str_[index] == '.' || str_[index] == 'x' 
    || str_[index] == 'P' || str_[index] == 'i') {
      char_str_[i++] = str_[index++];
    }
    output_[pos_++] = is_negative_ ? std::string(char_str_) + "-" : std::string(char_str_);
  }
}

void s21::model::PushLogic(const std::string &str) noexcept {
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

void s21::model::PushFunctions(size_t &index) noexcept {
  if (option_ == 1) {
    if (str_[index] == '^') {
      stack_.push("^");
    } else {
      char buffer[255] = {'\0'};
      for (size_t i = 0; str_[index] != '('; i++)
        buffer[i] = str_[index++];
      if (std::string(buffer).size())
        stack_.push(std::string(buffer));
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
      if (str_[index - 1] == '(' && !isdigit(str_[index + 1])
       && str_[index + 1] != 'P' && str_[index + 1] != 'x')
        PushLogic("!");
      else if (str_[index - 1] != '(')
        PushLogic("-");
    }
  }
}

void s21::model::PopFunctions() noexcept {
  if (option_ == 1) {
    while (!stack_.empty() && stack_.top() != "(") {
      output_[pos_++] = stack_.top();
      stack_.pop();
    }
    if (stack_.empty()) {
      is_error_ = true;
    } else {
      stack_.pop();
      for (size_t i = 0; i < array_size_ && !stack_.empty(); i++) {
        if (stack_.top() == functions_[i]) {
          output_[pos_++] = stack_.top();
          stack_.pop();
        }
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

bool s21::model::ConvertNums(const size_t &i) noexcept {
  bool status = false;
  double num_ = 0.0;
  if (isdigit(output_[i].front()) || output_[i].front() == 'x' || output_[i].front() == 'P') {
    if (output_[i].front() == 'x')
      num_ = x_value_;
    else if (output_[i].front() == 'P')
      num_ = M_PI;
    else
      num_ = atof(output_[i].c_str());
    if (output_[i].back() == '-')
      num_ = -num_;
    num_buffer_.push(num_);
    status = true;
  }
  return status;
}

void s21::model::Notation(const std::string &str) noexcept {
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

void s21::model::DoCalculations() noexcept {
  if (func_ == "+")
    num_buffer_.push(y_ + x_);
  else if (func_ == "-")
    num_buffer_.push(y_ - x_);
  else if (func_ == "*")
    num_buffer_.push(y_ * x_);
  else if (func_ == "/")
    num_buffer_.push(y_ / x_);
  else if (func_ == "ln")
    num_buffer_.push(log(x_));
  else if (func_ == "cos")
    num_buffer_.push(cos(x_));
  else if (func_ == "sin")
    num_buffer_.push(sin(x_));
  else if (func_ == "tan")
    num_buffer_.push(tan(x_));
  else if (func_ == "abs")
    num_buffer_.push(fabs(x_));
  else if (func_ == "acos")
    num_buffer_.push(acos(x_));
  else if (func_ == "asin")
    num_buffer_.push(asin(x_));
  else if (func_ == "atan")
    num_buffer_.push(atan(x_));
  else if (func_ == "sqrt")
    num_buffer_.push(sqrt(x_));
  else if (func_ == "log")
    num_buffer_.push(log10(x_));
  else if (func_ == "^")
    num_buffer_.push(pow(y_, x_));
  else if (func_ == "mod")
    num_buffer_.push(fmod(y_, x_));
}

void s21::model::Calculations() noexcept {
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
      func_ = output_[i];
      GetNums();
      DoCalculations();
    }
  }
  result_ = num_buffer_.top();
  num_buffer_.pop();
}

void s21::model::ClearOutput() noexcept {
  pos_ = 0;
}

/*
  ==================== C A L C U L A T O R ====================
*/

/*
  ==================== C R E D I T - C A L C U L A T O R ====================
*/

void s21::model::ClearCredit() noexcept {
  overpay_ = 0.0;
  month_pay_ = 0.0;
  f_payment_ = 0.0;
  l_payment_ = 0.0;
  result_sum_ = 0.0;
  cred_arr_.clear();
}

void s21::model::AnnuCred() noexcept {
  ClearCredit();
  double percent_ = percent_ / (100 * percent_);
  month_pay_ = sum_ * percent_ / (1 - pow(1 + percent_, -term_));
  overpay_ = month_pay_ * term_ - sum_;
  result_sum_ = sum_ + overpay_;
  cred_arr_.push_back(overpay_);
  cred_arr_.push_back(result_sum_);
  cred_arr_.push_back(month_pay_);
}

void s21::model::DifferCred() noexcept {
  ClearCredit();
  int days[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
  time_t now_;
  time(&now_);
  struct tm *local_ = localtime(&now_);
  int month_ = local_->tm_mon;
  double credit_body_ = sum_ / term_;
  overpay_ = (sum_ * (percent_ / 100) * days[month_]) / 365;
  f_payment_ = overpay_ + credit_body_;
  cred_arr_.push_back(f_payment_);
  double sum_copy_ = sum_;
  double percent_month_ = 0.0;
  for (int i = 0; i < term_ - 1; i++) {
    sum_copy_ -= credit_body_;
    month_ = month_ == 11 ? 0 : month_ + 1;
    percent_month_ = (sum_copy_ * (percent_ / 100) * days[month_]) / 365;
    overpay_ += percent_month_;
    cred_arr_.push_back(credit_body_ + percent_month_);
  }
  l_payment_ = percent_month_ + credit_body_;
  result_sum_ = sum_ + overpay_;
  cred_arr_.push_back(l_payment_);
  cred_arr_.push_back(overpay_);
  cred_arr_.push_back(result_sum_);
}

/*
  ==================== C R E D I T - C A L C U L A T O R ====================
*/

/*
  ==================== D E P O S I T - C A L C U L A T O R ====================
*/

std::array<double, 4> s21::model::Deposit() noexcept {
  int format_time_ = FormatTime();
  std::array<double, 4> result_;
  double res_per_ = 0.0, tax_res_ = 0.0, sum_tax_res_ = 0.0, sum_res_ = 0.0;
  if (!is_cap_) {
    sum_res_ = sum_;
    res_per_ = (sum_ * (percent_ / 100) / format_time_) * term_;
  } else {
    sum_res_ = sum_ * pow(1 + (percent_ / 100) / format_time_, term_ / 365 * format_time_);
    res_per_ = sum_res_ - sum_;
  }
  tax_res_ = res_per_ - 1000000 * (7.5 / 100);
  if (tax_res_ > 0) {
    tax_res_ *= tax_ / 100;
  } else {
    tax_res_ = 0;
  }
  sum_tax_res_ = res_per_ - tax_res_;
  result_[0] = res_per_;
  result_[1] = tax_res_;
  result_[2] = sum_tax_res_;
  result_[3] = sum_res_;
  return result_;
}

int s21::model::FormatTime() noexcept {
  int n = 0;
  if (!is_cap_) {
    if (period_ == 1 || period_ == 7) {
      n = 365;
    } else if (period_ == 2) {
      n = 52;
      term_ = floor(term_ / 7);
    } else if (period_ == 3) {
      n = 12;
      term_ = floor(term_ / 30.5);
    } else if (period_ == 4) {
      n = 4;
      term_ = floor(term_ / 91.25);
    } else if (period_ == 5) {
      n = 2;
      term_ = floor(term_ / 182.5);
    } else if (period_ == 6) {
      n = 1;
      term_ = floor(term_ / 365);
    }
  } else {
    if (period_ == 1) {
      n = 365;
    } else if (period_ == 2) {
      n = 52;
    } else if (period_ == 3) {
      n = 12;
    } else if (period_ == 4) {
      n = 4;
    } else if (period_ == 5) {
      n = 2;
    } else if (period_ == 6 || period_ == 7) {
      n = 1;
    }
  }
  return n;
}

double s21::model::AddSum(const double &sum, const int &time) const noexcept {
  double sum_result_ = 0.0;
  for (int i = 0; i < time; i++) {
    sum_result_ += sum;
  }
  return sum_result_;
}

/*
  ==================== D E P O S I T - C A L C U L A T O R ====================
*/
