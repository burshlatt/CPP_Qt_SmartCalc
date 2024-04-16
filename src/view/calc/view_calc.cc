#include <optional>

#include "view_calc.hpp"
#include "./ui_view_calc.h"

CalcView::CalcView(CalcController* controller, QWidget *parent) :
    QMainWindow(parent),
    ui_(std::make_unique<Ui::CalcView>()),
    controller_(controller)
{
    ui_->setupUi(this);
    this->setFixedSize(480, 380);

    QList<QPushButton*> buttons = {
        ui_->btnZero, ui_->btnOne,  ui_->btnTwo,   ui_->btnThree, ui_->btnFour,
        ui_->btnFive, ui_->btnSix,  ui_->btnSeven, ui_->btnEight, ui_->btnNine,
        ui_->btnX,    ui_->btnPi,   ui_->btnDot,   ui_->btnLB,    ui_->btnRB,
        ui_->btnCos,  ui_->btnAcos, ui_->btnSin,   ui_->btnAsin,  ui_->btnTan,
        ui_->btnAtan, ui_->btnAbs,  ui_->btnSqrt,  ui_->btnLog,   ui_->btnLn,
        ui_->btnPow,  ui_->btnMod,  ui_->btnMinus, ui_->btnPlus,  ui_->btnMul,
        ui_->btnDiv
    };

    for (auto button : buttons)
        connect(button, &QPushButton::clicked, this, &CalcView::NumsClicked);

    connect(ui_->btnRad, &QPushButton::clicked, this, &CalcView::btnRadClicked);
    connect(ui_->btnDeg, &QPushButton::clicked, this, &CalcView::btnDegClicked);
    connect(ui_->btnDel, &QPushButton::clicked, this, &CalcView::btnDelClicked);
    connect(ui_->btnDelAll, &QPushButton::clicked, this, &CalcView::btnDelAllClicked);
    connect(ui_->btnResult, &QPushButton::clicked, this, &CalcView::btnResultClicked);
    connect(ui_->btnShowGraph, &QPushButton::clicked, this, &CalcView::btnShowGraphClicked);
}

CalcView::~CalcView() {}

void CalcView::btnResultClicked() {
    std::string notation{ui_->leInput->text().toStdString()};
    std::optional<double> result{controller_->Calculate(notation)};

    if (result.has_value()) {
        ui_->leOutput->setText(QString::number(*result));
    } else {
        ui_->leOutput->setText(QString("ERROR: Icorrect data!"));
    }
}

void CalcView::NumsClicked() {
    QPushButton* button{static_cast<QPushButton*>(sender())};
    QString button_text{button->text()};
    QString current_text{ui_->leInput->text()};

    ui_->leInput->setText(current_text + button_text);
    token_sizes_.push(static_cast<std::uint8_t>(button_text.size()));
}

void CalcView::btnDelClicked() {
    if (!token_sizes_.empty()) {
        QString text{ui_->leInput->text()};

        text.chop(token_sizes_.top());
        ui_->leInput->setText(text);
        token_sizes_.pop();
    }
}

void CalcView::btnDelAllClicked() {
    ui_->leInput->clear();
    ui_->leOutput->clear();

    while(!token_sizes_.empty())
        token_sizes_.pop();
}

void CalcView::btnRadClicked() {
    ui_->btnRad->setStyleSheet(
        "background-color: rgb(255, 160, 122); "
        "color: black; "
        "border: 1px solid gray;"
        );

    ui_->btnDeg->setStyleSheet(
        "background-color: rgb(255, 219, 139); "
        "color: black; "
        "border: 1px solid gray;"
        );
}

void CalcView::btnDegClicked() {
    ui_->btnDeg->setStyleSheet(
        "background-color: rgb(255, 160, 122); "
        "color: black; "
        "border: 1px solid gray;"
    );

    ui_->btnRad->setStyleSheet(
        "background-color: rgb(255, 219, 139); "
        "color: black; "
        "border: 1px solid gray;"
    );
}

void CalcView::btnShowGraphClicked() {
    bool graph_is_open{ui_->btnShowGraph->text() != ">"};

    if (!graph_is_open) {
        this->setFixedSize(960, 380);
        ui_->btnShowGraph->setText("<");
    } else {
        this->setFixedSize(480, 380);
        ui_->btnShowGraph->setText(">");
    }
}

// void ViewCalculator::PrintGraph() noexcept {
//     OpenGraph();
//     if (!IsCorrectGraph()) {
//         QMessageBox msg_box_;
//         msg_box_.setText("Значения полей графика должны быть от -1000000 до 1000000");
//         msg_box_.exec();
//     } else {
//         ui_->output->setText("GRAPH");
//         ui_->Graph->clearGraphs();
//         ui_->Graph->xAxis->setRange(ui_->xMinCord->text().toDouble(), ui_->xMaxCord->text().toDouble());
//         ui_->Graph->yAxis->setRange(ui_->yMinCord->text().toDouble(), ui_->yMaxCord->text().toDouble());
//         QVector<double> x_cord_, y_cord_;
//         double x_ = ui_->xStart->text().toDouble();
//         const double x_end_ = ui_->xEnd->text().toDouble() + 0.1;
//         calc_.GraphStart(str_ + "=");
//         while (x_ <= x_end_) {
//             x_cord_.push_back(x_);
//             y_cord_.push_back(calc_.Graph(x_));
//             x_ += 0.1;
//         }
//         calc_.GraphEnd();
//         ui_->Graph->addGraph();
//         ui_->Graph->graph(0)->addData(x_cord_, y_cord_);
//         ui_->Graph->replot();
//     }
// }
