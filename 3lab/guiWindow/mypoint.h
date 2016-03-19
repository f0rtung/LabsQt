#ifndef MYPOINT
#define MYPOINT
#include <QColor>
struct MyPoint{
    QColor col;
    int m_y;
    int m_x;
    MyPoint(QColor c, int y) : col(c), m_y(y), m_x(0) {}
    MyPoint(){}
};
enum PRIORITY {MIN, NORM, MAX};
#endif // MYPOINT

