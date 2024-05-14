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
}

CreditView::~CreditView() {}

void CreditView::BtnResultClicked() {
    this->setFixedSize(960, 480);
}
