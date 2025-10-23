#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

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

private slots:
    void BtnNumClicked();

    void on_BtnPoint_clicked();

    void on_BtnDelete_clicked();

    void on_BtnC_clicked();

    void on_BtnChangeAM_clicked();

    void on_BtnPercentage_clicked();

    void on_BtnCountdown_clicked();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
