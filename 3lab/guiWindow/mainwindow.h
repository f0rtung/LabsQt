#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "mypoint.h"
#include <vector>
#include <Windows.h>
#include "treadclasses.h"
#include <memory>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    static DWORD WINAPI treadFunc(LPVOID lpParam);
    ~MainWindow();

private:
    template<typename ThreadType, typename SynchPrimitive>
    void InitThreads(SynchPrimitive prim)
    {
        tRed.reset(new ThreadType(Qt::red, 400, 200, prim));
        tBlack.reset(new ThreadType(Qt::black, 300, 200, prim));
        tGreen.reset(new ThreadType(Qt::green, 200, 200, prim));
    }

    void InitSignalsSlots();
    std::vector<HANDLE> createSuspendedThreads();
    void runSuspendedThreadsAndCloseHandle(const std::vector<HANDLE>& hArr);
    void runSuspendedThreads(const std::vector<HANDLE>& hArr);
    void closeAllThreadsHandle(const std::vector<HANDLE>& hArr);
    Ui::MainWindow *ui;
    std::vector<MyPoint> vecPoints;
    int commonX;
    CRITICAL_SECTION cs;
    HANDLE unknownMutex;
    HANDLE nameMutex;
    HANDLE unknownSemaphore;
    HANDLE nameSemaphore;
    HANDLE autoEvent;
    HANDLE manualEvent;
    std::shared_ptr<BaseTreadClass> tRed;
    std::shared_ptr<BaseTreadClass> tBlack;
    std::shared_ptr<BaseTreadClass> tGreen;

    PRIORITY getPriorityRedThread();
    PRIORITY getPriorityBlackThread();
    PRIORITY getPriorityGreenThread();

    void setAllThreadsPriority(const std::vector<HANDLE>& vec);
    void setTreadPriority(HANDLE tread, PRIORITY prt);
    bool needClear;
protected:
    void paintEvent(QPaintEvent *);
private slots:
    void getPointFromThread(MyPoint point);
    void on_pushButtonWithOutBlocks_clicked();
    void on_pushButton_clicked();
    void on_pushButton_3_clicked();
    void on_pushButton_4_clicked();
    void on_pushButton_5_clicked();
    void on_pushButton_6_clicked();
    void on_pushButton_7_clicked();
    void on_pushButton_8_clicked();
    void on_pushButton_9_clicked();
    void on_pushButton_10_clicked();
    void on_pushButton_11_clicked();
};

#endif // MAINWINDOW_H
