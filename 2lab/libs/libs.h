#ifndef LIBS_H
#define LIBS_H
#include <windows.h>
#include <QString>

void MinimizeAllWindowsWithName(const QString& nameWindow);
void MaximizeAllWindowsWithName(const QString& nameWindow);
void CloseAllWindowsWithName(const QString& nameWindow);
BOOL CALLBACK MinimizeMyWindow(HWND hwnd,  LPARAM lParam);
BOOL CALLBACK MaximizeMyWindow(HWND hwnd,  LPARAM lParam);
BOOL CALLBACK CloseMyWindow(HWND hwnd,  LPARAM lParam);

#endif // LIBS_H
