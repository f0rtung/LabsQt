#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "commonfunc.h"
#include <QDebug>
#include <vector>
#include <QMessageBox>
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

void MainWindow::on_RunNotepad_clicked()
{
    Utils::Process proc(L"Calc");
    if( proc.Create() )
    {

    }
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
            vecHandel.push_back(proc.getProcessHandle());
        }
    }
    DWORD resultOfWaiting = 0;
    while( true )
    {
        resultOfWaiting = MsgWaitForMultipleObjects(  vecHandel.size(),
                                                      vecHandel.data(),
                                                      false,
                                                      INFINITE,
                                                      QS_ALLEVENTS );
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
        while( PeekMessage(&m, 0, 0, 0, PM_REMOVE) ) {
            DispatchMessage(&m);
        }
    }
    QString stillActivProcessName;
    for( Utils::Process& proc : vecProc )
    {
        DWORD exitCode;
        if(GetExitCodeProcess(proc.getProcessHandle(), &exitCode) )
        {
            if( STILL_ACTIVE == exitCode )
            {
                if( TerminateProcess(proc.getProcessHandle(), -1) )
                {
                    qDebug() << proc.getProcessName() << " was terminate with exit code -1";
                }
                else
                {
                    qDebug() << "Cant terminate process!";
                }
            }
            else
            {
                stillActivProcessName = proc.getProcessName();
            }
        }
        else
        {
            qDebug() << "Cant get exit code!" << GetLastError();
        }
    }
    if( stillActivProcessName.size() != 0 )
    {
        QMessageBox::information(this, stillActivProcessName, stillActivProcessName + " was closed by user.");
    }
}
