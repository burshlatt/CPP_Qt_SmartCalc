#ifndef SMARTCALC_VIEW_CALC_VIEW_CALC_HPP
#define SMARTCALC_VIEW_CALC_VIEW_CALC_HPP

#include <QMainWindow>

#include <stack>
#include <memory>

#include "controller_calc.hpp"
#include "view_credit.hpp"

QT_BEGIN_NAMESPACE
namespace Ui {
class CalcView;
}
QT_END_NAMESPACE

class CalcView : public QMainWindow {
    Q_OBJECT

public:
    CalcView(CalcController* controller, CreditView* credit, QWidget* parent = nullptr);
    ~CalcView();

private:
    void PrintGraph();
    void BtnRadClicked();
    void BtnDegClicked();
    void BtnDelClicked();
    void BtnGraphClicked();
    void BtnDelAllClicked();
    void BtnResultClicked();
    void BtnOpenInfoClicked();
    void BtnShowGraphClicked();
    void NumsAndFuncsClicked();
    void BtnShowCreditClicked();

    void SetCenter();
    void ConnectButtons();

private:
    CalcController* controller_;
    std::unique_ptr<Ui::CalcView> ui_;
    std::stack<std::uint8_t> token_sizes_;

    CreditView* credit_view_;
};

#endif // SMARTCALC_VIEW_CALC_VIEW_CALC_HPP
