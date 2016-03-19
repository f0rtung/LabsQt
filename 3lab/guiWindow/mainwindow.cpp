#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QPainter>
#include <QDebug>
#include "mypoint.h"
#include "treadclasses.h"
#pragma comment(lib,"user32.lib")


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    if(SetProcessAffinityMask( GetCurrentProcess(), 1) )
    {
        qDebug() << "All treads will work on 1 processor!";
    }
    SetThreadPriority(GetCurrentThread(), THREAD_PRIORITY_HIGHEST);

    ui->radioButton_2->setChecked(true);
    ui->radioButton_4->setChecked(true);
    ui->radioButton_7->setChecked(true);

    vecPoints.clear();
    commonX = 0;
    InitializeCriticalSection(&cs);
    if( unknownMutex = CreateMutex(0, FALSE, 0))
    {
        qDebug() << "Create mutex!";
    }

    if( nameMutex = CreateMutex(0, FALSE, L"MyMutex"))
    {
        qDebug() << "Create mutex with name MyMutex!";
    }

    if( unknownSemaphore = CreateSemaphore(0, 2, 3, NULL))
    {
        qDebug() << "Create Semaphore!";
    }

    if( unknownSemaphore = CreateSemaphore(0, 2, 3, L"MySemaphore"))
    {
        qDebug() << "Create Semaphore with name MySemaphore!";
    }

    if( autoEvent = CreateEvent(0, FALSE, TRUE, NULL))
    {
        qDebug() << "Create autoEvent!";
    }

    if( manualEvent = CreateEvent(0, TRUE, FALSE, NULL))
    {
        qDebug() << "Create manualEvent!";
    }
    needClear = false;
}

DWORD MainWindow::treadFunc(LPVOID lpParam)
{
    static_cast<BaseTreadClass*>(lpParam)->Run();
    return 0;
}

MainWindow::~MainWindow()
{
    DeleteCriticalSection(&cs);
    CloseHandle(nameMutex);
    CloseHandle(unknownMutex);
    CloseHandle(autoEvent);
    CloseHandle(manualEvent);
    CloseHandle(unknownSemaphore);
    CloseHandle(nameSemaphore);
    delete ui;
}

void MainWindow::InitSignalsSlots()
{
    connect(tRed.get(), SIGNAL(addNewPoint(MyPoint)), this, SLOT(getPointFromThread(MyPoint)));
    connect(tBlack.get(), SIGNAL(addNewPoint(MyPoint)), this, SLOT(getPointFromThread(MyPoint)));
    connect(tGreen.get(), SIGNAL(addNewPoint(MyPoint)), this, SLOT(getPointFromThread(MyPoint)));
}

std::vector<HANDLE> MainWindow::createSuspendedThreads()
{
    std::vector<HANDLE> threads;
    threads.push_back(CreateThread(0, 0, treadFunc, (LPVOID)tRed.get(), CREATE_SUSPENDED, NULL));
    threads.push_back(CreateThread(0, 0, treadFunc, (LPVOID)tBlack.get(), CREATE_SUSPENDED, NULL));
    threads.push_back(CreateThread(0, 0, treadFunc, (LPVOID)tGreen.get(), CREATE_SUSPENDED, NULL));
    return threads;
}

void MainWindow::runSuspendedThreadsAndCloseHandle(const std::vector<HANDLE> &hArr)
{
    runSuspendedThreads(hArr);
    closeAllThreadsHandle(hArr);
}

void MainWindow::runSuspendedThreads(const std::vector<HANDLE> &hArr)
{
    for(const auto& thread : hArr)
    {
        ResumeThread(thread);
    }
}

void MainWindow::closeAllThreadsHandle(const std::vector<HANDLE> &hArr)
{
    for(const auto& thread : hArr)
    {
        CloseHandle(thread);
    }
}

PRIORITY MainWindow::getPriorityRedThread()
{
    if( ui->radioButton_2->isChecked()) return PRIORITY::NORM;
    else if( ui->radioButton->isChecked()) return PRIORITY::MIN;
    else return PRIORITY::MAX;
}

PRIORITY MainWindow::getPriorityBlackThread()
{
    if( ui->radioButton_4->isChecked()) return PRIORITY::NORM;
    else if( ui->radioButton_6->isChecked()) return PRIORITY::MIN;
    else return PRIORITY::MAX;
}

PRIORITY MainWindow::getPriorityGreenThread()
{
    if( ui->radioButton_7->isChecked()) return PRIORITY::NORM;
    else if( ui->radioButton_9->isChecked()) return PRIORITY::MIN;
    else return PRIORITY::MAX;
}

void MainWindow::setAllThreadsPriority(const std::vector<HANDLE> &vec)
{
    setTreadPriority(vec[0], getPriorityRedThread());
    setTreadPriority(vec[1], getPriorityBlackThread());
    setTreadPriority(vec[2], getPriorityGreenThread());
}

void MainWindow::setTreadPriority(HANDLE tread, PRIORITY prt)
{
    switch (prt) {
    case MIN:
        if( !SetThreadPriority(tread, THREAD_PRIORITY_LOWEST) )
        {
            qDebug() << "Error set priority!" << GetLastError();
        }
        break;
    case NORM:
        if( !SetThreadPriority(tread, THREAD_PRIORITY_IDLE) )
        {
            qDebug() << "Error set priority!" << GetLastError();
        }
        break;
    case MAX:
        if( !SetThreadPriority(tread, THREAD_PRIORITY_HIGHEST) )
        {
            qDebug() << "Error set priority!" << GetLastError();
        }
        break;
    }
}

void MainWindow::paintEvent(QPaintEvent *)
{
    QPainter painter;
    painter.begin(this);
    if(!needClear)
    {
        for(const auto& point : vecPoints)
        {
            painter.setPen(QPen(point.col));
            painter.drawLine(point.m_x, point.m_y + 5, point.m_x, point.m_y - 5);
        }
    }
    painter.end();
    needClear = false;
}

void MainWindow::getPointFromThread(MyPoint point)
{
    point.m_x = commonX++;
    vecPoints.push_back(point);
    repaint();
}

void MainWindow::on_pushButtonWithOutBlocks_clicked()
{
    on_pushButton_3_clicked();
    tRed.reset(new ThreadWithPriority(Qt::red, 400, 200));
    tBlack.reset(new ThreadWithPriority(Qt::black, 300, 200));
    tGreen.reset(new ThreadWithPriority(Qt::green, 200, 200));

    InitSignalsSlots();
    std::vector<HANDLE> hArr = createSuspendedThreads();

    setAllThreadsPriority(hArr);

    runSuspendedThreadsAndCloseHandle(hArr);

}

void MainWindow::on_pushButton_clicked()
{
    on_pushButton_3_clicked();
    InitThreads<ThreadCriticalSection, CRITICAL_SECTION*>(&cs);
    InitSignalsSlots();
    std::vector<HANDLE> hArr = createSuspendedThreads();
    setAllThreadsPriority(hArr);
    runSuspendedThreadsAndCloseHandle(hArr);
}

void MainWindow::on_pushButton_3_clicked()
{
    needClear   = true;
    commonX     = 0;
    vecPoints.clear();
    repaint();
}

void MainWindow::on_pushButton_4_clicked()
{
    on_pushButton_3_clicked();
    InitThreads<ThreadWithMutex, HANDLE>(unknownMutex);
    InitSignalsSlots();
    std::vector<HANDLE> hArr = createSuspendedThreads();
    setAllThreadsPriority(hArr);
    runSuspendedThreadsAndCloseHandle(hArr);
}

void MainWindow::on_pushButton_5_clicked()
{
    on_pushButton_3_clicked();
    InitThreads<ThreadWithMutex, HANDLE>(nameMutex);
    InitSignalsSlots();
    std::vector<HANDLE> hArr = createSuspendedThreads();
    setAllThreadsPriority(hArr);
    runSuspendedThreadsAndCloseHandle(hArr);
}

void MainWindow::on_pushButton_6_clicked()
{
    on_pushButton_3_clicked();
    InitThreads<ThreadWithSemaphore, HANDLE>(unknownSemaphore);
    InitSignalsSlots();
    std::vector<HANDLE> hArr = createSuspendedThreads();
    setAllThreadsPriority(hArr);
    runSuspendedThreadsAndCloseHandle(hArr);
}

void MainWindow::on_pushButton_7_clicked()
{
    on_pushButton_3_clicked();
    InitThreads<ThreadWithSemaphore, HANDLE>(nameSemaphore);
    InitSignalsSlots();
    std::vector<HANDLE> hArr = createSuspendedThreads();
    setAllThreadsPriority(hArr);
    runSuspendedThreadsAndCloseHandle(hArr);
}

void MainWindow::on_pushButton_8_clicked()
{
    on_pushButton_3_clicked();
    InitThreads<ThreadWithEvent, HANDLE>(autoEvent);
    InitSignalsSlots();
    std::vector<HANDLE> hArr = createSuspendedThreads();
    setAllThreadsPriority(hArr);
    runSuspendedThreadsAndCloseHandle(hArr);
}

void MainWindow::on_pushButton_9_clicked()
{
    on_pushButton_3_clicked();
    InitThreads<ThreadWithManualEvent, HANDLE>(manualEvent);
    InitSignalsSlots();
    std::vector<HANDLE> hArr = createSuspendedThreads();
    setAllThreadsPriority(hArr);
    runSuspendedThreads(hArr);
    while(TRUE)
    {
        MsgWaitForMultipleObjects(  NULL,
                                    NULL,
                                    FALSE,
                                    INFINITE,
                                    static_cast<DWORD>(QS_ALLEVENTS) );
        MSG m;
        while( PeekMessage(&m, 0, 0, 0, PM_REMOVE) )
        {
            DispatchMessage(&m);
        }
    }
    closeAllThreadsHandle(hArr);
}

void MainWindow::on_pushButton_10_clicked()
{
    SetEvent(manualEvent);
}

void MainWindow::on_pushButton_11_clicked()
{
    ResetEvent(manualEvent);
}
