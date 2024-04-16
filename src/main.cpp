#include <QApplication>

#include "view_calc.hpp"
#include "model_calc.hpp"
#include "controller_calc.hpp"

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    app.setWindowIcon(QIcon(":/images/smart_calc.png"));

    CalcModel calc_model;
    CalcController controller_calc(&calc_model);
    CalcView view(&controller_calc);

    view.show();

    return app.exec();
}
