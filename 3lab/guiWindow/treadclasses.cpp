#include "treadclasses.h"
#include "mypoint.h"
#include <QDebug>

BaseTreadClass::BaseTreadClass(QColor color, int y, int maxX)
                : m_col(color),
                  m_y(y),
                  m_maxX(maxX)
{

}

void BaseTreadClass::mainWork()
{
    for(size_t i = 0; i < this->getMaxX(); ++i )
    {
        MyPoint point(this->getColor(), this->getY());
        emit addNewPoint(point);
        for(size_t j = 0; j < 1000000; ++j )
        {
            j++;
        }
    }
}

ThreadCriticalSection::ThreadCriticalSection(QColor col, int y, int maxX, CRITICAL_SECTION* cs)
                    : BaseTreadClass(col, y, maxX), m_cs(cs)
{

}



void ThreadCriticalSection::Run()
{
    qDebug() << "Run thread with critical section and color " << this->getColor().name();
    EnterCriticalSection(m_cs);
    mainWork();
    LeaveCriticalSection(m_cs);
}

ThreadWithPriority::ThreadWithPriority(QColor col, int y, int maxX) : BaseTreadClass(col, y, maxX)
{

}

void ThreadWithPriority::Run()
{
    qDebug() << "Run thread with priority and color " << this->getColor().name();
    mainWork();
}

ThreadWithMutex::ThreadWithMutex(QColor col, int y, int maxX, HANDLE mutex) : BaseTreadClass(col, y, maxX), m_mutex(mutex)
{

}

void ThreadWithMutex::Run()
{
    qDebug() << "Run thread with mutex and color " << this->getColor().name();
    WaitForSingleObject(m_mutex, INFINITE);
    mainWork();
    ReleaseMutex(m_mutex);
}

ThreadWithSemaphore::ThreadWithSemaphore(QColor col, int y, int maxX, HANDLE semaphore) : BaseTreadClass(col, y, maxX), m_sem(semaphore)
{

}

void ThreadWithSemaphore::Run()
{
    WaitForSingleObject(m_sem, INFINITE);
    mainWork();
    ReleaseSemaphore(m_sem, 1, 0);
}

ThreadWithEvent::ThreadWithEvent(QColor col, int y, int maxX, HANDLE event) : BaseTreadClass(col, y, maxX), m_event(event)
{

}

void ThreadWithEvent::Run()
{
    WaitForSingleObject(m_event, INFINITE);
    mainWork();
    SetEvent(m_event);
}

ThreadWithManualEvent::ThreadWithManualEvent(QColor col, int y, int maxX, HANDLE event) : BaseTreadClass(col, y, maxX), m_event(event)
{

}

void ThreadWithManualEvent::Run()
{
    for(size_t i = 0; i < this->getMaxX(); ++i )
    {
        WaitForSingleObject(m_event, INFINITE);
        MyPoint point(this->getColor(), this->getY());
        emit addNewPoint(point);
        for(size_t j = 0; j < 1000000; ++j )
        {
            j++;
        }
    }
    SetEvent(m_event);
}
