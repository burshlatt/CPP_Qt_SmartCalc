#ifndef SMARTCALC_VIEW_CALC_CALC_HPP
#define SMARTCALC_VIEW_CALC_CALC_HPP

#include <QMainWindow>

#include <optional>
#include <memory>
#include <stack>

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
    void btnRadClicked();
    void btnDegClicked();
    void btnDelClicked();
    void btnNumsClicked();
    void btnDelAllClicked();
    void btnResultClicked();
    void btnShowGraphClicked();

private:
    std::stack<std::uint8_t> token_sizes_;

    std::unique_ptr<Ui::CalcView> ui_;
    CalcController* controller_;
};

#endif // SMARTCALC_VIEW_CALC_CALC_HPP
