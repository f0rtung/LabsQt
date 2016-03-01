#ifndef COMMONFUNC
#define COMMONFUNC

#include <Windows.h>
#include <string>
#include <QString>

namespace Utils {
    class Process{
        const std::wstring exe;
        const std::wstring commandLine;
        const QString processName;
        STARTUPINFO si;
        PROCESS_INFORMATION pi;
    public:
        Process(const std::wstring& exeName, const std::wstring& comLine, LPSTARTUPINFO lpsi);
        Process(const std::wstring& exeName);
        ~Process();
        bool Create();
        HANDLE getProcessHandle();
        QString getProcessName() const { return processName; }
    };
}
#endif // COMMONFUNC

