#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <commonfunc.h>
#include <QMainWindow>
#include <memory>
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    Utils::FileMapping file;
    Utils::FileMapping* fileMapLastTask;
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
protected:
    virtual bool nativeEvent(const QByteArray &eventType, void *message, long *result);
private slots:
    void on_RunNotepad_clicked();

    void on_runThreeProc_clicked();

    void on_pushButtonStartupInfo_clicked();

    void on_startMyProcess_clicked();

    void on_RunProcess_clicked();

    void on_pushButtonSendMessage_clicked();

    void on_lineEdit_textChanged(const QString &arg1);

    void on_pushButtonCreateFileMapping_clicked();

    void on_pushButton_clicked();

    void on_CloseMapFile_clicked();

    void on_WriteMapFile_clicked();

    void on_pushButton_2_clicked();

    void on_textEdit_textChanged();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
