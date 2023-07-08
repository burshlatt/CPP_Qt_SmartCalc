#ifndef SRC_CONTROLLER_CONTROLLER_H_
#define SRC_CONTROLLER_CONTROLLER_H_

#include "../model/model.h"

namespace s21 {
    class controller {
        public:
            controller() {}
            ~controller() {}
            
            bool IsError() noexcept;
            bool IsInteger(const double &res) noexcept;
            bool IsGraph(const std::string &str) noexcept;
            bool IsCorrect(const std::string &str) noexcept;

            void GraphEnd() noexcept;
            void SetRad(const bool &is_rad) noexcept;
            void GraphStart(const std::string &str) noexcept;

            double Graph(const double &x) noexcept;
            double Calculator(const std::string &str) noexcept;

            std::vector<double> AnnuCred(const double &sum, const int &term, const double &percent) noexcept;
            std::vector<double> DifferCred(const double &sum, const int &term, const double &percent) noexcept;

        private:
            s21::model model_;
    };
} // namespace s21 

#endif // SRC_CONTROLLER_CONTROLLER_H_
