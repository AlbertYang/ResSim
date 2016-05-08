#include <QtGui/QApplication>
#include "mainwindow.h"
#include<cstdlib>
#include<time.h>
#include <ctime>
#include<sstream>
#include<string>
using namespace std;

int random(int start, int end) //产生一个从start到end的随机数
{
    int tmpRand = start + rand()%(end-start+1);
    return tmpRand;
}

string i2s(int a ){   // change a number to a string
   string temp;//temp:string;
   ostringstream oss;
   oss<<a;
   temp=oss.str();
   return temp;
}

QString s2q(const string &s) //string to QString
{
return QString(QString::fromLocal8Bit(s.c_str()));
}
string q2s(const QString &s) //QString to string
{
return string((const char *)s.toLocal8Bit());
}

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    srand(unsigned(time(0)));
    w.show();
    
    return a.exec();

}
