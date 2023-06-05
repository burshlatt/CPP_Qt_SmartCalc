#include "controller.h"

bool s21::controller::IsGraph(const std::string str) noexcept {
    bool status_ = false;
    for (size_t i = 0; i < str.size(); i++) {
        if (str[i] == 'x') {
            status_ = true;
        }
    }
    return status_;
}

void s21::controller::SetRad(const bool is_rad_) noexcept {
    model_.set_rad(is_rad_);
}

bool s21::controller::IsCorrect(const std::string str) noexcept {
    bool status_ = true;
    if (str.back() != ')' && (str.back() < '0' || str.back() > '9') && str.back() != 'x') {
        status_ = false;
    }
    return status_;
}

bool s21::controller::IsError() noexcept {
    return model_.get_error();
}

double s21::controller::Calculator(const std::string str) noexcept {
    model_.Notation(str);
    model_.Calculations();
    model_.ClearOutput();
    return model_.get_res();
}

void s21::controller::GraphStart(const std::string str) noexcept {
    model_.Notation(str);
}

double s21::controller::Graph(const double x) noexcept {
    model_.set_x(x);
    model_.Calculations();
    return model_.get_res();
}

void s21::controller::GraphEnd() noexcept {
    model_.ClearOutput();
}
