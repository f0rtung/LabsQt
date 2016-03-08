/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.5.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralWidget;
    QPushButton *pushButtonExit;
    QPushButton *pushButtonRunCalc;
    QPushButton *pushButtonCloseAllCalc;
    QPushButton *pushButtonMinAllWindow;
    QPushButton *pushButtonCloseAllCalc_2;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(212, 207);
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        pushButtonExit = new QPushButton(centralWidget);
        pushButtonExit->setObjectName(QStringLiteral("pushButtonExit"));
        pushButtonExit->setGeometry(QRect(10, 130, 191, 23));
        pushButtonRunCalc = new QPushButton(centralWidget);
        pushButtonRunCalc->setObjectName(QStringLiteral("pushButtonRunCalc"));
        pushButtonRunCalc->setGeometry(QRect(10, 10, 191, 23));
        pushButtonCloseAllCalc = new QPushButton(centralWidget);
        pushButtonCloseAllCalc->setObjectName(QStringLiteral("pushButtonCloseAllCalc"));
        pushButtonCloseAllCalc->setGeometry(QRect(10, 40, 191, 23));
        pushButtonMinAllWindow = new QPushButton(centralWidget);
        pushButtonMinAllWindow->setObjectName(QStringLiteral("pushButtonMinAllWindow"));
        pushButtonMinAllWindow->setGeometry(QRect(10, 70, 191, 23));
        pushButtonCloseAllCalc_2 = new QPushButton(centralWidget);
        pushButtonCloseAllCalc_2->setObjectName(QStringLiteral("pushButtonCloseAllCalc_2"));
        pushButtonCloseAllCalc_2->setGeometry(QRect(10, 100, 191, 23));
        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 212, 18));
        MainWindow->setMenuBar(menuBar);
        mainToolBar = new QToolBar(MainWindow);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        MainWindow->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        MainWindow->setStatusBar(statusBar);

        retranslateUi(MainWindow);
        QObject::connect(pushButtonExit, SIGNAL(clicked()), MainWindow, SLOT(close()));

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", 0));
        pushButtonExit->setText(QApplication::translate("MainWindow", "\320\222\321\213\321\205\320\276\320\264", 0));
        pushButtonRunCalc->setText(QApplication::translate("MainWindow", "\320\227\320\260\320\277\321\203\321\201\321\202\320\270\321\202\321\214 10 \320\272\320\260\320\273\321\214\320\272\321\203\320\273\321\217\321\202\320\276\321\200\320\276\320\262", 0));
        pushButtonCloseAllCalc->setText(QApplication::translate("MainWindow", "\320\241\320\262\320\265\321\200\320\275\321\203\321\202\321\214 \320\262\321\201\320\265 \320\272\320\260\320\273\321\214\320\272\321\203\320\273\321\217\321\202\320\276\321\200\321\213", 0));
        pushButtonMinAllWindow->setText(QApplication::translate("MainWindow", "\320\222\320\276\321\201\321\201\321\202\320\260\320\275\320\276\320\262\320\270\321\202\321\214 \320\276\320\272\320\275\320\260 \320\272\320\260\320\273\321\214\320\272\321\203\320\273\321\217\321\202\320\276\321\200\320\276\320\262", 0));
        pushButtonCloseAllCalc_2->setText(QApplication::translate("MainWindow", "\320\227\320\260\320\272\321\200\321\213\321\202\321\214 \320\262\321\201\320\265 \320\276\320\272\320\275\320\260 \320\272\320\260\320\273\321\214\320\272\321\203\320\273\321\217\321\202\320\276\321\200\320\276\320\262", 0));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
