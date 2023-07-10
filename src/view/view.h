#ifndef VIEW_H
#define VIEW_H

#include "credit.h"
#include "deposit.h"
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
        void GetInfo() noexcept;
        void PrintGraph() noexcept;
        void CheckFields() noexcept;
        void FuncClicked() noexcept;
        void on_rad_clicked() noexcept;
        void on_deg_clicked() noexcept;
        void SymbolsClicked() noexcept;
        void BracketsClicked() noexcept;
        void OperatorsClicked() noexcept;
        void on_dotSym_clicked() noexcept;
        void on_delAll_clicked() noexcept;
        void on_subFunc_clicked() noexcept;
        void on_delElem_clicked() noexcept;
        void on_credCalc_clicked() noexcept;
        void on_deposCalc_clicked() noexcept;
        void on_showGraph_clicked() noexcept;
        void on_resultFunc_clicked() noexcept;

private:
        Ui::view *ui;
        credit *credit_;
        deposit *deposit_;

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
