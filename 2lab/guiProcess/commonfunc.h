#ifndef COMMONFUNC
#define COMMONFUNC

#include <Windows.h>
#include <string>
#include <QString>
#include <memory>

namespace Utils {
    class Process{
        const std::wstring exe;
        const std::wstring commandLine;
        const QString processName;
        STARTUPINFO si;
        PROCESS_INFORMATION pi;
    public:
        Process(const std::wstring& exeName, const std::wstring& comLine, LPSTARTUPINFO lpsi);
        Process(const std::wstring& exeName, LPSTARTUPINFO lpsi);
        Process(const std::wstring& exeName);
        ~Process();
        BOOL Create();
        void CloseAllHandles();
        BOOL CloseThreadHandle();
        BOOL CloseProcessHandle();
        BOOL CreateAndCloseAllHandels();
        BOOL IsSteelActive();
        BOOL TerminateMe(UINT uExitCode);
        HANDLE getProcessHandle();
        QString getProcessName() const { return processName; }
    };

    class MyFile
    {
        SECURITY_ATTRIBUTES sa;
        std::wstring pathToFile;
        HANDLE fileHandle;
    public:
        MyFile();
        MyFile(const std::wstring& filePath);
        MyFile(const std::wstring &filePath, LPSECURITY_ATTRIBUTES lpsa);
        MyFile(HANDLE hFile);
        MyFile(const MyFile& file);
        MyFile& operator=(const MyFile& file);
        ~MyFile();
        BOOL CreateMyFile();
        HANDLE getFileHandle();
        BOOL CloseFileHandle();
        BOOL WriteText(const std::wstring& someText);
    };

    class FileMapping
    {
    private:
        MyFile* m_file;
        HANDLE fileMapping;
        LPVOID fileData;
    public:
        FileMapping(const MyFile& file);
        FileMapping(std::nullptr_t prt);
        FileMapping();
        ~FileMapping();
        VOID CloseFileMap();
        BOOL CreateMyFileMapping(const std::wstring& lpName);
        BOOL CreateMyFileMapping(const std::wstring& lpName, DWORD dwMaximumSizeHigh, DWORD dwMaximumSizeLow);
        BOOL CreateMyMapViewOfFole();
        LPVOID getPointerToData();
    };

    VOID SendMessageAllWindows(const std::wstring& windowName, const std::wstring& messageName);
}
#endif // COMMONFUNC

