#ifndef VIEW_H
#define VIEW_H

#include <QMainWindow>
#include "credit.h"
//#include "depositwindow.h"
#include "../controller/controller.h"

QT_BEGIN_NAMESPACE
namespace Ui {
    class view;
}
QT_END_NAMESPACE

class view : public QMainWindow {
  Q_OBJECT

    public:
        view(QWidget *parent = nullptr);
        ~view();

    private slots:
        void GetInfo();
        void PrintGraph();
        void CheckFields();
        void FuncClicked();
        void on_rad_clicked();
        void on_deg_clicked();
        void SymbolsClicked();
        void BracketsClicked();
        void OperatorsClicked();
        void on_dotSym_clicked();
        void on_delAll_clicked();
        void on_subFunc_clicked();
        void on_delElem_clicked();
        void on_credCalc_clicked();
//        void on_deposCalc_clicked();
        void on_showGraph_clicked();
        void on_resultFunc_clicked();

private:
        Ui::view *ui;
        credit *credit_;
//        DepositWindow *thirdWindow;
        std::string str_;
        QPushButton *button_;
        s21::controller calc_;
        std::vector<std::string> output;

        size_t size_ = 0;
        bool is_dot_ = false;
        bool graph_open_ = false;
        char operators[6] = {'-', '+', '*', '/', '^', 'd'};
};

#endif // VIEW_H
