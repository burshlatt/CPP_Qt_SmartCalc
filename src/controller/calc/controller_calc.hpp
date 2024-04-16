#ifndef SMARTCALC_CONTROLLER_CALC_CONTROLLER_HPP
#define SMARTCALC_CONTROLLER_CALC_CONTROLLER_HPP

#include <optional>
#include <string_view>

#include "model_calc.hpp"

class CalcController {
public:
    CalcController(CalcModel* model) :
        model_(model)
    {}

    std::optional<double> Calculate(std::string_view notation) {
        return model_->Calculate(notation);
    }

private:
    CalcModel* model_;
};

#endif  // SMARTCALC_CONTROLLER_CALC_CONTROLLER_HPP
