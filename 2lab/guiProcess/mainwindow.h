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

private slots:
    void on_pushButtonRunCalc_clicked();

    void on_pushButtonCloseAllCalc_clicked();

    void on_pushButtonMinAllWindow_clicked();

    void on_pushButtonCloseAllCalc_2_clicked();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
