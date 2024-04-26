#ifndef SMARTCALC_CONTROLLER_CALC_CONTROLLER_CALC_HPP
#define SMARTCALC_CONTROLLER_CALC_CONTROLLER_CALC_HPP

#include <optional>
#include <string_view>

#include "model_calc.hpp"

class CalcController {
public:
    CalcController(CalcModel* model) :
        model_(model)
    {}

    std::optional<double> Calculate(std::string_view notation, double x = 0.0) {
        return model_->Calculate(notation, x);
    }

    CalcModel::Coords CalculateGraph(std::string_view input, double x_start, double x_end) {
        return model_->CalculateGraph(input, x_start, x_end);
    }

private:
    CalcModel* model_;
};

#endif  // SMARTCALC_CONTROLLER_CALC_CONTROLLER_CALC_HPP
