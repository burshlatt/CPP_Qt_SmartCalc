#include "view.h"
#include "ui_view.h"

view::view(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::view) {
  ui->setupUi(this);

  secondWindow = new CreditWindow();
  connect(secondWindow, &CreditWindow::firstWindow, this, &view::show);

//  thirdWindow = new DepositWindow();
//  connect(thirdWindow, &DepositWindow::firstWindow, this, &view::show);

  this->setFixedSize(480, 380);

  QScreen *screen = QGuiApplication::primaryScreen();
  QRect screenGeometry = screen->geometry();
  int x = (screenGeometry.width() - 480) / 2;
  int y = (screenGeometry.height() - 380) / 2;
  move(x, y);

  connect(ui->lnFunc, SIGNAL(clicked()), this, SLOT(func_clicked()));
  connect(ui->logFunc, SIGNAL(clicked()), this, SLOT(func_clicked()));
  connect(ui->absFunc, SIGNAL(clicked()), this, SLOT(func_clicked()));
  connect(ui->cosFunc, SIGNAL(clicked()), this, SLOT(func_clicked()));
  connect(ui->sinFunc, SIGNAL(clicked()), this, SLOT(func_clicked()));
  connect(ui->tanFunc, SIGNAL(clicked()), this, SLOT(func_clicked()));
  connect(ui->acosFunc, SIGNAL(clicked()), this, SLOT(func_clicked()));
  connect(ui->asinFunc, SIGNAL(clicked()), this, SLOT(func_clicked()));
  connect(ui->atanFunc, SIGNAL(clicked()), this, SLOT(func_clicked()));
  connect(ui->sqrtFunc, SIGNAL(clicked()), this, SLOT(func_clicked()));
  connect(ui->xSym, SIGNAL(clicked()), this, SLOT(symbols_clicked()));
  connect(ui->num_0, SIGNAL(clicked()), this, SLOT(symbols_clicked()));
  connect(ui->num_1, SIGNAL(clicked()), this, SLOT(symbols_clicked()));
  connect(ui->num_2, SIGNAL(clicked()), this, SLOT(symbols_clicked()));
  connect(ui->num_3, SIGNAL(clicked()), this, SLOT(symbols_clicked()));
  connect(ui->num_4, SIGNAL(clicked()), this, SLOT(symbols_clicked()));
  connect(ui->num_5, SIGNAL(clicked()), this, SLOT(symbols_clicked()));
  connect(ui->num_6, SIGNAL(clicked()), this, SLOT(symbols_clicked()));
  connect(ui->num_7, SIGNAL(clicked()), this, SLOT(symbols_clicked()));
  connect(ui->num_8, SIGNAL(clicked()), this, SLOT(symbols_clicked()));
  connect(ui->num_9, SIGNAL(clicked()), this, SLOT(symbols_clicked()));
  connect(ui->num_pi, SIGNAL(clicked()), this, SLOT(symbols_clicked()));
  connect(ui->addFunc, SIGNAL(clicked()), this, SLOT(operators_clicked()));
  connect(ui->mulFunc, SIGNAL(clicked()), this, SLOT(operators_clicked()));
  connect(ui->divFunc, SIGNAL(clicked()), this, SLOT(operators_clicked()));
  connect(ui->powFunc, SIGNAL(clicked()), this, SLOT(operators_clicked()));
  connect(ui->modFunc, SIGNAL(clicked()), this, SLOT(operators_clicked()));
  connect(ui->leftBracket, SIGNAL(clicked()), this, SLOT(brackets_clicked()));
  connect(ui->rightBracket, SIGNAL(clicked()), this, SLOT(brackets_clicked()));
}

view::~view() { delete ui; }

void view::on_credCalc_clicked() {
  secondWindow->show();
  this->close();
}

//void view::on_deposCalc_clicked() {
//  thirdWindow->show();
//  this->close();
//}

void view::GetInfo() {
  if (is_result_) {
    ui->inputOutput->clear();
    is_result_ = false;
  }
  button_ = (QPushButton *)sender();
  str_ = ui->inputOutput->text().toStdString();
  last_symbol_ = str_.back();
  size_ = str_.size();
  if (size_ >= 255) {
    ui->inputOutput->clear();
    ui->inputOutput->setText(ui->inputOutput->text() + "ERROR: Too many elements!");
  }
}

void view::operators_clicked() {
    GetInfo();
    bool is_operator_ = false;
    if (size_ && last_symbol_ != '(' && last_symbol_ != '.') {
        for (int i = 0; i < 6; i++) {
            if (last_symbol_ == operators[i]) {
                if (last_symbol_ != '-' || str_[str_.size() - 2] != '(') {
                    is_operator_ = true;
                }
            }
        }
        if (is_operator_) {
            if (last_symbol_ == 'd') {
                on_delElem_clicked();
                on_delElem_clicked();
            }
            on_delElem_clicked();
        }
        if (size_ < 255) {
          ui->inputOutput->setText(ui->inputOutput->text() + button_->text());
          is_dot_ = false;
        }
    }
}

void view::symbols_clicked() {
    GetInfo();
    if (size_ < 255) {
        if (last_symbol_ == 'x' || last_symbol_ == ')' || last_symbol_ == 'i') {
            ui->inputOutput->setText(ui->inputOutput->text() + "*");
        }
        if (button_->text() == "Pi" && last_symbol_ != '.') {
            if (last_symbol_ >= '0' && last_symbol_ <= '9') {
                ui->inputOutput->setText(ui->inputOutput->text() + "*");
            }
            ui->inputOutput->setText(ui->inputOutput->text() + button_->text());
            is_dot_ = false;
        } else if (button_->text() == 'x' && last_symbol_ != '.') {
            if (last_symbol_ >= '0' && last_symbol_ <= '9') {
                ui->inputOutput->setText(ui->inputOutput->text() + "*");
            }
            ui->inputOutput->setText(ui->inputOutput->text() + "x");
            is_dot_ = false;
        } else if (button_->text() >= '0' && button_->text() <= '9') {
            ui->inputOutput->setText(ui->inputOutput->text() + button_->text());
        }
    }
}

void view::func_clicked() {
  GetInfo();
  if (size_ < 255 && last_symbol_ != '.') {
    if ((last_symbol_ >= '0' && last_symbol_ <= '9') || last_symbol_ == ')' || last_symbol_ == 'i') {
      ui->inputOutput->setText(ui->inputOutput->text() + "*");
    }
    ui->inputOutput->setText(ui->inputOutput->text() + button_->text() + "(");
    is_dot_ = false;
  }
}

void view::brackets_clicked() {
  GetInfo();
  l_brackets_ = 0;
  r_brackets_ = 0;
  bool can_do_ = true;
  if (last_symbol_ != '.') {
    for (size_t i = 0; i < size_; i++) {
      if (str_[i] == '(') {
        l_brackets_++;
      }
      if (str_[i] == ')') {
        r_brackets_++;
      }
    }
    if (size_ < 255) {
      if (button_->text() == '(') {
        if ((last_symbol_ >= '0' && last_symbol_ <= '9') || last_symbol_ == 'x' ||
            last_symbol_ == ')') {
          ui->inputOutput->setText(ui->inputOutput->text() + "*");
        }
        ui->inputOutput->setText(ui->inputOutput->text() + "(");
        is_dot_ = false;
      }
      if (button_->text() == ')' &&
          r_brackets_ < l_brackets_) {
        for (int i = 0; i < 6; i++) {
          if (last_symbol_ == operators[i]) {
            can_do_ = false;
          }
        }
        if (can_do_) {
          ui->inputOutput->setText(ui->inputOutput->text() + ")");
          is_dot_ = false;
        }
      }
    }
  }
}

void view::on_subFunc_clicked() {
  GetInfo();
  if (size_ < 255 && last_symbol_ != '.') {
    if (size_ == 0) {
      ui->inputOutput->setText(ui->inputOutput->text() + "(");
    } else {
      for (int i = 0; i < 6; i++) {
        if (last_symbol_ == operators[i]) {
          ui->inputOutput->setText(ui->inputOutput->text() + "(");
          break;
        }
      }
    }
    ui->inputOutput->setText(ui->inputOutput->text() + "-");
    is_dot_ = false;
  }
}

void view::on_dotSym_clicked() {
  GetInfo();
  if (size_ < 255 && last_symbol_ != '.' && !is_dot_) {
    if (last_symbol_ < '0' || last_symbol_ > '9') {
      if (last_symbol_ == ')') {
        ui->inputOutput->setText(ui->inputOutput->text() + "*");
      }
      ui->inputOutput->setText(ui->inputOutput->text() + "0");
    }
    ui->inputOutput->setText(ui->inputOutput->text() + ".");
    is_dot_ = true;
  }
}

void view::on_delElem_clicked() {
  GetInfo();
  if (last_symbol_ == '.') {
    is_dot_ = false;
  }
  if (size_ == 0) {
    ui->inputOutput->clear();
  } else {
    QString text = ui->inputOutput->text();
    text.chop(1);
    ui->inputOutput->setText(text);
  }
  GetInfo();
  for (int i = str_.size() - 1;
       str_[i] >= '0' && str_[i] <= '9'; i--) {
    if (str_[i - 1] == '.') {
      is_dot_ = true;
    }
  }
}

void view::on_delAll_clicked() {
  is_dot_ = false;
  ui->inputOutput->clear();
}

void view::check_fields() {
  if (ui->xValue->text().size() == 0) {
    ui->xValue->setText("0");
  }
  if (ui->xMinCord->text().size() == 0) {
    ui->xMinCord->setText("-5");
  } else if (ui->xMinCord->text().toDouble() < -1000000) {
    ui->xMinCord->setText("-1000000");
  }
  if (ui->xMaxCord->text().size() == 0) {
    ui->xMaxCord->setText("5");
  } else if (ui->xMaxCord->text().toDouble() > 1000000) {
    ui->xMaxCord->setText("1000000");
  }
  if (ui->yMinCord->text().size() == 0) {
    ui->yMinCord->setText("-5");
  } else if (ui->yMinCord->text().toDouble() < -1000000) {
    ui->yMinCord->setText("-1000000");
  }
  if (ui->yMaxCord->text().size() == 0) {
    ui->yMaxCord->setText("5");
  } else if (ui->yMaxCord->text().toDouble() > 1000000) {
    ui->yMaxCord->setText("1000000");
  }
  if (ui->xStart->text().size() == 0) {
    ui->xStart->setText("-200");
  } else if (ui->xStart->text().toDouble() < -1000000) {
    ui->xStart->setText("-1000000");
  }
  if (ui->xEnd->text().size() == 0) {
    ui->xEnd->setText("200");
  } else if (ui->xEnd->text().toDouble() > 1000000) {
    ui->xEnd->setText("1000000");
  }
}

void view::on_showGraph_clicked() {
  int xPos = this->geometry().x();
  int yPos = this->geometry().y();
  if (!graph_open_) {
    this->setFixedSize(960, 380);
    ui->showGraph->setText("<");
    setGeometry(xPos, yPos, width() + 480, height());
    graph_open_ = true;
  } else {
    this->setFixedSize(480, 380);
    ui->showGraph->setText(">");
    setGeometry(xPos, yPos, width() - 480, height());
    graph_open_ = false;
  }
}

void view::on_resultFunc_clicked() {
    check_fields();
    str_ = ui->inputOutput->text().toStdString();
    if (calc_.IsCorrect(str_) && str_.size()) {
        if (!calc_.IsGraph(str_)) {
            double result_ = calc_.Calculator(str_ + "=");
            if (!calc_.IsError()) {
                ui->inputOutput->clear();
                if (std::fabs(result_ - (int)result_) < std::numeric_limits<double>::epsilon()) {
                    ui->inputOutput->setText(ui->inputOutput->text() + QString::number(result_, 'f', 0));
                } else {
                    ui->inputOutput->setText(ui->inputOutput->text() + QString::number(result_, 'f', 7));
                }
            } else {
                ui->inputOutput->clear();
                ui->inputOutput->setText(ui->inputOutput->text() + "ERROR: Incorrect data!");
            }
            is_result_ = true;
        } else {
            if (!graph_open_) {
                int xPos = this->geometry().x();
                int yPos = this->geometry().y();
                this->setFixedSize(960, 380);
                ui->showGraph->setText("<");
                setGeometry(xPos, yPos, width() + 480, height());
                graph_open_ = true;
            }
            print_graph();
        }
    } else if (!calc_.IsCorrect(str_) && str_.size()) {
        is_result_ = true;
        ui->inputOutput->clear();
        ui->inputOutput->setText(ui->inputOutput->text() + "ERROR: Incorrect data!");
    }
}

void view::print_graph() {
    check_fields();
    ui->functionGraph->clearGraphs();
    ui->functionGraph->xAxis->setRange(ui->xMinCord->text().toDouble(), ui->xMaxCord->text().toDouble());
    ui->functionGraph->yAxis->setRange(ui->yMinCord->text().toDouble(), ui->yMaxCord->text().toDouble());
    QVector<double> xCord, yCord;
    double xBegin = ui->xStart->text().toDouble();
    double xEnd = ui->xEnd->text().toDouble() + 0.01;
    double X = xBegin;
    calc_.GraphStart(str_ + "=");
    while (X <= xEnd) {
        xCord.push_back(X);
        yCord.push_back(calc_.Graph(X));
        X += 0.01;
    }
    calc_.GraphEnd();
    ui->functionGraph->addGraph();
    ui->functionGraph->graph(0)->addData(xCord, yCord);
    ui->functionGraph->replot();
}
