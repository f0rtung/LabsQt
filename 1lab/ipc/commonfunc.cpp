#include "commonfunc.h"
#include <Windows.h>
#include <QDebug>

namespace Utils {

Process::Process(const std::wstring &exeName, const std::wstring &comLine, LPSTARTUPINFO lpsi)
                : exe(exeName), commandLine(comLine), processName(QString::fromStdWString(exe))
{
    if( NULL == lpsi)
    {
        ZeroMemory(&si, sizeof(si));
        si.cb = sizeof(si);
    }
    else
    {
        si = *lpsi;
    }
    ZeroMemory(&pi, sizeof(pi));
}

Process::Process(const std::wstring &exeName) : Process(exeName, L"", NULL)
{

}

Process::~Process()
{
    if ( CloseHandle(pi.hThread) )
    {
        qDebug() << "Thread was closed, name " << processName << ", id " << QString::number(pi.dwThreadId);
    }
    else if( pi.hThread != 0 )
    {
        qDebug() << "Cant close handle " << GetLastError();
    }
    if ( CloseHandle(pi.hProcess) )
    {
        qDebug() << "Process was closed, name " << processName << ", id " << QString::number(pi.dwProcessId);
    }
    else if( pi.hProcess != 0 )
    {
        qDebug() << "Cant close handle " << GetLastError();
    }
}

bool Process::Create()
{
    std::wstring runCMD = exe + L" " + commandLine;
    if( CreateProcess(NULL, &runCMD[0], 0, 0, FALSE, 0, NULL, NULL, &si, &pi) )
    {
        qDebug() << "Procces was created, name " << processName << ", id " << QString::number(pi.dwProcessId);
        return true;
    }
    else
    {
        qDebug() << "Cant create proccess! " << GetLastError();
        return false;
    }
}

HANDLE Process::getProcessHandle()
{
    return pi.hProcess;
}

} //namespace

