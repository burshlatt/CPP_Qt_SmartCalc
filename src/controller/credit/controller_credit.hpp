#ifndef SMARTCALC_CONTROLLER_CREDIT_CONTROLLER_CREDIT_HPP
#define SMARTCALC_CONTROLLER_CREDIT_CONTROLLER_CREDIT_HPP

#include "model_credit.hpp"

class CreditController {
public:
    using Info = CreditModel::Info;

public:
    CreditController(CreditModel* model) :
        model_(model)
    {}

public:
    Info CalculateAnnuityCredit(double loan_amount, double term, double percent) {
        return model_->CalculateAnnuityCredit(loan_amount, term, percent);
    }

    Info CalculateDifferentiatedCredit(double loan_amount, double term, double percent) {
        return model_->CalculateDifferentiatedCredit(loan_amount, term, percent);
    }

private:
    CreditModel* model_;
};

#endif  // SMARTCALC_CONTROLLER_CREDIT_CONTROLLER_CREDIT_HPP
