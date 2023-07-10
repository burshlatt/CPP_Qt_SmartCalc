#include "controller.h"

void s21::controller::SetRad(const bool &is_rad) noexcept {
    model_.set_rad(is_rad);
}

bool s21::controller::IsGraph(const std::string &str) noexcept {
    bool status_ = false;
    for (size_t i = 0; i < str.size(); i++) {
        if (str[i] == 'x') {
            status_ = true;
        }
    }
    return status_;
}

bool s21::controller::IsCorrect(const std::string &str) noexcept {
    bool status_ = true;
    if (str.back() != ')' && (str.back() < '0' || str.back() > '9') && str.back() != 'x')
        status_ = false;
    int l_bracket = 0, r_bracket = 0;
    for (size_t i = 0; i < str.size(); i++) {
        if (str[i] == '(') l_bracket++;
        if (str[i] == ')') r_bracket++;
    }
    if (l_bracket != r_bracket) status_ = false;
    return status_;
}

bool s21::controller::IsError() noexcept {
    return model_.get_error();
}

bool s21::controller::IsInteger(const double &res) noexcept {
    if (std::fabs(res - (int)res) < std::numeric_limits<double>::epsilon())
        return true;
    else
        return false;
}

QString s21::controller::Calculator(const std::string &str) noexcept {
    model_.Notation(str);
    model_.Calculations();
    model_.ClearOutput();
    double res_ = model_.get_res();
    return QString::number(res_, 'f', IsInteger(res_) ? 0 : 7);
}

void s21::controller::GraphStart(const std::string &str) noexcept {
    model_.Notation(str);
}

double s21::controller::Graph(const double &x) noexcept {
    model_.set_x(x);
    model_.Calculations();
    return model_.get_res();
}

void s21::controller::GraphEnd() noexcept {
    model_.ClearOutput();
}

QVector<QString> s21::controller::AnnuCred(const double &sum, const int &term, const double &percent) noexcept {
    model_.AnnuCred(sum, term, percent);
    std::vector<double> result_ = model_.get_cred();
    QVector<QString> format_result_;
    for (size_t i = 0; i < result_.size(); i++) {
        format_result_.push_back(QString::number(result_[i], 'f', 2));
    }
    return format_result_;
}

QVector<QString> s21::controller::DifferCred(const double &sum, const int &term, const double &percent) noexcept {
    model_.DifferCred(sum, term, percent);
    std::vector<double> result_ = model_.get_cred();
    QVector<QString> format_result_;
    for (size_t i = 0; i < result_.size(); i++) {
        format_result_.push_back(QString::number(result_[i], 'f', 2));
    }
    return format_result_;
}

bool s21::controller::IsCorrectInt(const QString &str) const noexcept {
  for (int i = 0; i < str.size(); i++) {
    if (str[i] < '0' || str[i] > '9') {
      return false;
    }
  }
  return true;
}

bool s21::controller::IsCorrectDec(const QString &str) const noexcept {
  for (int i = 0; i < str.size(); i++) {
    if ((str[i] < '0' || str[i] > '9') && str[i] != '.') {
      return false;
    }
  }
  return true;
}

double s21::controller::AddSum(const double &sum, const int &time) const noexcept {
    return model_.AddSum(sum, time);
}
