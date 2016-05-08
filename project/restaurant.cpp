#include "restaurant.h"
#include<iostream>
#include<vector>
using namespace std;

restaurant::restaurant(){}

restaurant::restaurant(int seatN,int maxF,double c[],double p[],int q[],double f,double b)
{
    seatNum = seatN;
    maxFood = maxF;
    freeMake = f;
    busyMake = b;
    for(int i=0;i<7;i++){
        cost[i] = c[i];
        price[i] = p[i];
        quality[i] = q[i];
        sells[i]=0;
        throws[i]=0;
    }
}

int restaurant::getSeatNum()//��ȡ��λ����
{
    return seatNum;
}

void restaurant::getSells(int get[])
{
    for(int i=0;i<7;i++)
        get[i] = sells[i];
}

void restaurant::getThrows(int get[])
{
    for(int i=0;i<7;i++)
        get[i] = throws[i];
}
void restaurant::getProfit(double get[])
{
    for(int i=0;i<7;i++)
        get[i] = sells[i]*price[i]-(sells[i]+throws[i])*cost[i];
}

void restaurant::makeFood(int nowTime, int wait[])//����ʱ���ж��Ƿ�����ʳ���Լ�����ʳ����ٶ�
{
    int hour = nowTime/60;
    int min = nowTime%60;
    if(hour==6 && min==0){ //��ҵʱ����������
        for(int i=0;i<7;i++){
            for(int j=0;j<maxFood;j++){
                foods[i].push_back(nowTime);
            }
        }
    }else if( (hour>=7 && hour<=8) || (hour>=11 && hour<=12) || (hour>=17 && hour<=18) ){//�߷���ÿ������busyMake��
        for(int n=0;n<busyMake;n++){
            for(int i=0;i<7;i++){
                if(foods[i].size()<maxFood)
                    foods[i].push_back(nowTime);
            }
        }
    }else if(min%int(freeMake) == 0){  //�Ǹ߷���ÿfreeMake������һ��
        for(int i=0;i<7;i++){
            if(foods[i].size()<maxFood)
                foods[i].push_back(nowTime);
        }
    }else{ //��������ڵȴ�����ÿ������һ��
        for(int i=0;i<7;i++){
            if(wait[i]>0 && foods[i].size()<maxFood)
                foods[i].push_back(nowTime);
        }
    }
}

void restaurant::throwsFood(int nowTime)//����ʱ�䶪������ʳ��
{
    for(int i=0;i<7;i++){
        for(vector<int>::iterator vi=foods[i].begin();vi!=foods[i].end();){
            if(nowTime-(*vi)==quality[i]){
                vi = foods[i].erase(vi);
                throws[i]++;
            }
            else
                ++vi;
        }
    }
}

bool restaurant::hasFood(int a[])//�ж��Ƿ����㹻��ʳ��
{
    for(int i=0;i<7;i++){
        if(a[i]>foods[i].size())
            return false;
    }

    for(int i=0;i<7;i++){
        for(int j=0;j<a[i];j++){
            foods[i].erase(foods[i].begin());
            sells[i]++;
        }
    }


    return true;
}

