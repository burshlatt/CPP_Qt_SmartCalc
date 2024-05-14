#ifndef SMARTCALC_MODEL_CREDIT_MODEL_CREDIT_HPP
#define SMARTCALC_MODEL_CREDIT_MODEL_CREDIT_HPP

#include <vector>

class CreditModel {
public:
    struct Info {
        double monthly_payment;
        double total_payment;
        double overpayment;
        std::vector<double> monthly_payments;
    };

public:
    Info CalculateAnnuityCredit(double loan_amount, double term, double percent);
    Info CalculateDifferentiatedCredit(double loan_amount, double term, double percent);
};

#endif  // SMARTCALC_MODEL_CREDIT_MODEL_CREDIT_HPP
