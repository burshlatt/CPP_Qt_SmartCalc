#ifndef SMARTCALC_MODEL_CREDIT_MODEL_CREDIT_HPP
#define SMARTCALC_MODEL_CREDIT_MODEL_CREDIT_HPP

#include <vector>

class CreditModel {
public:
    struct Info {
        double overpayment;
        double total_payment;
        double monthly_payment;
        std::vector<double> monthly_payments;
    };

public:
    Info CalculateAnnuityCredit(double loan_amount, int term, double percent);
    Info CalculateDifferentiatedCredit(double loan_amount, int term, double percent);
};

#endif  // SMARTCALC_MODEL_CREDIT_MODEL_CREDIT_HPP
