#include "setdialog.h"
#include "ui_setdialog.h"

#include<iostream>
#include <iostream>
#include<sstream>
#include<fstream>
#include<string>
using namespace std;

int random(int start, int end);
string i2s(int a );
QString s2q(const string &s);
string q2s(const QString &s);

setDialog::setDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::setDialog)
{
    ui->setupUi(this);
}

void setDialog::loadfile(const char* filename)
{
    ifstream infile;
    infile.open(filename);

    string tmpLine;
    while(getline(infile,tmpLine)){
        if(tmpLine=="CONSUMER_INFO"){
            getline(infile,tmpLine);
            istringstream istring(tmpLine);
            string tmp[4];
            istring>>tmp[0]>>tmp[1]>>tmp[2]>>tmp[3];
            ui->lineEdit->setText(s2q(tmp[0]));
            ui->lineEdit_2->setText(s2q(tmp[1]));
            ui->lineEdit_3->setText(s2q(tmp[2]));
            ui->lineEdit_4->setText(s2q(tmp[3]));
        }

        if(tmpLine=="SIMULATION_INFO"){
            getline(infile,tmpLine);
            istringstream istring(tmpLine);
            string tmp[4];
            istring>>tmp[0]>>tmp[1]>>tmp[2]>>tmp[3];
            ui->lineEdit_28->setText(s2q(tmp[0]));
            ui->lineEdit_29->setText(s2q(tmp[1]));
            ui->lineEdit_30->setText(s2q(tmp[2]));
            ui->lineEdit_31->setText(s2q(tmp[3]));
        }

        if(tmpLine=="RESTAURANT_INFO"){
            string temp;

            string tmp[2];
            getline(infile,tmpLine);
            istringstream istring(tmpLine);
            istring>>temp>>tmp[0];
            getline(infile,tmpLine);
            istringstream istring2(tmpLine);
            istring2>>temp>>tmp[1];
            ui->lineEdit_5->setText(s2q(tmp[0]));
            ui->lineEdit_6->setText(s2q(tmp[1]));

            string tmp2[7][3];
            for(int i=0;i<7;i++){
                getline(infile,tmpLine);
                istringstream istring(tmpLine);
                istring>>temp>>tmp2[i][0]>>tmp2[i][1]>>tmp2[i][2];
            }

            ui->lineEdit_7->setText(s2q(tmp2[0][0]));ui->lineEdit_8->setText(s2q(tmp2[0][1]));ui->lineEdit_9->setText(s2q(tmp2[0][2]));
            ui->lineEdit_10->setText(s2q(tmp2[1][0]));ui->lineEdit_11->setText(s2q(tmp2[1][1]));ui->lineEdit_12->setText(s2q(tmp2[1][2]));
            ui->lineEdit_13->setText(s2q(tmp2[2][0]));ui->lineEdit_14->setText(s2q(tmp2[2][1]));ui->lineEdit_15->setText(s2q(tmp2[2][2]));
            ui->lineEdit_16->setText(s2q(tmp2[3][0]));ui->lineEdit_17->setText(s2q(tmp2[3][1]));ui->lineEdit_18->setText(s2q(tmp2[3][2]));
            ui->lineEdit_19->setText(s2q(tmp2[4][0]));ui->lineEdit_20->setText(s2q(tmp2[4][1]));ui->lineEdit_21->setText(s2q(tmp2[4][2]));
            ui->lineEdit_22->setText(s2q(tmp2[5][0]));ui->lineEdit_23->setText(s2q(tmp2[5][1]));ui->lineEdit_24->setText(s2q(tmp2[5][2]));
            ui->lineEdit_25->setText(s2q(tmp2[6][0]));ui->lineEdit_26->setText(s2q(tmp2[6][1]));ui->lineEdit_27->setText(s2q(tmp2[6][2]));

        }
    }
    infile.close();
}

setDialog::~setDialog()
{
    delete ui;
}

void setDialog::on_saveButton_clicked()
{
    ofstream outFile;
    outFile.open("info.txt");
    if(outFile.fail())
    {
            cout<<"Input file opening failed.\n";
    }

    outFile<<"CONSUMER_INFO\n"
           <<q2s(ui->lineEdit->text())<<" "
           <<q2s(ui->lineEdit_2->text())<<" "
           <<q2s(ui->lineEdit_3->text())<<" "
           <<q2s(ui->lineEdit_4->text())<<"\n"
           <<endl;

    outFile<<"SIMULATION_INFO\n"
           <<q2s(ui->lineEdit_28->text())<<" "
           <<q2s(ui->lineEdit_29->text())<<" "
           <<q2s(ui->lineEdit_30->text())<<" "
           <<q2s(ui->lineEdit_31->text())<<"\n"
           <<endl;

    outFile<<"RESTAURANT_INFO\n"
           <<"seatNum "<<q2s(ui->lineEdit_5->text())<<"\n"
           <<"maxFood "<<q2s(ui->lineEdit_6->text())<<"\n"
           <<"hamburger "<<q2s(ui->lineEdit_7->text())<<" "<<q2s(ui->lineEdit_8->text())<<" "<<q2s(ui->lineEdit_9->text())<<"\n"
           <<"chips "<<q2s(ui->lineEdit_10->text())<<" "<<q2s(ui->lineEdit_11->text())<<" "<<q2s(ui->lineEdit_12->text())<<"\n"
           <<"eggTart "<<q2s(ui->lineEdit_13->text())<<" "<<q2s(ui->lineEdit_14->text())<<" "<<q2s(ui->lineEdit_15->text())<<"\n"
           <<"chicken "<<q2s(ui->lineEdit_16->text())<<" "<<q2s(ui->lineEdit_17->text())<<" "<<q2s(ui->lineEdit_18->text())<<"\n"
           <<"juice "<<q2s(ui->lineEdit_19->text())<<" "<<q2s(ui->lineEdit_20->text())<<" "<<q2s(ui->lineEdit_21->text())<<"\n"
           <<"coke "<<q2s(ui->lineEdit_22->text())<<" "<<q2s(ui->lineEdit_23->text())<<" "<<q2s(ui->lineEdit_24->text())<<"\n"
           <<"coffee "<<q2s(ui->lineEdit_25->text())<<" "<<q2s(ui->lineEdit_26->text())<<" "<<q2s(ui->lineEdit_27->text())<<"\n"
           <<endl;

    outFile.close();

    this->close();

}

void setDialog::on_cancelButton_clicked()
{
    this->close();
}
