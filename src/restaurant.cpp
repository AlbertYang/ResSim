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

int restaurant::getSeatNum()//获取座位数量
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

void restaurant::makeFood(int nowTime, int wait[])//根据时间判断是否制作食物以及制作食物的速度
{
    int hour = nowTime/60;
    int min = nowTime%60;
    if(hour==6 && min==0){ //开业时储存是满的
        for(int i=0;i<7;i++){
            for(int j=0;j<maxFood;j++){
                foods[i].push_back(nowTime);
            }
        }
    }else if( (hour>=7 && hour<=8) || (hour>=11 && hour<=12) || (hour>=17 && hour<=18) ){//高峰期每分钟做busyMake个
        for(int n=0;n<busyMake;n++){
            for(int i=0;i<7;i++){
                if(foods[i].size()<maxFood)
                    foods[i].push_back(nowTime);
            }
        }
    }else if(min%int(freeMake) == 0){  //非高峰期每freeMake分钟做一个
        for(int i=0;i<7;i++){
            if(foods[i].size()<maxFood)
                foods[i].push_back(nowTime);
        }
    }else{ //如果有人在等待，则每分钟做一个
        for(int i=0;i<7;i++){
            if(wait[i]>0 && foods[i].size()<maxFood)
                foods[i].push_back(nowTime);
        }
    }
}

void restaurant::throwsFood(int nowTime)//根据时间丢弃过期食物
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

bool restaurant::hasFood(int a[])//判断是否有足够的食物
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

