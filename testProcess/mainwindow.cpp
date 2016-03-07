#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <windows.h>
#include <qdebug.h>
#include <QMessageBox>
#include "commonfunc.h"
#pragma comment(lib,"user32.lib")

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->label->setText(QString("Сообщение не получено!"));
}

bool MainWindow::nativeEvent(const QByteArray &eventType, void *message, long *result)
{
    UNREFERENCED_PARAMETER(eventType);
    MSG* myMessage = static_cast<MSG*>(message);
    static UINT messageHandle = RegisterWindowMessage(L"TestMessage");
    if( myMessage->message == messageHandle )
    {
        ui->label->setText(QString("Сообщение получено!"));
        *result = 0;
        return true;
    }
    else if( myMessage->message == WM_COPYDATA )
    {
        COPYDATASTRUCT* pds = reinterpret_cast<COPYDATASTRUCT*>(myMessage->lParam);
        if( pds->dwData == 33 )
        {
            QString text = QString::fromStdString(reinterpret_cast<char*>(pds->lpData));
            ui->label_2->setText(text);
            *result = 0;
        }
        return true;
    }
    return false;
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushWriteTextToFille_clicked()
{
    HANDLE hFile = GetStdHandle(STD_OUTPUT_HANDLE);
    if( INVALID_HANDLE_VALUE == hFile )
    {
        QMessageBox:: information(0, "INVALID_HANDLE_VALUE", QString::number(GetLastError()), 0 );
        return;
    }
    Utils::MyFile file(hFile);
    if( file.WriteText(L"Text from childe process!\n") )
    {
        file.CloseFileHandle();
    }
    else
    {
        QMessageBox:: information(0, QString::number(GetLastError()), QString::number(GetLastError()), 0 );
    }
}
