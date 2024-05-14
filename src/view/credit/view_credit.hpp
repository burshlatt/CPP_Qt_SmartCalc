#ifndef SMARTCALC_VIEW_CREDIT_VIEW_CREDIT_HPP
#define SMARTCALC_VIEW_CREDIT_VIEW_CREDIT_HPP

#include <QMainWindow>
#include <QScreen>

#include <memory>

#include "controller_credit.hpp"

QT_BEGIN_NAMESPACE
namespace Ui {
class CreditView;
}
QT_END_NAMESPACE

class CreditView : public QMainWindow {
    Q_OBJECT

public:
    CreditView(CreditController* controller, QWidget* parent = nullptr);
    ~CreditView();

private:
    void BtnResultClicked();

private:
    CreditController* controller_;
    std::unique_ptr<Ui::CreditView> ui_;
};

#endif // SMARTCALC_VIEW_CREDIT_VIEW_CREDIT_HPP
