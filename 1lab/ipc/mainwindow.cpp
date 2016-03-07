#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "commonfunc.h"
#include <QDebug>
#include <vector>
#include <QMessageBox>

#pragma comment(lib,"user32.lib")

const std::wstring dirPath(L"d:\\Programming\\cpp\\qt\\LabsQt\\testProcess\\release\\");

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->pushButtonSendMessage->setEnabled(false);
    ui->lineEdit->setEnabled(false);
    ui->WriteMapFile->setEnabled(false);
    ui->CloseMapFile->setEnabled(false);
}

MainWindow::~MainWindow()
{
    delete fileMapLastTask;
    delete ui;
}

void MainWindow::on_RunNotepad_clicked()
{
    Utils::Process proc(L"Calc");
    proc.CreateAndCloseAllHandels();
}

void MainWindow::on_runThreeProc_clicked()
{
    std::vector<Utils::Process> vecProc;
    std::vector<HANDLE> vecHandel;
    vecProc.emplace_back(Utils::Process(L"Calc"));
    vecProc.emplace_back(Utils::Process(L"Notepad"));
    vecProc.emplace_back(Utils::Process(L"cmd"));
    for( Utils::Process& proc : vecProc )
    {
        if(proc.Create())
        {
            proc.CloseThreadHandle();
            vecHandel.push_back(proc.getProcessHandle());
        }
    }
    DWORD resultOfWaiting = 0;
    while( TRUE )
    {
        resultOfWaiting = MsgWaitForMultipleObjects(  vecHandel.size(),
                                                      vecHandel.data(),
                                                      FALSE,
                                                      INFINITE,
                                                      static_cast<DWORD>(QS_ALLEVENTS) );
        if( resultOfWaiting >= WAIT_OBJECT_0 &&
            resultOfWaiting < WAIT_OBJECT_0 + vecHandel.size() )
        {
            qDebug() << "Some one process was ended!";
            break;
        }
        if( resultOfWaiting == WAIT_FAILED )
        {
            qDebug() << "Error waiting!";
        }
        MSG m;
        while( PeekMessage(&m, 0, 0, 0, PM_REMOVE) )
        {
            DispatchMessage(&m);
        }
    }
    QString stillActivProcessName;
    for( Utils::Process& proc : vecProc )
    {
        if( proc.IsSteelActive() )
        {
            proc.TerminateMe(-1);
        }
        else
        {
            stillActivProcessName = proc.getProcessName();
        }
        proc.CloseProcessHandle();
    }
    if( stillActivProcessName.size() != 0 )
    {
        QMessageBox::information(this, stillActivProcessName, stillActivProcessName + " was closed by user.");
    }
}

void MainWindow::on_pushButtonStartupInfo_clicked()
{
    STARTUPINFO si;
    ZeroMemory(&si, sizeof(si));
    si.cb           = sizeof(si);
    si.dwFlags      = STARTF_USESHOWWINDOW;
    si.wShowWindow  = SW_SHOWMAXIMIZED;
    Utils::Process proc(L"Notepad", &si);
    if( !proc.CreateAndCloseAllHandels() )
    {
        qDebug() << GetLastError();
    }
}

void MainWindow::on_startMyProcess_clicked()
{
    qDebug() << "on_startMyProcess_clicked() start.";

    SECURITY_ATTRIBUTES sa;
    ZeroMemory(&sa, sizeof(sa));
    sa.nLength = sizeof(sa);
    sa.bInheritHandle = TRUE;
    Utils::MyFile outFile(dirPath + L"outFile.txt", &sa);

    if( outFile.CreateMyFile() )
    {
        outFile.WriteText(L"First text from parent process!\n");
        STARTUPINFO si;
        ZeroMemory(&si, sizeof(si));
        si.cb = sizeof(si);
        si.dwFlags = STARTF_USESTDHANDLES;
        si.hStdOutput = outFile.getFileHandle();
        Utils::Process testProc(dirPath + L"testProcess.exe", &si);
        if( testProc.Create() )
        {
            testProc.CloseThreadHandle();
            WaitForSingleObject(testProc.getProcessHandle(), INFINITE);
            testProc.CloseProcessHandle();
        }
        else
        {
            qDebug() << GetLastError();
        }
        outFile.WriteText(L"Second text from parent process!\n");
    }
    outFile.CloseFileHandle();
    qDebug() << "on_startMyProcess_clicked() end.";
}

void MainWindow::on_RunProcess_clicked()
{
       Utils::Process proc(dirPath + L"testProcess.exe");
       if( proc.CreateAndCloseAllHandels() )
       {
            ui->pushButtonSendMessage->setEnabled(true);
            ui->lineEdit->setEnabled(true);
       }
       else
       {

       }
}

void MainWindow::on_pushButtonSendMessage_clicked()
{
    Utils::SendMessageAllWindows(L"TestProcess", L"TestMessage");
}

void MainWindow::on_lineEdit_textChanged(const QString &arg1)
{
    static HWND window = FindWindow(0, L"TestProcess");
    if( window )
    {
        std::string text(arg1.toStdString());
        COPYDATASTRUCT data;
        data.dwData = 33;
        data.cbData = static_cast<DWORD>(text.size() + 1);
        data.lpData = &text[0];
        qDebug() << "Send some message!";
        SendMessage(window,
                    WM_COPYDATA,
                    static_cast<WPARAM>(winId()),
                    reinterpret_cast<LPARAM>(&data));
    }
    else
    {
        qDebug() << "Cant send some message!";
    }
}

void MainWindow::on_pushButtonCreateFileMapping_clicked()
{
    Utils::MyFile file(dirPath + L"testFile.txt");
    if( file.CreateMyFile() )
    {
        Utils::FileMapping fileMapping(file);
        if( fileMapping.CreateMyFileMapping(L"mapFile") )
        {
            if( fileMapping.CreateMyMapViewOfFole() )
            {
                LPVOID someData = fileMapping.getPointerToData();
                QString text(QString::fromStdString((char*)someData));
                ui->textBrowser->setText(text);
            }
        }
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
            Utils::SendMessageAllWindows(L"TestProcess", L"CreateFileMapping");
        }
    }
}

void MainWindow::on_CloseMapFile_clicked()
{
    file.CloseFileMap();
    ui->WriteMapFile->setEnabled(false);
    ui->CloseMapFile->setEnabled(false);
    Utils::SendMessageAllWindows(L"TestProcess", L"CloseFileMapping");
}

void MainWindow::on_WriteMapFile_clicked()
{
    std::string textFromEdit = ui->lineEdit_2->text().toStdString();
    if( textFromEdit.empty() )
    {
        qDebug() << "LineEdit is Empty!";
        return;
    }
    for( size_t i = 0; i < textFromEdit.size(); i++ )
    {
        static_cast<char*>(file.getPointerToData())[i] = textFromEdit[i];
    }
    qDebug() << "Write seccess!";
    qDebug() << static_cast<char*>(file.getPointerToData());
    Utils::SendMessageAllWindows(L"TestProcess", L"WriteMessageToFileMap");
}

bool MainWindow::nativeEvent(const QByteArray &eventType, void *message, long *result)
{
    UNREFERENCED_PARAMETER(eventType);
    MSG* myMessage = static_cast<MSG*>(message);
    static UINT createFileMapping       = RegisterWindowMessage(L"CreateFileMapping");
    static UINT closeFileMapping        = RegisterWindowMessage(L"CloseFileMapping");
    static UINT writeMessageToMapFile   = RegisterWindowMessage(L"WriteMessageToFileMap");
    if( myMessage->message == createFileMapping )
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
    return false;
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

void MainWindow::on_textEdit_textChanged()
{
    std::string textFromEdit = ui->textEdit->toPlainText().toStdString();
    for( size_t i = 0; i < textFromEdit.size(); i++ )
    {
        static_cast<char*>(fileMapLastTask->getPointerToData())[i] = textFromEdit[i];
    }
    Utils::SendMessageAllWindows(L"testProcess", L"ChangeLastTaskEdit");
}
