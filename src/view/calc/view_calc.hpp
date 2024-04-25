#ifndef SMARTCALC_VIEW_CALC_CALC_HPP
#define SMARTCALC_VIEW_CALC_CALC_HPP

#include <QMainWindow>

#include <stack>
#include <memory>

#include "controller_calc.hpp"

QT_BEGIN_NAMESPACE
namespace Ui {
class CalcView;
}
QT_END_NAMESPACE

class CalcView : public QMainWindow {
    Q_OBJECT

public:
    CalcView(CalcController* controller, QWidget *parent = nullptr);
    ~CalcView();

private:
    void PrintGraph();
    void BtnRadClicked();
    void BtnDegClicked();
    void BtnDelClicked();
    void BtnGraphClicked();
    void BtnDelAllClicked();
    void BtnResultClicked();
    void BtnShowGraphClicked();
    void NumsAndFuncsClicked();

private:
    CalcController* controller_;
    std::unique_ptr<Ui::CalcView> ui_;
    std::stack<std::uint8_t> token_sizes_;
};

#endif // SMARTCALC_VIEW_CALC_CALC_HPP
