#include <QScreen>
#include <QDate>

#include "view_credit.hpp"
#include "./ui_view_credit.h"

CreditView::CreditView(CreditController* controller, QWidget *parent) :
    QMainWindow(parent),
    controller_(controller),
    ui_(std::make_unique<Ui::CreditView>())
{
    ui_->setupUi(this);

    this->setFixedSize(480, 325);

    QScreen* screen{QGuiApplication::primaryScreen()};
    QRect screenGeometry{screen->geometry()};
    const int x{(screenGeometry.width() - 480) / 2};
    const int y{(screenGeometry.height() - 330) / 2};

    move(x, y);

    connect(ui_->btnResult, &QPushButton::clicked, this, &CreditView::BtnResultClicked);

    scroll_widget_ = std::make_unique<QWidget>();
    ui_->saTable->setWidget(scroll_widget_.get());

    grid_layout_ = std::make_unique<QGridLayout>();
    scroll_widget_->setLayout(grid_layout_.get());
}

CreditView::~CreditView() {}

void CreditView::FillPaymentsField(const CreditController::Info& info) {
    labels_vec_.clear();

    int term{static_cast<int>(info.monthly_payments.size())};

    for (int i{}; i < term; ++i) {
        labels_vec_.push_back(std::make_unique<QLabel>());
        QLabel* id{labels_vec_.back().get()};

        labels_vec_.push_back(std::make_unique<QLabel>());
        QLabel* date{labels_vec_.back().get()};

        labels_vec_.push_back(std::make_unique<QLabel>());
        QLabel* sum{labels_vec_.back().get()};

        id->setFixedWidth(110);
        id->setFixedHeight(35);
        date->setFixedWidth(110);
        date->setFixedHeight(35);
        sum->setFixedWidth(110);
        sum->setFixedHeight(35);

        grid_layout_->addWidget(id, i, 0);
        grid_layout_->addWidget(date, i, 1);
        grid_layout_->addWidget(sum, i, 2);

        id->setText(QString::number(i + 1));
        date->setText(QDate::currentDate().addMonths(i).toString("dd.MM.yyyy"));
        sum->setText(QString::number(info.monthly_payments[i], 'f', 2));
    }
}

void CreditView::BtnResultClicked() {
    this->setFixedSize(960, 480);

    int term{ui_->leTerm->text().toInt()};
    double sum{ui_->leSum->text().toDouble()};
    double percent{ui_->lePercent->text().toDouble()};

    if (ui_->rbYear->isChecked()) {
        term *= 12;
    }

    CreditController::Info info;

    if (ui_->rbAnnu->isChecked()) {
        info = controller_->CalculateAnnuityCredit(sum, term, percent);
    } else {
        info = controller_->CalculateDifferentiatedCredit(sum, term, percent);
    }

    QString first_payment{QString::number(info.monthly_payments.front(), 'f', 2)};
    QString last_payment{QString::number(info.monthly_payments.back(), 'f', 2)};

    if (ui_->rbAnnu->isChecked()) {
        ui_->leMonthResult->setText(first_payment);
    } else {
        ui_->leMonthResult->setText(first_payment + "..." + last_payment);
    }

    ui_->leOverpay->setText(QString::number(info.overpayment, 'f', 2));
    ui_->leSumResult->setText(QString::number(info.total_payment, 'f', 2));

    FillPaymentsField(info);
}
