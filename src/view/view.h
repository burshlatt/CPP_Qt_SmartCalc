#ifndef VIEW_H
#define VIEW_H

#include <QMainWindow>
#include "creditwindow.h"
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
        void print_graph();
        void check_fields();
        void func_clicked();
        void symbols_clicked();
        void brackets_clicked();
        void operators_clicked();
        void on_dotSym_clicked();
        void on_delAll_clicked();
        void on_subFunc_clicked();
        void on_delElem_clicked();
        void on_credCalc_clicked();
//        void on_deposCalc_clicked();
        void on_showGraph_clicked();
        void on_resultFunc_clicked();

        void on_rad_clicked();

        void on_deg_clicked();

private:
        Ui::view *ui;
        s21::controller calc_;
        CreditWindow *secondWindow;
//        DepositWindow *thirdWindow;

        std::string str_;
        QPushButton *button_;
        std::vector<std::string> output;

        bool is_dot_ = false;
        bool graph_open_ = false;

        size_t size_ = 0;

        char last_symbol_ = str_.back();
        char operators[6] = {'-', '+', '*', '/', '^', 'd'};
};

#endif // VIEW_H
