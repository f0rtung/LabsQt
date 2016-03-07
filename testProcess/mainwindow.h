#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
protected:
    virtual bool nativeEvent(const QByteArray &eventType, void *message, long *result);


private slots:
    void on_pushWriteTextToFille_clicked();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
