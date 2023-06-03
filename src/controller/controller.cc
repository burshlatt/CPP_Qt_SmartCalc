#include "controller.h"

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
