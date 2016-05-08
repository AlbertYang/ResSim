#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include"setdialog.h"
#include"simulation.h"

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
    void on_exitButton_clicked();

    void on_pushButton_2_clicked();

    void on_startButton_clicked();

    void on_pushButton_clicked();

    void on_setButton_clicked();

private:
    Ui::MainWindow *ui;
    bool isStop;
    setDialog *setD;
    simulation *sim;

};

#endif // MAINWINDOW_H
