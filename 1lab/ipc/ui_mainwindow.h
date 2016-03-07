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
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTextBrowser>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralWidget;
    QPushButton *exitButton;
    QPushButton *RunNotepad;
    QPushButton *runThreeProc;
    QPushButton *pushButtonStartupInfo;
    QPushButton *startMyProcess;
    QGroupBox *groupBox;
    QPushButton *RunProcess;
    QPushButton *pushButtonSendMessage;
    QLineEdit *lineEdit;
    QGroupBox *groupBox_2;
    QTextBrowser *textBrowser;
    QPushButton *pushButtonCreateFileMapping;
    QGroupBox *groupBox_3;
    QLineEdit *lineEdit_2;
    QPushButton *pushButton;
    QPushButton *WriteMapFile;
    QPushButton *CloseMapFile;
    QGroupBox *groupBox_4;
    QTextEdit *textEdit;
    QPushButton *pushButton_2;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(539, 526);
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        exitButton = new QPushButton(centralWidget);
        exitButton->setObjectName(QStringLiteral("exitButton"));
        exitButton->setGeometry(QRect(424, 10, 101, 111));
        RunNotepad = new QPushButton(centralWidget);
        RunNotepad->setObjectName(QStringLiteral("RunNotepad"));
        RunNotepad->setGeometry(QRect(10, 10, 101, 23));
        runThreeProc = new QPushButton(centralWidget);
        runThreeProc->setObjectName(QStringLiteral("runThreeProc"));
        runThreeProc->setGeometry(QRect(10, 40, 101, 23));
        pushButtonStartupInfo = new QPushButton(centralWidget);
        pushButtonStartupInfo->setObjectName(QStringLiteral("pushButtonStartupInfo"));
        pushButtonStartupInfo->setGeometry(QRect(10, 70, 101, 23));
        startMyProcess = new QPushButton(centralWidget);
        startMyProcess->setObjectName(QStringLiteral("startMyProcess"));
        startMyProcess->setGeometry(QRect(10, 100, 101, 23));
        groupBox = new QGroupBox(centralWidget);
        groupBox->setObjectName(QStringLiteral("groupBox"));
        groupBox->setGeometry(QRect(120, 10, 291, 111));
        RunProcess = new QPushButton(groupBox);
        RunProcess->setObjectName(QStringLiteral("RunProcess"));
        RunProcess->setGeometry(QRect(10, 20, 111, 31));
        pushButtonSendMessage = new QPushButton(groupBox);
        pushButtonSendMessage->setObjectName(QStringLiteral("pushButtonSendMessage"));
        pushButtonSendMessage->setGeometry(QRect(10, 60, 111, 31));
        lineEdit = new QLineEdit(groupBox);
        lineEdit->setObjectName(QStringLiteral("lineEdit"));
        lineEdit->setGeometry(QRect(130, 20, 131, 21));
        groupBox_2 = new QGroupBox(centralWidget);
        groupBox_2->setObjectName(QStringLiteral("groupBox_2"));
        groupBox_2->setGeometry(QRect(10, 130, 511, 121));
        textBrowser = new QTextBrowser(groupBox_2);
        textBrowser->setObjectName(QStringLiteral("textBrowser"));
        textBrowser->setGeometry(QRect(120, 10, 381, 101));
        pushButtonCreateFileMapping = new QPushButton(groupBox_2);
        pushButtonCreateFileMapping->setObjectName(QStringLiteral("pushButtonCreateFileMapping"));
        pushButtonCreateFileMapping->setGeometry(QRect(10, 20, 101, 81));
        groupBox_3 = new QGroupBox(centralWidget);
        groupBox_3->setObjectName(QStringLiteral("groupBox_3"));
        groupBox_3->setGeometry(QRect(10, 260, 511, 111));
        lineEdit_2 = new QLineEdit(groupBox_3);
        lineEdit_2->setObjectName(QStringLiteral("lineEdit_2"));
        lineEdit_2->setGeometry(QRect(10, 60, 481, 31));
        pushButton = new QPushButton(groupBox_3);
        pushButton->setObjectName(QStringLiteral("pushButton"));
        pushButton->setGeometry(QRect(10, 20, 111, 23));
        WriteMapFile = new QPushButton(groupBox_3);
        WriteMapFile->setObjectName(QStringLiteral("WriteMapFile"));
        WriteMapFile->setGeometry(QRect(190, 20, 111, 23));
        CloseMapFile = new QPushButton(groupBox_3);
        CloseMapFile->setObjectName(QStringLiteral("CloseMapFile"));
        CloseMapFile->setGeometry(QRect(380, 20, 111, 23));
        groupBox_4 = new QGroupBox(centralWidget);
        groupBox_4->setObjectName(QStringLiteral("groupBox_4"));
        groupBox_4->setGeometry(QRect(10, 370, 511, 101));
        textEdit = new QTextEdit(groupBox_4);
        textEdit->setObjectName(QStringLiteral("textEdit"));
        textEdit->setGeometry(QRect(120, 10, 381, 81));
        pushButton_2 = new QPushButton(groupBox_4);
        pushButton_2->setObjectName(QStringLiteral("pushButton_2"));
        pushButton_2->setGeometry(QRect(10, 20, 101, 71));
        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 539, 18));
        MainWindow->setMenuBar(menuBar);
        mainToolBar = new QToolBar(MainWindow);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        MainWindow->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        MainWindow->setStatusBar(statusBar);

        retranslateUi(MainWindow);
        QObject::connect(exitButton, SIGNAL(clicked()), MainWindow, SLOT(close()));

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", 0));
        exitButton->setText(QApplication::translate("MainWindow", "Exit", 0));
        RunNotepad->setText(QApplication::translate("MainWindow", "Run Notepad", 0));
        runThreeProc->setText(QApplication::translate("MainWindow", "Run 3 proc", 0));
        pushButtonStartupInfo->setText(QApplication::translate("MainWindow", "StartupInfo", 0));
        startMyProcess->setText(QApplication::translate("MainWindow", "Start Test Process", 0));
        groupBox->setTitle(QApplication::translate("MainWindow", "SendMessage", 0));
        RunProcess->setText(QApplication::translate("MainWindow", "Run Process", 0));
        pushButtonSendMessage->setText(QApplication::translate("MainWindow", "Send Message", 0));
        groupBox_2->setTitle(QApplication::translate("MainWindow", "FileMapping", 0));
        pushButtonCreateFileMapping->setText(QApplication::translate("MainWindow", "Create FileMapping", 0));
        groupBox_3->setTitle(QApplication::translate("MainWindow", "FileMapping", 0));
        pushButton->setText(QApplication::translate("MainWindow", "\320\241\320\276\320\267\320\264\320\260\321\202\321\214", 0));
        WriteMapFile->setText(QApplication::translate("MainWindow", "\320\227\320\260\320\277\320\270\321\201\320\260\321\202\321\214", 0));
        CloseMapFile->setText(QApplication::translate("MainWindow", "\320\227\320\260\320\272\321\200\321\213\321\202\321\214", 0));
        groupBox_4->setTitle(QApplication::translate("MainWindow", "\320\237\320\276\321\201\320\273\320\265\320\264\320\275\320\265\320\265 \320\267\320\260\320\264\320\260\320\275\320\270\320\265", 0));
        pushButton_2->setText(QApplication::translate("MainWindow", "Mapping File", 0));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
