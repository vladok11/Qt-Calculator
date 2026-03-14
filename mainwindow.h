#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void digit_pressed();
    void operation_pressed();
    void on_btn_clear_clicked();
    void on_btn_equal_clicked();
    void coma_pressed();
    void minus_pressed();
private:
    double firstNum;
    QString currentOp;
    bool userIsTypingSecondNumber = false;
    Ui::MainWindow *ui;
    QString pendingOperation;
};



#endif
