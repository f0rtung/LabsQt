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
    if( CreateProcess(NULL, &runCMD[0], 0, 0, TRUE, 0, NULL, NULL, &si, &pi) )
    {
        qDebug() << "Procces was created, name " << processName << ", id " << QString::number(pi.dwProcessId);
        return TRUE;
    }
    else
    {
        qDebug() << "Cant create proccess! Error: " << GetLastError();
        return FALSE;
    }
}

void Process::CloseAllHandles()
{
    CloseProcessHandle();
    CloseThreadHandle();
}

BOOL Process::CloseThreadHandle()
{
    if(pi.hThread)
    {
        if (CloseHandle(pi.hThread) )
        {
            qDebug() << "Thread was closed, name " << processName << ", id " << QString::number(pi.dwThreadId);
            pi.hThread = 0;
            return TRUE;
        }
        else
        {
            qDebug() << "Error close handle, idThread: " << pi.dwThreadId;
            qDebug() << "Last error: " << GetLastError();
            return FALSE;
        }
    }
    return TRUE;
}

BOOL Process::CloseProcessHandle()
{
    if(pi.hProcess)
    {
        if(CloseHandle(pi.hProcess))
        {
            qDebug() << "Process was closed, name " << processName << ", id " << QString::number(pi.dwProcessId);
            pi.hProcess = 0;
            return TRUE;
        }
        else
        {
            qDebug() << "Error close handle, idProcess: " << pi.dwProcessId;
            qDebug() << "Last error: " << GetLastError();
            return FALSE;
        }
    }
    return TRUE;
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

MyFile::MyFile() : MyFile(L"", NULL)
{

}

MyFile::MyFile(const std::wstring &filePath) : MyFile(filePath, NULL)
{

}

MyFile::MyFile(const std::wstring &filePath, LPSECURITY_ATTRIBUTES lpsa)
{
    pathToFile = filePath;
    fileHandle = NULL;
    if( lpsa != NULL)
    {
        sa = *lpsa;
    }
    else
    {
        ZeroMemory(&sa, sizeof(sa));
        sa.nLength = sizeof(sa);
    }
}

MyFile::MyFile(HANDLE hFile)
{
    fileHandle = hFile;
}

MyFile::MyFile(const MyFile &file)
{
    if( !DuplicateHandle(GetCurrentProcess(),
                        file.fileHandle,
                        GetCurrentProcess(),
                        &this->fileHandle,
                        0,
                        TRUE,
                        DUPLICATE_SAME_ACCESS) )
    {
        this->fileHandle = NULL;
    }
    this->pathToFile    = file.pathToFile;
    this->sa            = file.sa;
}

MyFile &MyFile::operator=(const MyFile &file)
{
    if( !DuplicateHandle(GetCurrentProcess(),
                        file.fileHandle,
                        GetCurrentProcess(),
                        &this->fileHandle,
                        0,
                        TRUE,
                        DUPLICATE_SAME_ACCESS) )
    {
        this->fileHandle = NULL;
    }
    this->pathToFile    = file.pathToFile;
    this->sa            = file.sa;
    return *this;
}

MyFile::~MyFile()
{
    CloseFileHandle();
}

BOOL MyFile::CreateMyFile()
{
    fileHandle = CreateFile(pathToFile.c_str(),
                            GENERIC_READ | GENERIC_WRITE,
                            FILE_SHARE_READ | FILE_SHARE_WRITE,
                            &sa,
                            OPEN_ALWAYS,
                            FILE_ATTRIBUTE_NORMAL,
                            NULL);
    if ( INVALID_HANDLE_VALUE != fileHandle )
    {
        qDebug() << "Succsess creating file";
        return TRUE;
    }
    else
    {
        qDebug() << "Error creating file!" << GetLastError();
        fileHandle = NULL;
        return FALSE;
    }
}

HANDLE MyFile::getFileHandle()
{
    return fileHandle;
}

BOOL MyFile::CloseFileHandle()
{
    if( fileHandle )
    {
        if( !CloseHandle( fileHandle ) )
        {
            qDebug() << "Cant close file, path " + QString::fromStdWString(pathToFile);
            return FALSE;
        }
        qDebug() << "File was closed: " + QString::fromStdWString(pathToFile);
        fileHandle = NULL;
    }
    return TRUE;
}

BOOL MyFile::WriteText(const std::wstring &someText)
{
    if( fileHandle )
    {
        std::string text(someText.begin(), someText.end());
        DWORD numChars;
        if( WriteFile(fileHandle,
                      text.c_str(),
                      text.size(),
                      &numChars,
                      NULL) && numChars == text.size() )
        {
            qDebug() << "WriteText()" << "success!";
            return TRUE;
        }
        else
        {
            qDebug() << "WriteText()" << "error!";
        }
    }
    return FALSE;
}

FileMapping::FileMapping(const MyFile &file)
{
    m_file = new MyFile(file);
    fileMapping = NULL;
    fileData    = NULL;
}

FileMapping::FileMapping(std::nullptr_t prt)
{
    m_file      = prt;
    fileMapping = NULL;
    fileData    = NULL;
}

FileMapping::FileMapping() : FileMapping(nullptr)
{

}

FileMapping::~FileMapping()
{
    CloseFileMap();
    delete m_file;
}

void FileMapping::CloseFileMap()
{
    if( fileMapping )
    {
        if( fileData )
        {
            if( UnmapViewOfFile(fileData))
            {
                qDebug() << "Unmap file";
            }
            else
            {
                qDebug() << "Cant unmap file " << GetLastError();
            }
        }
        if( CloseHandle(fileMapping) )
        {
            qDebug() << "Close fileMap";
        }
        else
        {
            qDebug() << "Cant close fileMap";
        }
    }
}

BOOL FileMapping::CreateMyFileMapping(const std::wstring &lpName)
{
    return CreateMyFileMapping(lpName, 0, 0);
}

BOOL FileMapping::CreateMyFileMapping(const std::wstring& lpName, DWORD dwMaximumSizeHigh, DWORD dwMaximumSizeLow)
{
    fileMapping = CreateFileMapping(m_file == nullptr ? INVALID_HANDLE_VALUE : m_file->getFileHandle(),
                                    NULL,
                                    PAGE_READWRITE,
                                    dwMaximumSizeHigh,
                                    dwMaximumSizeLow,
                                    lpName.c_str());
    if( fileMapping != NULL )
    {
        qDebug() << "Create succsess!";
        return TRUE;
    }
    else
    {
        qDebug() << "Create error: " << GetLastError();
        return FALSE;
    }
}

BOOL FileMapping::CreateMyMapViewOfFole()
{
    fileData = MapViewOfFile(fileMapping,
                             FILE_MAP_ALL_ACCESS,
                             0,
                             0,
                             0);
    if( fileData )
    {
        return TRUE;
    }
    else
    {
        return FALSE;
    }

}

LPVOID FileMapping::getPointerToData()
{
    return fileData;
}

void SendMessageAllWindows(const std::wstring& windowName, const std::wstring& messageName)
{
    HWND window = FindWindow(0,windowName.c_str());
    UINT messageHandle = RegisterWindowMessage(messageName.c_str());
    if( PostMessage(window, messageHandle, 0, 0) )
    {

    }
    else
    {
        qDebug() << "Cant send some message!";
    }
}

} //namespace Utils

