#include "view.h"
#include "ui_view.h"

view::view(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::view) {
  ui->setupUi(this);

  credit_ = new credit();
  connect(credit_, &credit::firstWindow, this, &view::show);

//  thirdWindow = new DepositWindow();
//  connect(thirdWindow, &DepositWindow::firstWindow, this, &view::show);

  this->setFixedSize(480, 380);

  QScreen *screen = QGuiApplication::primaryScreen();
  QRect screenGeometry = screen->geometry();
  int x = (screenGeometry.width() - 480) / 2;
  int y = (screenGeometry.height() - 380) / 2;
  move(x, y);

  connect(ui->lnFunc, SIGNAL(clicked()), this, SLOT(FuncClicked()));
  connect(ui->logFunc, SIGNAL(clicked()), this, SLOT(FuncClicked()));
  connect(ui->absFunc, SIGNAL(clicked()), this, SLOT(FuncClicked()));
  connect(ui->cosFunc, SIGNAL(clicked()), this, SLOT(FuncClicked()));
  connect(ui->sinFunc, SIGNAL(clicked()), this, SLOT(FuncClicked()));
  connect(ui->tanFunc, SIGNAL(clicked()), this, SLOT(FuncClicked()));
  connect(ui->acosFunc, SIGNAL(clicked()), this, SLOT(FuncClicked()));
  connect(ui->asinFunc, SIGNAL(clicked()), this, SLOT(FuncClicked()));
  connect(ui->atanFunc, SIGNAL(clicked()), this, SLOT(FuncClicked()));
  connect(ui->sqrtFunc, SIGNAL(clicked()), this, SLOT(FuncClicked()));
  connect(ui->xSym, SIGNAL(clicked()), this, SLOT(SymbolsClicked()));
  connect(ui->num_0, SIGNAL(clicked()), this, SLOT(SymbolsClicked()));
  connect(ui->num_1, SIGNAL(clicked()), this, SLOT(SymbolsClicked()));
  connect(ui->num_2, SIGNAL(clicked()), this, SLOT(SymbolsClicked()));
  connect(ui->num_3, SIGNAL(clicked()), this, SLOT(SymbolsClicked()));
  connect(ui->num_4, SIGNAL(clicked()), this, SLOT(SymbolsClicked()));
  connect(ui->num_5, SIGNAL(clicked()), this, SLOT(SymbolsClicked()));
  connect(ui->num_6, SIGNAL(clicked()), this, SLOT(SymbolsClicked()));
  connect(ui->num_7, SIGNAL(clicked()), this, SLOT(SymbolsClicked()));
  connect(ui->num_8, SIGNAL(clicked()), this, SLOT(SymbolsClicked()));
  connect(ui->num_9, SIGNAL(clicked()), this, SLOT(SymbolsClicked()));
  connect(ui->num_pi, SIGNAL(clicked()), this, SLOT(SymbolsClicked()));
  connect(ui->addFunc, SIGNAL(clicked()), this, SLOT(OperatorsClicked()));
  connect(ui->mulFunc, SIGNAL(clicked()), this, SLOT(OperatorsClicked()));
  connect(ui->divFunc, SIGNAL(clicked()), this, SLOT(OperatorsClicked()));
  connect(ui->powFunc, SIGNAL(clicked()), this, SLOT(OperatorsClicked()));
  connect(ui->modFunc, SIGNAL(clicked()), this, SLOT(OperatorsClicked()));
  connect(ui->leftBracket, SIGNAL(clicked()), this, SLOT(BracketsClicked()));
  connect(ui->rightBracket, SIGNAL(clicked()), this, SLOT(BracketsClicked()));
}

view::~view() { delete ui; }

void view::on_credCalc_clicked() {
  credit_->show();
  this->close();
}

//void view::on_deposCalc_clicked() {
//  thirdWindow->show();
//  this->close();
//}

void view::GetInfo() {
  button_ = (QPushButton *)sender();
  str_ = ui->input->text().toStdString();
  size_ = str_.size();
  if (size_ >= 255) {
    ui->input->clear();
    ui->output->clear();
    ui->output->setText("ERROR: Too many elements!");
  }
}

void view::OperatorsClicked() {
    GetInfo();
    bool is_operator_ = false;
    if (size_ && str_.back() != '(' && str_.back() != '.') {
        if ((str_.back() == '-' && str_[str_.size() - 2] != '(') || str_.back() != '-') {
            for (int i = 0; i < 6; i++) {
                if (str_.back() == operators[i]) {
                    if (str_.back() != '-' || str_[str_.size() - 2] != '(') {
                        is_operator_ = true;
                        break;
                    }
                }
            }
            if (is_operator_) {
                on_delElem_clicked();
            }
            if (size_ < 255) {
              ui->input->setText(ui->input->text() + button_->text());
              is_dot_ = false;
            }
        }
    }
}

void view::SymbolsClicked() {
    GetInfo();
    if (str_.back() == 'x' || str_.back() == ')' || str_.back() == 'i') {
        ui->input->setText(ui->input->text() + "*");
    }
    if (button_->text() == "Pi" && str_.back() != '.') {
        if (str_.back() >= '0' && str_.back() <= '9') {
            ui->input->setText(ui->input->text() + "*");
        }
        ui->input->setText(ui->input->text() + button_->text());
        is_dot_ = false;
    } else if (button_->text() == 'x' && str_.back() != '.') {
        if (str_.back() >= '0' && str_.back() <= '9') {
            ui->input->setText(ui->input->text() + "*");
        }
        ui->input->setText(ui->input->text() + "x");
        is_dot_ = false;
    } else if (button_->text() >= '0' && button_->text() <= '9') {
        ui->input->setText(ui->input->text() + button_->text());
    }
}

void view::FuncClicked() {
  GetInfo();
  if (size_ < 255 && str_.back() != '.') {
    if ((str_.back() >= '0' && str_.back() <= '9') || str_.back() == ')' || str_.back() == 'i') {
      ui->input->setText(ui->input->text() + "*");
    }
    ui->input->setText(ui->input->text() + button_->text() + "(");
    is_dot_ = false;
  }
}

void view::BracketsClicked() {
  GetInfo();
  int l_brackets_ = 0, r_brackets_ = 0;
  bool can_do_ = true;
  if (str_.back() != '.') {
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
        if ((str_.back() >= '0' && str_.back() <= '9') || str_.back() == 'x' ||
            str_.back() == ')') {
          ui->input->setText(ui->input->text() + "*");
        }
        ui->input->setText(ui->input->text() + "(");
        is_dot_ = false;
      }
      if (button_->text() == ')' &&
          r_brackets_ < l_brackets_) {
        for (int i = 0; i < 6; i++) {
          if (str_.back() == operators[i]) {
            can_do_ = false;
          }
        }
        if (can_do_) {
          ui->input->setText(ui->input->text() + ")");
          is_dot_ = false;
        }
      }
    }
  }
}

void view::on_subFunc_clicked() {
  GetInfo();
  if (size_ < 255 && str_.back() != '.') {
    if (size_ == 0) {
      ui->input->setText(ui->input->text() + "(");
    } else {
      for (int i = 0; i < 6; i++) {
        if (str_.back() == operators[i]) {
          ui->input->setText(ui->input->text() + "(");
          break;
        }
      }
    }
    ui->input->setText(ui->input->text() + "-");
    is_dot_ = false;
  }
}

void view::on_dotSym_clicked() {
  GetInfo();
  for (int i = str_.size() - 1; str_[i] >= '0' && str_[i] <= '9'; i--) {
    if (str_[i - 1] == '.') {
      is_dot_ = true;
    }
  }
  if (size_ < 255 && str_.back() != '.' && !is_dot_) {
    if (str_.back() < '0' || str_.back() > '9') {
      if (str_.back() == ')' || str_.back() == 'i' || str_.back() == 'x') {
        ui->input->setText(ui->input->text() + "*");
      }
      ui->input->setText(ui->input->text() + "0");
    }
    ui->input->setText(ui->input->text() + ".");
    is_dot_ = true;
  }
}

void view::on_delElem_clicked() {
  GetInfo();
  if (str_.back() == '.') is_dot_ = false;
  if (size_ != 0) {
    char m_five = str_[str_.size() - 5];
    char m_four = str_[str_.size() - 4];
    char m_three = str_[str_.size() - 3];
    char m_two = str_[str_.size() - 2];
    QString text = ui->input->text();
    if (str_.back() == '(' && (m_five == 'a' || m_five == 's'))
        text.chop(5);
    else if (str_.back() == '(' && m_five != 'a' && (m_four == 'c' || m_four == 's' || m_four == 't' || m_four == 'a' || m_four == 'l'))
        text.chop(4);
    else if ((str_.back() == '(' && m_three == 'l') || (str_.back() == 'd' && m_three == 'm'))
        text.chop(3);
    else if (str_.back() == 'i' && m_two == 'P')
        text.chop(2);
    else
        text.chop(1);
    ui->input->setText(text);
  }
}

void view::on_delAll_clicked() {
  is_dot_ = false;
  ui->input->clear();
  ui->output->clear();
}

void view::CheckFields() {
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

void view::on_resultFunc_clicked() {
    ui->output->clear();
    str_ = ui->input->text().toStdString();
    if (calc_.IsCorrect(str_) && str_.size()) {
        if (!calc_.IsGraph(str_)) {
            double result_ = calc_.Calculator(str_ + "=");
            if (!calc_.IsError()) {
                ui->output->clear();
                int count_ = calc_.IsInteger(result_) ? 0 : 7;
                ui->output->setText(QString::number(result_, 'f', count_));
            } else {
                ui->output->setText("ERROR: Incorrect data!");
            }
        } else {
            if (!graph_open_) {
                int xPos = this->geometry().x();
                int yPos = this->geometry().y();
                this->setFixedSize(960, 380);
                ui->showGraph->setText("<");
                setGeometry(xPos, yPos, width() + 480, height());
                graph_open_ = true;
            }
            PrintGraph();
        }
    } else if (!calc_.IsCorrect(str_) && str_.size()) {
        ui->output->setText("ERROR: Incorrect data!");
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

void view::PrintGraph() {
    CheckFields();
    ui->output->setText("GRAPH");
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

void view::on_rad_clicked() {
    ui->rad->setStyleSheet("background-color: rgb(255, 160, 122); color: black; border: 1px solid gray;");
    ui->deg->setStyleSheet("background-color: rgb(255, 219, 139); color: black; border: 1px solid gray;");
    calc_.SetRad(true);
    on_resultFunc_clicked();
}

void view::on_deg_clicked() {
    ui->deg->setStyleSheet("background-color: rgb(255, 160, 122); color: black; border: 1px solid gray;");
    ui->rad->setStyleSheet("background-color: rgb(255, 219, 139); color: black; border: 1px solid gray;");
    calc_.SetRad(false);
    on_resultFunc_clicked();
}
