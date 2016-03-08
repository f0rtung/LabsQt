#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "commonfunc.h"
#include "libs.h"
#include <QString>
#include <QDebug>


#pragma comment(lib,"user32.lib")

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButtonRunCalc_clicked()
{
    Utils::Process proc(L"Calc");
    for( size_t i = 0; i < 10; ++i )
    {
        proc.CreateAndCloseAllHandels();
    }
}

void MainWindow::on_pushButtonCloseAllCalc_clicked()
{
    MinimizeAllWindowsWithName(QString("Калькулятор"));
}

void MainWindow::on_pushButtonMinAllWindow_clicked()
{
    MaximizeAllWindowsWithName(QString("Калькулятор"));
}

void MainWindow::on_pushButtonCloseAllCalc_2_clicked()
{
    CloseAllWindowsWithName(QString("Калькулятор"));
}
