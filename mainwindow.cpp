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
    // 清除当前正在输入的操作数（保留之前的运算状态，如已输入的运算符和上一个操作数）
    operand.clear();
    // 更新显示区域为空（表示当前无输入）
    ui->display->setText(operand);
}



void MainWindow::on_BtnSquare_clicked()
{
    // 若当前无输入，不执行操作
    if (operand.isEmpty()) {
        return;
    }

    // 将当前输入的字符串转为数字
    bool ok;
    double num = operand.toDouble(&ok);

    // 转换成功则计算平方，否则显示错误
    if (ok) {
        double result = num * num;  // 计算平方

        // // 处理显示格式：若为整数则不带小数位，否则正常显示
        // if (result == result.toLongLong()) {
        //     operand = QString::number(result.toLongLong());
        // } else {
        //     operand = QString::number(result);
        // }

        operand = QString::number(result);

        // 更新显示
        ui->display->setText(operand);
    } else {
        // 输入无效时显示错误（例如输入非数字内容）
        ui->display->setText("错误");
        operand.clear();  // 清空当前输入，等待重新输入
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
        double result = sqrt(num);  // 调用数学库的开平方函数

        // // 处理显示格式：整数结果不带小数位，否则正常显示
        // if (result == result.toLongLong()) {
        //     operand = QString::number(result.toLongLong());
        // } else {
        //     operand = QString::number(result);
        // }

        operand = QString::number(result);

        // 更新显示
        ui->display->setText(operand);
    } else {
        // 输入无效（非数字）或负数开根号，显示错误
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
        // ui->statusbar->showMessage("calculation is in progress");
    }
    else {
        result = operands.front().toDouble();
        operands.pop_front();
        // ui->statusbar->showMessage(QString("operands is %1,opcodes is %2").arg(operands.size()).arg(opcodes.size()));
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

