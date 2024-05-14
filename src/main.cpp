#include <QApplication>

#include "view_calc.hpp"
#include "view_credit.hpp"

#include "model_calc.hpp"
#include "model_credit.hpp"

#include "controller_calc.hpp"
#include "controller_credit.hpp"

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    app.setWindowIcon(QIcon(":/images/smart_calc.png"));

    CreditModel credit_model;
    CreditController credit_controller(&credit_model);
    CreditView credit_view(&credit_controller);

    CalcModel calc_model;
    CalcController calc_controller(&calc_model);
    CalcView calc_view(&calc_controller, &credit_view);

    calc_view.show();

    return app.exec();
}
