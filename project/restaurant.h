#ifndef RESTAURANT_H
#define RESTAURANT_H

#include<iostream>
#include<vector>
using namespace std;

class restaurant
{
public:
    restaurant();
    restaurant(int seatN,int maxF,double c[],double p[],int q[],double freeMake,double busyMake); //��ȡ�ļ���ʼ��

    int getSeatNum();//��ȡ��λ����
    void getSells(int get[]);
    void getThrows(int get[]);
    void getProfit(double get[]);

    void throwsFood(int nowTime);//����ʱ�䶪������ʳ��
    void makeFood(int nowTime,int wait[]);//����ʱ���ж��Ƿ�����ʳ���Լ�����ʳ����ٶ�
    bool hasFood(int a[]);//�ж��Ƿ����㹻��ʳ��

private:
    //��Ҫ�ⲿ��ȡ�ı���
    int seatNum;//��λ����
    int maxFood;//ÿ��ʳ�����󱣴���
    double cost[7];//ÿ��ʳ��ĳɱ�
    double price[7];//ÿ��ʳ��ļ۸�
    int quality[7];//ÿ��ʳ��ı����� 
    double freeMake;//�Ǹ߷�ʱ������ʳƷ���ٶ�
    double busyMake;//�߷�ʱ������ʳƷ���ٶ�

    //���б���
    int sells[7];//ÿ��ʳ����۳�����
    int throws[7];//ÿ��ʳ��Ķ�������
    vector<int> foods[7];//ÿ��ʳ����ִ�����ÿ��ʳ�����������

};

#endif // RESTAURANT_H
