#ifndef SRC_CONTROLLER_CONTROLLER_H_
#define SRC_CONTROLLER_CONTROLLER_H_

#include "../model/model.h"
#include "../view/calculator.h"

namespace s21 {
    class controller {
        public:
            controller() {}
            ~controller() {}

            void set_cap(const bool &cap) noexcept;
            void set_sum(const double &sum) noexcept;
            void set_tax(const QString &tax) noexcept;
            void set_rad(const bool &is_rad) noexcept;
            void set_term(const double &term) noexcept;
            void set_period(const int &period) noexcept;
            void set_percent(const QString &percent) noexcept;
            
            bool IsError() noexcept;
            bool IsInteger(const double &res) noexcept;
            bool IsGraph(const std::string &str) noexcept;
            bool IsCorrectInt(const QString &str) const noexcept;
            bool IsCorrectDec(const QString &str) const noexcept;
            bool IsCorrect(const std::string &str) noexcept;

            void GraphEnd() noexcept;
            void GraphStart(const std::string &str) noexcept;

            double Graph(const double &x) noexcept;
            double AddSum(const double &sum, const int &time) const noexcept;

            QVector<QString> AnnuCred() noexcept;
            QVector<QString> DifferCred() noexcept;
            QString Calculator(const std::string &str) noexcept;
            QVector<QString> s21::controller::Deposit() noexcept;

        private:
            s21::model model_;
    };
} // namespace s21 

#endif // SRC_CONTROLLER_CONTROLLER_H_
