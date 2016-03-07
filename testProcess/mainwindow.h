#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <commonfunc.h>

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
    void on_pushWriteTextToFille_clicked();

    void on_pushButton_clicked();

    void on_CloseMapFile_clicked();

    void on_WriteMapFile_clicked();

    void on_pushButton_2_clicked();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
