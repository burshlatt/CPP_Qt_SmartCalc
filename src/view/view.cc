#include "view.h"

#include "ui_view.h"

View::View(QWidget *parent) : QMainWindow(parent), ui_(new Ui::View) {
  ui_->setupUi(this);

  credit_ = new Credit();
  connect(credit_, &Credit::firstWindow, this, &View::show);

  deposit_ = new Deposit();
  connect(deposit_, &Deposit::firstWindow, this, &View::show);

  this->setFixedSize(480, 380);

  QScreen *screen = QGuiApplication::primaryScreen();
  QRect screenGeometry = screen->geometry();
  const int x = (screenGeometry.width() - 480) / 2;
  const int y = (screenGeometry.height() - 380) / 2;
  move(x, y);

  connect(ui_->lnFunc, SIGNAL(clicked()), this, SLOT(FuncClicked()));
  connect(ui_->logFunc, SIGNAL(clicked()), this, SLOT(FuncClicked()));
  connect(ui_->absFunc, SIGNAL(clicked()), this, SLOT(FuncClicked()));
  connect(ui_->cosFunc, SIGNAL(clicked()), this, SLOT(FuncClicked()));
  connect(ui_->sinFunc, SIGNAL(clicked()), this, SLOT(FuncClicked()));
  connect(ui_->tanFunc, SIGNAL(clicked()), this, SLOT(FuncClicked()));
  connect(ui_->acosFunc, SIGNAL(clicked()), this, SLOT(FuncClicked()));
  connect(ui_->asinFunc, SIGNAL(clicked()), this, SLOT(FuncClicked()));
  connect(ui_->atanFunc, SIGNAL(clicked()), this, SLOT(FuncClicked()));
  connect(ui_->sqrtFunc, SIGNAL(clicked()), this, SLOT(FuncClicked()));
  connect(ui_->xSym, SIGNAL(clicked()), this, SLOT(SymbolsClicked()));
  connect(ui_->num_0, SIGNAL(clicked()), this, SLOT(SymbolsClicked()));
  connect(ui_->num_1, SIGNAL(clicked()), this, SLOT(SymbolsClicked()));
  connect(ui_->num_2, SIGNAL(clicked()), this, SLOT(SymbolsClicked()));
  connect(ui_->num_3, SIGNAL(clicked()), this, SLOT(SymbolsClicked()));
  connect(ui_->num_4, SIGNAL(clicked()), this, SLOT(SymbolsClicked()));
  connect(ui_->num_5, SIGNAL(clicked()), this, SLOT(SymbolsClicked()));
  connect(ui_->num_6, SIGNAL(clicked()), this, SLOT(SymbolsClicked()));
  connect(ui_->num_7, SIGNAL(clicked()), this, SLOT(SymbolsClicked()));
  connect(ui_->num_8, SIGNAL(clicked()), this, SLOT(SymbolsClicked()));
  connect(ui_->num_9, SIGNAL(clicked()), this, SLOT(SymbolsClicked()));
  connect(ui_->num_pi, SIGNAL(clicked()), this, SLOT(SymbolsClicked()));
  connect(ui_->addFunc, SIGNAL(clicked()), this, SLOT(OperatorsClicked()));
  connect(ui_->mulFunc, SIGNAL(clicked()), this, SLOT(OperatorsClicked()));
  connect(ui_->divFunc, SIGNAL(clicked()), this, SLOT(OperatorsClicked()));
  connect(ui_->powFunc, SIGNAL(clicked()), this, SLOT(OperatorsClicked()));
  connect(ui_->modFunc, SIGNAL(clicked()), this, SLOT(OperatorsClicked()));
  connect(ui_->leftBracket, SIGNAL(clicked()), this, SLOT(BracketsClicked()));
  connect(ui_->rightBracket, SIGNAL(clicked()), this, SLOT(BracketsClicked()));
}

View::~View() { delete ui_; }

void View::on_credCalc_clicked() noexcept {
  credit_->show();
  this->close();
}

void View::on_deposCalc_clicked() noexcept {
  deposit_->show();
  this->close();
}

void View::GetInfo() noexcept {
  button_ = (QPushButton *)sender();
  str_ = ui_->input->text().toStdString();
  size_ = str_.size();
  if (size_ >= 255) {
    ui_->input->clear();
    ui_->output->clear();
    ui_->output->setText("ERROR: Too many elements!");
  }
}

void View::OperatorsClicked() noexcept {
  GetInfo();
  bool is_operator_ = false;
  if ((size_ && str_.back() != '(' && str_.back() != '.') &&
      ((str_.back() == '-' && str_[str_.size() - 2] != '(') ||
       str_.back() != '-')) {
    for (size_t i = 0; i < operators_.size(); i++) {
      if (str_.back() == operators_[i] &&
          (str_.back() != '-' || str_[str_.size() - 2] != '(')) {
        is_operator_ = true;
        break;
      }
    }
    if (is_operator_) {
      on_delElem_clicked();
    }
    if (size_ < 255) {
      ui_->input->setText(ui_->input->text() + button_->text());
      is_dot_ = false;
    }
  }
}

void View::SymbolsClicked() noexcept {
  GetInfo();
  if (str_.back() == 'x' || str_.back() == ')' || str_.back() == 'i') {
    ui_->input->setText(ui_->input->text() + "*");
  }
  if (button_->text() == "Pi" && str_.back() != '.') {
    if (str_.back() >= '0' && str_.back() <= '9') {
      ui_->input->setText(ui_->input->text() + "*");
    }
    ui_->input->setText(ui_->input->text() + button_->text());
    is_dot_ = false;
  } else if (button_->text() == 'x' && str_.back() != '.') {
    if (str_.back() >= '0' && str_.back() <= '9') {
      ui_->input->setText(ui_->input->text() + "*");
    }
    ui_->input->setText(ui_->input->text() + "x");
    is_dot_ = false;
  } else if (button_->text() >= '0' && button_->text() <= '9') {
    ui_->input->setText(ui_->input->text() + button_->text());
  }
}

void View::FuncClicked() noexcept {
  GetInfo();
  if (size_ < 255 && str_.back() != '.') {
    if ((str_.back() >= '0' && str_.back() <= '9') || str_.back() == ')' ||
        str_.back() == 'i') {
      ui_->input->setText(ui_->input->text() + "*");
    }
    ui_->input->setText(ui_->input->text() + button_->text() + "(");
    is_dot_ = false;
  }
}

void View::BracketsClicked() noexcept {
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
          ui_->input->setText(ui_->input->text() + "*");
        }
        ui_->input->setText(ui_->input->text() + "(");
        is_dot_ = false;
      }
      if (button_->text() == ')' && r_brackets_ < l_brackets_) {
        for (size_t i = 0; i < operators_.size(); i++) {
          if (str_.back() == operators_[i]) {
            can_do_ = false;
          }
        }
        if (can_do_) {
          ui_->input->setText(ui_->input->text() + ")");
          is_dot_ = false;
        }
      }
    }
  }
}

void View::on_subFunc_clicked() noexcept {
  GetInfo();
  if (size_ < 255 && str_.back() != '.') {
    if (size_ == 0) {
      ui_->input->setText(ui_->input->text() + "(");
    } else {
      for (size_t i = 0; i < operators_.size(); i++) {
        if (str_.back() == operators_[i] && str_.back() != '(') {
          ui_->input->setText(ui_->input->text() + "(");
          break;
        }
      }
    }
    ui_->input->setText(ui_->input->text() + "-");
    is_dot_ = false;
  }
}

void View::on_dotSym_clicked() noexcept {
  GetInfo();
  for (int i = str_.size() - 1; str_[i] >= '0' && str_[i] <= '9'; i--) {
    if (str_[i - 1] == '.') {
      is_dot_ = true;
    }
  }
  if (size_ < 255 && str_.back() != '.' && !is_dot_) {
    if (str_.back() < '0' || str_.back() > '9') {
      if (str_.back() == ')' || str_.back() == 'i' || str_.back() == 'x') {
        ui_->input->setText(ui_->input->text() + "*");
      }
      ui_->input->setText(ui_->input->text() + "0");
    }
    ui_->input->setText(ui_->input->text() + ".");
    is_dot_ = true;
  }
}

void View::on_delElem_clicked() noexcept {
  GetInfo();
  if (str_.back() == '.') is_dot_ = false;
  if (size_ != 0) {
    const char m_five = str_[str_.size() - 5];
    const char m_four = str_[str_.size() - 4];
    const char m_three = str_[str_.size() - 3];
    const char m_two = str_[str_.size() - 2];
    QString text = ui_->input->text();
    if (str_.back() == '(' && (m_five == 'a' || m_five == 's'))
      text.chop(5);
    else if (str_.back() == '(' && m_five != 'a' &&
             (m_four == 'c' || m_four == 's' || m_four == 't' ||
              m_four == 'a' || m_four == 'l'))
      text.chop(4);
    else if ((str_.back() == '(' && m_three == 'l') ||
             (str_.back() == 'd' && m_three == 'm'))
      text.chop(3);
    else if (str_.back() == 'i' && m_two == 'P')
      text.chop(2);
    else
      text.chop(1);
    ui_->input->setText(text);
  }
}

void View::on_delAll_clicked() noexcept {
  is_dot_ = false;
  ui_->input->clear();
  ui_->output->clear();
}

void View::CheckFields() noexcept {
  if (ui_->xMinCord->text().size() == 0) {
    ui_->xMinCord->setText("-5");
  } else if (ui_->xMinCord->text().toDouble() < -1000000) {
    ui_->xMinCord->setText("-1000000");
  }
  if (ui_->xMaxCord->text().size() == 0) {
    ui_->xMaxCord->setText("5");
  } else if (ui_->xMaxCord->text().toDouble() > 1000000) {
    ui_->xMaxCord->setText("1000000");
  }
  if (ui_->yMinCord->text().size() == 0) {
    ui_->yMinCord->setText("-5");
  } else if (ui_->yMinCord->text().toDouble() < -1000000) {
    ui_->yMinCord->setText("-1000000");
  }
  if (ui_->yMaxCord->text().size() == 0) {
    ui_->yMaxCord->setText("5");
  } else if (ui_->yMaxCord->text().toDouble() > 1000000) {
    ui_->yMaxCord->setText("1000000");
  }
  if (ui_->xStart->text().size() == 0) {
    ui_->xStart->setText("-200");
  } else if (ui_->xStart->text().toDouble() < -1000000) {
    ui_->xStart->setText("-1000000");
  }
  if (ui_->xEnd->text().size() == 0) {
    ui_->xEnd->setText("200");
  } else if (ui_->xEnd->text().toDouble() > 1000000) {
    ui_->xEnd->setText("1000000");
  }
}

void View::on_resultFunc_clicked() noexcept {
  ui_->output->clear();
  str_ = ui_->input->text().toStdString();
  if (calc_.IsCorrect(str_) && str_.size()) {
    if (!calc_.IsGraph(str_)) {
      QString result_ = calc_.Calculator(str_ + "=");
      if (!calc_.IsError()) {
        ui_->output->clear();
        ui_->output->setText(result_);
      } else {
        ui_->output->setText("ERROR: Incorrect data!");
      }
    } else {
      if (!graph_open_) {
        const int xPos = this->geometry().x();
        const int yPos = this->geometry().y();
        this->setFixedSize(960, 380);
        ui_->showGraph->setText("<");
        setGeometry(xPos, yPos, width() + 480, height());
        graph_open_ = true;
      }
      PrintGraph();
    }
  } else if (!calc_.IsCorrect(str_) && str_.size()) {
    ui_->output->setText("ERROR: Incorrect data!");
  }
}

void View::on_showGraph_clicked() noexcept {
  const int xPos = this->geometry().x();
  const int yPos = this->geometry().y();
  if (!graph_open_) {
    this->setFixedSize(960, 380);
    ui_->showGraph->setText("<");
    setGeometry(xPos, yPos, width() + 480, height());
    graph_open_ = true;
  } else {
    this->setFixedSize(480, 380);
    ui_->showGraph->setText(">");
    setGeometry(xPos, yPos, width() - 480, height());
    graph_open_ = false;
  }
}

void View::PrintGraph() noexcept {
  CheckFields();
  ui_->output->setText("GRAPH");
  ui_->Graph->clearGraphs();
  ui_->Graph->xAxis->setRange(ui_->xMinCord->text().toDouble(),
                              ui_->xMaxCord->text().toDouble());
  ui_->Graph->yAxis->setRange(ui_->yMinCord->text().toDouble(),
                              ui_->yMaxCord->text().toDouble());
  QVector<double> xCord, yCord;
  double X = ui_->xStart->text().toDouble();
  const double xEnd = ui_->xEnd->text().toDouble() + 0.1;
  calc_.GraphStart(str_ + "=");
  while (X <= xEnd) {
    xCord.push_back(X);
    yCord.push_back(calc_.Graph(X));
    X += 0.1;
  }
  calc_.GraphEnd();
  ui_->Graph->addGraph();
  ui_->Graph->graph(0)->addData(xCord, yCord);
  ui_->Graph->replot();
}

void View::on_rad_clicked() noexcept {
  ui_->rad->setStyleSheet(
      "background-color: rgb(255, 160, 122); color: black; border: 1px solid "
      "gray;");
  ui_->deg->setStyleSheet(
      "background-color: rgb(255, 219, 139); color: black; border: 1px solid "
      "gray;");
  calc_.set_rad(true);
  on_resultFunc_clicked();
}

void View::on_deg_clicked() noexcept {
  ui_->deg->setStyleSheet(
      "background-color: rgb(255, 160, 122); color: black; border: 1px solid "
      "gray;");
  ui_->rad->setStyleSheet(
      "background-color: rgb(255, 219, 139); color: black; border: 1px solid "
      "gray;");
  calc_.set_rad(false);
  on_resultFunc_clicked();
}
