#ifndef SMARTCALC_VIEW_CREDIT_VIEW_CREDIT_HPP
#define SMARTCALC_VIEW_CREDIT_VIEW_CREDIT_HPP

#include <QLabel>
#include <QGridLayout>
#include <QMainWindow>

#include <memory>
#include <vector>

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
    void FillPaymentsField(const CreditController::Info& info, int term);

private:
    CreditController* controller_;
    std::unique_ptr<Ui::CreditView> ui_;
    std::unique_ptr<QWidget> scroll_widget_;
    std::unique_ptr<QGridLayout> grid_layout_;
    std::vector<std::unique_ptr<QLabel>> labels_vec_;
};

#endif // SMARTCALC_VIEW_CREDIT_VIEW_CREDIT_HPP
