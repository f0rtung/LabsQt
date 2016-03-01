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

Process::Process(const std::wstring &exeName, LPSTARTUPINFO lpsi) : Process(exeName, L"", lpsi)
{

}

Process::~Process()
{
    CloseAllHandles();
}

BOOL Process::Create()
{
    std::wstring runCMD = exe + L" " + commandLine;
    if( CreateProcess(NULL, &runCMD[0], 0, 0, FALSE, 0, NULL, NULL, &si, &pi) )
    {
        qDebug() << "Procces was created, name " << processName << ", id " << QString::number(pi.dwProcessId);
        return TRUE;
    }
    else
    {
        qDebug() << "Cant create proccess! " << GetLastError();
        return FALSE;
    }
}

void Process::CloseAllHandles()
{
    if(pi.hProcess)
    {
        if(!CloseHandle(pi.hProcess))
        {
            qDebug() << "Error close handle, idProcess: " << pi.dwProcessId;
            qDebug() << "Last error: " << GetLastError();
        }
        else
        {
            qDebug() << "Process was closed, name " << processName << ", id " << QString::number(pi.dwProcessId);
            pi.hProcess = 0;
        }
    }
    if(pi.hThread)
    {
        if(!CloseHandle(pi.hThread))
        {
            qDebug() << "Error close handle, idThread: " << pi.dwThreadId;
            qDebug() << "Last error: " << GetLastError();
        }
        else
        {
            qDebug() << "Thread was closed, name " << processName << ", id " << QString::number(pi.dwThreadId);
            pi.hThread = 0;
        }
    }
}

BOOL Process::CreateAndCloseAllHandels()
{
    bool result = Create();
    if( result )
    {
        CloseAllHandles();
    }
    return result;
}

BOOL Process::IsSteelActive()
{
    DWORD exitCode = STILL_ACTIVE;
    if( !GetExitCodeProcess(pi.hProcess, &exitCode) )
    {
        qDebug() << L"Cant get exitCode" << GetLastError();
        return FALSE;
    }
    return exitCode == STILL_ACTIVE;
}

BOOL Process::TerminateMe(UINT uExitCode)
{
    if( TerminateProcess(pi.hProcess, uExitCode) )
    {
        qDebug() << processName << " was terminate with exit code " << uExitCode;
        return TRUE;
    }
    else
    {
        qDebug() << "Cant terminate process!";
        return FALSE;
    }
}

HANDLE Process::getProcessHandle()
{
    return pi.hProcess;
}

} //namespace

