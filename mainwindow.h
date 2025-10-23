#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <Qstack>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    QString operand;
    QString opcode;
    QStack<QString> operands;
    QStack<QString> opcodes;

    QString calculation(bool *ok=NULL);

private slots:
    void binaryOperatorClicked();

    void BtnNumClicked();

    void on_BtnPoint_clicked();

    void on_BtnDelete_clicked();

    void on_BtnC_clicked();

    void on_BtnChangeAM_clicked();

    void on_BtnPercentage_clicked();

    void on_BtnCountdown_clicked();

    void on_BtnCE_clicked();

    void on_BtnSquare_clicked();

    void on_BtnSquareRoot_clicked();

    void on_BtnEquals_clicked();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
