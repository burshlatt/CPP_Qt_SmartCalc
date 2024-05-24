#include <cmath>

#include "model_credit.hpp"

CreditModel::Info CreditModel::CalculateAnnuityCredit(double loan_amount, int term, double percent) {
    Info cred_info;

    cred_info.monthly_payments.push_back(std::round(loan_amount * (((percent / (term * 100)) *
        std::pow(1 + (percent / (term * 100)), term)) /
        (std::pow(1 + (percent / (term * 100)), term) - 1)) * 100) / 100);

    cred_info.overpayment = cred_info.monthly_payments[0] * term - loan_amount;
    cred_info.total_payment = loan_amount + cred_info.overpayment;

    while (cred_info.monthly_payments.size() != static_cast<std::size_t>(term)) {
        cred_info.monthly_payments.push_back(cred_info.monthly_payments[0]);
    }

    return cred_info;
}

CreditModel::Info CreditModel::CalculateDifferentiatedCredit(double loan_amount, int term, double percent) {
    Info cred_info;

    int remaining_loan_term{term};
    double remaining_loan_amount{loan_amount};

    while (remaining_loan_term != 0.0) {
        double monthly_payment{(loan_amount / term) + (remaining_loan_amount * percent / (term * 100))};

        cred_info.monthly_payments.push_back(monthly_payment);

        cred_info.total_payment += monthly_payment;
        remaining_loan_amount -= loan_amount / term;

        --remaining_loan_term;
    }

    cred_info.overpayment = cred_info.total_payment - loan_amount;

    return cred_info;
}
