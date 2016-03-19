#ifndef TREADCLASSES
#define TREADCLASSES
#include <QObject>
#include <QColor>
#include <Windows.h>
#include "mypoint.h"
class BaseTreadClass : public QObject{
    Q_OBJECT
    QColor m_col;
    int m_y;
    int m_maxX;
public:
    void mainWork();
    QColor getColor() const {return m_col;}
    int getY() const {return m_y;}
    int getMaxX() const {return m_maxX;}
    virtual void Run() = 0;
    virtual void addNewPoint(MyPoint) {}
    virtual ~BaseTreadClass(){}
    BaseTreadClass(QColor col, int y, int maxX);
};

class ThreadCriticalSection : public BaseTreadClass{
    Q_OBJECT
    CRITICAL_SECTION* m_cs;
public:
    ThreadCriticalSection(QColor col, int y, int maxX, CRITICAL_SECTION* cs);
    virtual void Run();
    virtual ~ThreadCriticalSection(){}
signals:
    void addNewPoint(MyPoint p);
};

class ThreadWithPriority : public BaseTreadClass{
    Q_OBJECT
public:
    ThreadWithPriority(QColor col, int y, int maxX);
    virtual void Run();
    virtual ~ThreadWithPriority() {}
signals:
    void addNewPoint(MyPoint p);
};

class ThreadWithMutex : public BaseTreadClass{
    Q_OBJECT
    HANDLE m_mutex;
public:
    ThreadWithMutex(QColor col, int y, int maxX, HANDLE mutex);
    virtual void Run();
    virtual ~ThreadWithMutex() {}
signals:
    void addNewPoint(MyPoint p);
};

class ThreadWithSemaphore : public BaseTreadClass{
    Q_OBJECT
    HANDLE m_sem;
public:
    ThreadWithSemaphore(QColor col, int y, int maxX, HANDLE semaphore);
    virtual void Run();
    virtual ~ThreadWithSemaphore() {}
signals:
    void addNewPoint(MyPoint p);
};

class ThreadWithEvent : public BaseTreadClass{
    Q_OBJECT
    HANDLE m_event;
public:
    ThreadWithEvent(QColor col, int y, int maxX, HANDLE event);
    virtual void Run();
    virtual ~ThreadWithEvent() {}
signals:
    void addNewPoint(MyPoint p);
};

class ThreadWithManualEvent : public BaseTreadClass{
    Q_OBJECT
    HANDLE m_event;
public:
    ThreadWithManualEvent(QColor col, int y, int maxX, HANDLE event);
    virtual void Run();
    virtual ~ThreadWithManualEvent() {}
signals:
    void addNewPoint(MyPoint p);
};

#endif // TREADCLASSES

