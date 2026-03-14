#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <cmath>
#include <QRegularExpression>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QList<QPushButton*> opButtons = {ui->btn_plus, ui->btn_minus, ui->btn_umn,
                                      ui->btn_dil, ui->btn_procent, ui->btn_pow};
    for(auto btn : opButtons) btn->setCheckable(true);

    connect(ui->btn_0, &QPushButton::clicked, this, &MainWindow::digit_pressed);
    connect(ui->btn_1, &QPushButton::clicked, this, &MainWindow::digit_pressed);
    connect(ui->btn_2, &QPushButton::clicked, this, &MainWindow::digit_pressed);
    connect(ui->btn_3, &QPushButton::clicked, this, &MainWindow::digit_pressed);
    connect(ui->btn_4, &QPushButton::clicked, this, &MainWindow::digit_pressed);
    connect(ui->btn_5, &QPushButton::clicked, this, &MainWindow::digit_pressed);
    connect(ui->btn_6, &QPushButton::clicked, this, &MainWindow::digit_pressed);
    connect(ui->btn_7, &QPushButton::clicked, this, &MainWindow::digit_pressed);
    connect(ui->btn_8, &QPushButton::clicked, this, &MainWindow::digit_pressed);
    connect(ui->btn_9, &QPushButton::clicked, this, &MainWindow::digit_pressed);

    connect(ui->btn_coma, &QPushButton::clicked, this, &MainWindow::coma_pressed);

    connect(ui->btn_plus, &QPushButton::clicked, this, &MainWindow::operation_pressed);
    connect(ui->btn_umn, &QPushButton::clicked, this, &MainWindow::operation_pressed);
    connect(ui->btn_dil, &QPushButton::clicked, this, &MainWindow::operation_pressed);
    connect(ui->btn_procent, &QPushButton::clicked, this, &MainWindow::operation_pressed);
    connect(ui->btn_pow, &QPushButton::clicked, this, &MainWindow::operation_pressed);


    connect(ui->btn_minus, &QPushButton::clicked, this, &MainWindow::minus_pressed);
}

MainWindow::~MainWindow() { delete ui; }

void MainWindow::digit_pressed() {
    QPushButton * button = (QPushButton*)sender();
    if (ui->display->text() == "0") {
        ui->display->setText(button->text());
    } else {
        ui->display->setText(ui->display->text() + button->text());
    }
}

void MainWindow::minus_pressed() {
    QString text = ui->display->text();

    if (text == "0" || text.isEmpty()) {
        ui->display->setText("-");
        return;
    }

    if (text.endsWith("-")) {
        return;
    }

    if (QString("+*/%^").contains(text.right(1))) {
        ui->display->setText(text + "-");
        return;
    }

    operation_pressed();
}

void MainWindow::coma_pressed() {
    QString text = ui->display->text();
    int lastOp = text.lastIndexOf(QRegularExpression("[\\+\\*/%\\^]"));
    int lastMinus = text.lastIndexOf('-');
    if (lastMinus > 0 && !QString("+-*/%^").contains(text.at(lastMinus-1))) {
        lastOp = qMax(lastOp, lastMinus);
    }

    QString currentPart = (lastOp == -1) ? text : text.mid(lastOp + 1);

    if (!currentPart.contains('.')) {
        if (currentPart.isEmpty() || currentPart == "-") {
            ui->display->setText(text + "0.");
        } else {
            ui->display->setText(text + ".");
        }
    }
}

void MainWindow::operation_pressed() {
    QPushButton * button = (QPushButton*)sender();
    QString text = ui->display->text();

    if (text.isEmpty() || text == "-") return;

    firstNum = text.toDouble();
    currentOp = button->text();

    ui->display->setText(text + currentOp);

    QList<QPushButton*> opButtons = {ui->btn_plus, ui->btn_minus, ui->btn_umn,
                                      ui->btn_dil, ui->btn_procent, ui->btn_pow};
    for(auto btn : opButtons) btn->setChecked(false);
    button->setChecked(true);
}

void MainWindow::on_btn_equal_clicked() {
    QString displayVal = ui->display->text();

    if (currentOp.isEmpty()) return;

    int opPos = displayVal.indexOf(currentOp, 1);

    if (opPos == -1) return;

    QString secondNumStr = displayVal.mid(opPos + 1);

    if (secondNumStr.isEmpty() || secondNumStr == "-") return;

    double secondNum = secondNumStr.toDouble();
    double result = 0;

    if (currentOp == "+") result = firstNum + secondNum;
    else if (currentOp == "-") result = firstNum - secondNum;
    else if (currentOp == "*") result = firstNum * secondNum;
    else if (currentOp == "/") {
        if (secondNum == 0) {
            ui->display->setText("Error");
            currentOp = "";
            return;
        }
        result = firstNum / secondNum;
    }
    else if (currentOp == "%") result = fmod(firstNum, secondNum);
    else if (currentOp == "^") result = std::pow(firstNum, secondNum);

    ui->display->setText(QString::number(result, 'g', 15));

    currentOp = "";
    QList<QPushButton*> opButtons = {ui->btn_plus, ui->btn_minus, ui->btn_umn,
                                      ui->btn_dil, ui->btn_procent, ui->btn_pow};
    for(auto btn : opButtons) btn->setChecked(false);
}

void MainWindow::on_btn_clear_clicked() {
    ui->display->setText("0");
    firstNum = 0;
    ui->btn_plus->setChecked(false);
    ui->btn_minus->setChecked(false);
    ui->btn_umn->setChecked(false);
    ui->btn_dil->setChecked(false);
    ui->btn_procent->setChecked(false);
    ui->btn_pow->setChecked(false);
}
