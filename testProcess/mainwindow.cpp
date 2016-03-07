#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <windows.h>
#include <qdebug.h>
#include <QMessageBox>
#include "commonfunc.h"
#pragma comment(lib,"user32.lib")

const std::wstring dirPath(L"d:\\Programming\\cpp\\qt\\LabsQt\\testProcess\\release\\");

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    fileMapLastTask = nullptr;
    ui->setupUi(this);
    ui->label->setText(QString("Сообщение не получено!"));
    ui->WriteMapFile->setEnabled(false);
    ui->CloseMapFile->setEnabled(false);
}

bool MainWindow::nativeEvent(const QByteArray &eventType, void *message, long *result)
{
    UNREFERENCED_PARAMETER(eventType);
    MSG* myMessage = static_cast<MSG*>(message);
    static UINT messageHandle           = RegisterWindowMessage(L"TestMessage");
    static UINT createFileMapping       = RegisterWindowMessage(L"CreateFileMapping");
    static UINT closeFileMapping        = RegisterWindowMessage(L"CloseFileMapping");
    static UINT writeMessageToMapFile   = RegisterWindowMessage(L"WriteMessageToFileMap");
    if( myMessage->message == messageHandle )
    {
        ui->label->setText(QString("Сообщение получено!"));
        *result = 0;
        return true;
    }
    else if( myMessage->message == createFileMapping )
    {
        if( file.getPointerToData() == NULL )
        {
            on_pushButton_clicked();
        }
        *result = 0;
        return true;
    }
    else if( myMessage->message == closeFileMapping )
    {
        ui->WriteMapFile->setEnabled(false);
        ui->CloseMapFile->setEnabled(false);
        *result = 0;
        return true;
    }
    else if( myMessage->message == writeMessageToMapFile )
    {
        QString textFromEdit(static_cast<char*>(file.getPointerToData()));
        ui->lineEdit_2->setText(textFromEdit);
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
    delete fileMapLastTask;
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

void MainWindow::on_pushButton_clicked()
{
    using namespace Utils;
    if( file.CreateMyFileMapping(L"MemoryMapping", 0, 300) )
    {
        if( file.CreateMyMapViewOfFole() )
        {
            ui->WriteMapFile->setEnabled(true);
            ui->CloseMapFile->setEnabled(true);
            Utils::SendMessageAllWindows(L"MainWindow", L"CreateFileMapping");
        }
    }
}

void MainWindow::on_CloseMapFile_clicked()
{
    file.CloseFileMap();
    ui->WriteMapFile->setEnabled(false);
    ui->CloseMapFile->setEnabled(false);
    Utils::SendMessageAllWindows(L"MainWindow", L"CloseFileMapping");
}

void MainWindow::on_WriteMapFile_clicked()
{
    QString text(static_cast<char*>(file.getPointerToData()));
    ui->label_2->setText(text);
}

void MainWindow::on_pushButton_2_clicked()
{
    Utils::MyFile file(dirPath + L"testFile.txt");
    if( file.CreateMyFile() )
    {
        fileMapLastTask = new Utils::FileMapping(file);
        if( fileMapLastTask->CreateMyFileMapping(L"mapFile2") )
        {
            if( fileMapLastTask->CreateMyMapViewOfFole() )
            {
                LPVOID someData = fileMapLastTask->getPointerToData();
                QString text(QString::fromStdString((char*)someData));
                ui->textEdit->setText(text);
            }
        }
    }
}
