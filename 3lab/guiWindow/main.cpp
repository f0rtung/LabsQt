#include "mainwindow.h"
#include <QApplication>
#include "mypoint.h"

Q_DECLARE_METATYPE(MyPoint);

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    qRegisterMetaType<MyPoint>();
    return a.exec();
}
