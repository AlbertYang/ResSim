#ifndef SETDIALOG_H
#define SETDIALOG_H

#include <QDialog>
#include<iostream>
#include<string>
using namespace std;

namespace Ui {
class setDialog;
}

class setDialog : public QDialog
{
    Q_OBJECT
    
public:
    explicit setDialog(QWidget *parent = 0);
    void loadfile(const char* filename);
    ~setDialog();
    
private slots:
    void on_saveButton_clicked();

    void on_cancelButton_clicked();

private:
    Ui::setDialog *ui;
};

#endif // SETDIALOG_H
