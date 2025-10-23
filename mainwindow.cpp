#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    connect(ui->BtnNum0,SIGNAL(clicked()),this,SLOT(BtnNumClicked()));
    connect(ui->BtnNum1,SIGNAL(clicked()),this,SLOT(BtnNumClicked()));
    connect(ui->BtnNum2,SIGNAL(clicked()),this,SLOT(BtnNumClicked()));
    connect(ui->BtnNum3,SIGNAL(clicked()),this,SLOT(BtnNumClicked()));
    connect(ui->BtnNum4,SIGNAL(clicked()),this,SLOT(BtnNumClicked()));
    connect(ui->BtnNum5,SIGNAL(clicked()),this,SLOT(BtnNumClicked()));
    connect(ui->BtnNum6,SIGNAL(clicked()),this,SLOT(BtnNumClicked()));
    connect(ui->BtnNum7,SIGNAL(clicked()),this,SLOT(BtnNumClicked()));
    connect(ui->BtnNum8,SIGNAL(clicked()),this,SLOT(BtnNumClicked()));
    connect(ui->BtnNum9,SIGNAL(clicked()),this,SLOT(BtnNumClicked()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::BtnNumClicked()
{
    QString digit = qobject_cast<QPushButton *>(sender())->text();

    if(digit == "0" && operand == "0")
        digit = "";

    if(digit != "0" && operand == "0")
        operand = "";
    operand += digit;
    ui->display->setText(operand);
}

void MainWindow::on_BtnPoint_clicked()
{
    QString digit = qobject_cast<QPushButton *>(sender())->text();
    if(!operand.contains(".")){
        if(ui->display->text().length() == 0 && digit == ".")
            operand = '0';
        operand += digit;
    }
    ui->display->setText(operand);
}


void MainWindow::on_BtnDelete_clicked()
{
    operand = operand.left(operand.length()-1);
    ui->display->setText(operand);

}


void MainWindow::on_BtnC_clicked()
{
    operand.clear();
    ui->display->setText(operand);
}


void MainWindow::on_BtnChangeAM_clicked()
{
    if (operand.isEmpty() || operand == '0') return;

    if (operand.startsWith("-")) {
        operand.remove(0, 1);  // 移除负号
    } else {
        operand.prepend("-");  // 添加负号
    }
    ui->display->setText(operand);
}


void MainWindow::on_BtnPercentage_clicked()
{
    if (operand.isEmpty() || operand == '0') return;

    double num = operand.toDouble();
    num /= 100;  // 转为百分比
    operand = QString::number(num);
    ui->display->setText(operand);
}


void MainWindow::on_BtnCountdown_clicked()
{
    if (operand.isEmpty() || operand == '0') return;

    double num = operand.toDouble();
    num = 1/num;
    operand = QString::number(num);
    ui->display->setText(operand);
}

