#ifndef SRC_CONTROLLER_CONTROLLER_H_
#define SRC_CONTROLLER_CONTROLLER_H_

#include "../model/model.h"

namespace s21 {
    class controller {
        public:
            controller() {};
            ~controller() {};
            
            double Calculator(const std::string str) noexcept;
            void GraphStart(const std::string str) noexcept;
            double Graph(const double x) noexcept;
            void GraphEnd() noexcept;

        private:
            s21::model model_;
    };
} // namespace s21 

#endif // SRC_CONTROLLER_CONTROLLER_H_
