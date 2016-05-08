#include "mainwindow.h"
#include "ui_mainwindow.h"

#include<sstream>
#include<fstream>
#include<string>
#include<cstdlib>
#include<time.h>
#include <ctime>
#include<QTime>
#include<iostream>
using namespace std;

int random(int start, int end);
string i2s(int a );
QString s2q(const string &s);
string q2s(const QString &s);

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setD=NULL;
    sim=NULL;
}

MainWindow::~MainWindow()
{
    delete ui;
    delete setD;
    delete sim;
}

void MainWindow::on_exitButton_clicked()
{
    isStop = true;
}

void MainWindow::on_pushButton_2_clicked(){}

void MainWindow::on_startButton_clicked()
{
    isStop = false;
    ui->startButton->setEnabled(0);
    ui->resultBrowser->setText("");
    double size = atof(q2s(ui->sizeEdit->text()).c_str());

    int time = 0;
    int hour = 6 + time/60;
    int minute = time%60;
    QString strHour = "06";
    QString strMin = "00";

    ifstream inFile;
    inFile.open("info.txt");
    string tmpStr;
    if(!getline(inFile,tmpStr)){
        tmpStr = "\"info.txt\"不存在，请先进行参数配置！\n";
        ui->resultBrowser->append(s2q(tmpStr));
        ui->startButton->setEnabled(1);
        ui->timeLabel->setText(strHour+":"+strMin);
        return;
    }

    if(sim!=NULL){
        delete sim;
        sim=NULL;
    }
    sim = new simulation("info.txt");

    while(strHour!="23" && !isStop){
        QTime t;
        t.start();
        while(t.elapsed()<size*1000){QCoreApplication::processEvents();}  //此处设定循环间隔

        if(hour<10)
            strHour = "0"+s2q(i2s(hour));
        else
            strHour = s2q(i2s(hour));

        if(minute<10)
            strMin = "0"+s2q(i2s(minute));
        else
            strMin = s2q(i2s(minute));
        ui->timeLabel->setText(strHour+":"+strMin);

        int nowTime = hour*60+minute;
        string result = sim->simulate(nowTime);
        if(result!=""){
            ui->resultBrowser->append(s2q(result));
            ofstream fout;
            fout.open("result.txt");
            fout<<result<<endl;
            fout.close();
        }

        time++;
        hour = 6 + time/60;
        minute = time%60;
    }
    ui->timeLabel->setText(strHour+":"+strMin);
    ui->startButton->setEnabled(1);
}

void MainWindow::on_pushButton_clicked()
{
    exit(0);
}

void MainWindow::on_setButton_clicked()
{
    if(setD!=NULL){
        delete setD;
        setD=NULL;
    }
    setD = new setDialog();
    setD->loadfile("info.txt");
    setD->show();
}
