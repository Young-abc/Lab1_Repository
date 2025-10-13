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
    QString str = ui->display->text();
    str += qobject_cast<QPushButton *>(sender())->text();
    ui->display->setText(str);
    // ui->statusbar->showMessage(qobject_cast<QPushButton *>(sender())->text()+"button0 clicked");
}

void MainWindow::on_BtnPoint_clicked()
{
    QString str = ui->display->text();
    if(!str.contains("."))
        str += qobject_cast<QPushButton *>(sender())->text();
    ui->display->setText(str);
}


void MainWindow::on_BtnDelete_clicked()
{
    QString str = ui->display->text();
    str = str.left(str.length()-1);
    ui->display->setText(str);

}

