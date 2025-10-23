#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QKeyEvent>
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
    connect(ui->BtnAdd,SIGNAL(clicked()),this,SLOT(binaryOperatorClicked()));
    connect(ui->BtnMinus,SIGNAL(clicked()),this,SLOT(binaryOperatorClicked()));
    connect(ui->BtnMultiplication,SIGNAL(clicked()),this,SLOT(binaryOperatorClicked()));
    connect(ui->BtnDivision,SIGNAL(clicked()),this,SLOT(binaryOperatorClicked()));
}

MainWindow::~MainWindow()
{
    delete ui;
}


//数字点击
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


//小数点按钮
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



//删除按钮
void MainWindow::on_BtnDelete_clicked()
{
    operand = operand.left(operand.length()-1);
    ui->display->setText(operand);

}


//清空按钮C
void MainWindow::on_BtnC_clicked()
{
    operand.clear();
    ui->display->setText(operand);
    while(operands.size()!=0){
        operands.pop_back();
    }
    while(opcodes.size()!=0){
        opcodes.pop_back();
    }
}



//改变符号按钮
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


//百分号
void MainWindow::on_BtnPercentage_clicked()
{
    if (operand.isEmpty() || operand == '0') return;

    double num = operand.toDouble();
    num /= 100;  // 转为百分比
    operand = QString::number(num);
    ui->display->setText(operand);
}



//倒数
void MainWindow::on_BtnCountdown_clicked()
{
    if (operand.isEmpty() || operand == '0') return;

    double num = operand.toDouble();
    num = 1/num;
    operand = QString::number(num);
    ui->display->setText(operand);
}

//CE清除按钮
void MainWindow::on_BtnCE_clicked()
{
    operand.clear();
    ui->display->setText(operand);
}



void MainWindow::on_BtnSquare_clicked()
{
    // 若当前无输入，不执行操作
    if (operand.isEmpty()) {
        return;
    }

    bool ok;
    double num = operand.toDouble(&ok);

    if (ok) {
        double result = num * num;  // 计算平方

        operand = QString::number(result);

        // 更新显示
        ui->display->setText(operand);
    } else {
        ui->display->setText("错误");
        operand.clear();
    }
}


void MainWindow::on_BtnSquareRoot_clicked()
{
    // 若当前无输入，不执行操作
    if (operand.isEmpty()) {
        return;
    }

    // 将当前输入的字符串转为数字
    bool ok;
    double num = operand.toDouble(&ok);

    // 转换成功且数字非负时计算平方根，否则显示错误
    if (ok && num >= 0) {
        double result = sqrt(num);

        operand = QString::number(result);

        // 更新显示
        ui->display->setText(operand);
    } else {
        ui->display->setText("错误");
        operand.clear();  // 清空当前输入，等待重新输入
    }
}

QString MainWindow::calculation(bool *ok)
{
    double result = 0;

    if(operands.size() == 2 &&opcodes.size() > 0){

        double operand1 = operands.front().toDouble();
        operands.pop_front();
        double operand2 = operands.front().toDouble();
        operands.pop_front();

        //取操作符
        QString op = opcodes.front();
        opcodes.pop_front();

        if(op == "+"){
            result = operand1 + operand2;
        }
        else if(op == "-"){
            result = operand1 - operand2;
        }
        else if(op == "×"){
            result = operand1 * operand2;
        }
        else if(op == "÷"){
            result = operand1 / operand2;
        }
        else;
    }
    else {
        result = operands.front().toDouble();
        operands.pop_front();
    }
    return QString::number(result);
}

//运算符号
void MainWindow::binaryOperatorClicked()
{
    // ui->statusbar->showMessage("last operand "+operand);
    QString opcode = qobject_cast<QPushButton *>(sender())->text();

    //把运算符放入运算符堆栈
    opcodes.push_back(opcode);

    if(operand != ""){

        //把操作数放入操作数堆栈
        operands.push_back(operand);
        operand = "";

    }

    QString result = calculation();

    operands.push_front(result);
    ui->display->setText(result);
}


//等于号
void MainWindow::on_BtnEquals_clicked()
{
    if(operand != ""){
        operands.push_back(operand);
        operand = "";
    }

    QString result = calculation();
    operands.push_front(result);
    ui->display->setText(result);
}

void MainWindow::keyPressEvent(QKeyEvent *event)
{
    if (event->key() >= Qt::Key_0 && event->key() <= Qt::Key_9) {
        // 模拟数字按钮点击
        QString num = event->text();
        if (num == "0") ui->BtnNum0->animateClick();
        else if (num == "1") ui->BtnNum1->animateClick();
        else if (num == "2") ui->BtnNum2->animateClick();
        else if (num == "3") ui->BtnNum3->animateClick();
        else if (num == "4") ui->BtnNum4->animateClick();
        else if (num == "5") ui->BtnNum5->animateClick();
        else if (num == "6") ui->BtnNum6->animateClick();
        else if (num == "7") ui->BtnNum7->animateClick();
        else if (num == "8") ui->BtnNum8->animateClick();
        else if (num == "9") ui->BtnNum9->animateClick();
    }
    else if (event->key() == Qt::Key_Period) { // 小数点
        ui->BtnPoint->animateClick();
    }
    // 运算符处理
    else if (event->key() == Qt::Key_Plus) { // +
        ui->BtnAdd->animateClick();
    }
    else if (event->key() == Qt::Key_Minus) { // -
        ui->BtnMinus->animateClick();
    }
    else if (event->key() == Qt::Key_Asterisk) { // *
        ui->BtnMultiplication->animateClick();
    }
    else if (event->key() == Qt::Key_Slash) { // /
        ui->BtnDivision->animateClick();
    }
    else if (event->key() == Qt::Key_Percent) { // %
        ui->BtnPercentage->animateClick();
    }
    else if (event->key() == Qt::Key_Return) { // =
        ui->BtnEquals->animateClick();
    }
    else if (event->key() == Qt::Key_Backspace) { // 删除
        ui->BtnDelete->animateClick();
    }
    else;
}

