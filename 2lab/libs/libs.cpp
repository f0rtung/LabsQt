#include "libs.h"
#include <Windows.h>
#include <QDebug>

void MinimizeAllWindowsWithName(const QString& nameWindow)
{
    QString name(nameWindow);
    EnumWindows( MinimizeMyWindow, reinterpret_cast<LPARAM>(&name));
}

BOOL CALLBACK MinimizeMyWindow(HWND hwnd,  LPARAM lParam)
{
    static int count = 0;
    int nameLength = (int)SendMessage(hwnd, WM_GETTEXTLENGTH, 0, 0);
    if( nameLength )
    {
        wchar_t* nameWindow = new wchar_t[nameLength + 1];
        QString nameFindWindow = *(reinterpret_cast<QString*>(lParam));
        SendMessage(hwnd, WM_GETTEXT, nameLength + 1, reinterpret_cast<LPARAM>(nameWindow));
        QString nameWindowQString = QString::fromStdWString(nameWindow);
        if( nameWindowQString == nameFindWindow )
        {
            if( !CloseWindow(hwnd) )
            {
                qDebug() << "Cant minimize window, error " << GetLastError();
            }
            else
            {
                ++count;
            }
        }
        delete[] nameWindow;
    }
    return count == 10 ? FALSE : TRUE;
}

BOOL MaximizeMyWindow(HWND hwnd, LPARAM lParam)
{
    static int count = 0;
    int nameLength = (int)SendMessage(hwnd, WM_GETTEXTLENGTH, 0, 0);
    if( nameLength )
    {
        wchar_t* nameWindow = new wchar_t[nameLength + 1];
        QString nameFindWindow = *(reinterpret_cast<QString*>(lParam));
        SendMessage(hwnd, WM_GETTEXT, nameLength + 1, reinterpret_cast<LPARAM>(nameWindow));
        QString nameWindowQString = QString::fromStdWString(nameWindow);
        if( nameWindowQString == nameFindWindow )
        {
            if( !OpenIcon (hwnd) )
            {
                qDebug() << "Cant maximize window, error " << GetLastError();
            }
            else
            {
                count++;
            }
        }
        delete[] nameWindow;
    }
    return count == 10 ? FALSE : TRUE;
}

void MaximizeAllWindowsWithName(const QString &nameWindow)
{
    QString name(nameWindow);
    EnumWindows( MaximizeMyWindow, reinterpret_cast<LPARAM>(&name));
}

void CloseAllWindowsWithName(const QString &nameWindow)
{
    QString name(nameWindow);
    EnumWindows( CloseMyWindow, reinterpret_cast<LPARAM>(&name));
}

BOOL CloseMyWindow(HWND hwnd, LPARAM lParam)
{
    static int count = 0;
    int nameLength = (int)SendMessage(hwnd, WM_GETTEXTLENGTH, 0, 0);
    if( nameLength )
    {
        wchar_t* nameWindow = new wchar_t[nameLength + 1];
        QString nameFindWindow = *(reinterpret_cast<QString*>(lParam));
        SendMessage(hwnd, WM_GETTEXT, nameLength + 1, reinterpret_cast<LPARAM>(nameWindow));
        QString nameWindowQString = QString::fromStdWString(nameWindow);
        if( nameWindowQString == nameFindWindow )
        {
            SendMessage(hwnd, WM_CLOSE, 0, 0);
            count++;
        }
        delete[] nameWindow;
    }
    return count == 10 ? FALSE : TRUE;
}
