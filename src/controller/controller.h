#ifndef SRC_CONTROLLER_CONTROLLER_H_
#define SRC_CONTROLLER_CONTROLLER_H_

#include "../model/model.h"
#include "../view/calculator.h"

namespace s21 {
    class controller {
        public:
            controller() {}
            ~controller() {}
            
            bool IsError() noexcept;
            bool IsInteger(const double &res) noexcept;
            bool IsGraph(const std::string &str) noexcept;
            bool IsCorrectInt(const QString &str) const noexcept;
            bool IsCorrectDec(const QString &str) const noexcept;
            bool IsCorrect(const std::string &str) noexcept;

            void GraphEnd() noexcept;
            void SetRad(const bool &is_rad) noexcept;
            void GraphStart(const std::string &str) noexcept;

            double Graph(const double &x) noexcept;
            double AddSum(const double &sum, const int &time) const noexcept;

            QString Calculator(const std::string &str) noexcept;
            QVector<QString> AnnuCred(const double &sum, const int &term, const double &percent) noexcept;
            QVector<QString> DifferCred(const double &sum, const int &term, const double &percent) noexcept;

        private:
            s21::model model_;
    };
} // namespace s21 

#endif // SRC_CONTROLLER_CONTROLLER_H_
