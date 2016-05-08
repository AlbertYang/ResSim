#ifndef RESTAURANT_H
#define RESTAURANT_H

#include<iostream>
#include<vector>
using namespace std;

class restaurant
{
public:
    restaurant();
    restaurant(int seatN,int maxF,double c[],double p[],int q[],double freeMake,double busyMake); //读取文件初始化

    int getSeatNum();//获取座位数量
    void getSells(int get[]);
    void getThrows(int get[]);
    void getProfit(double get[]);

    void throwsFood(int nowTime);//根据时间丢弃过期食物
    void makeFood(int nowTime,int wait[]);//根据时间判断是否制作食物以及制作食物的速度
    bool hasFood(int a[]);//判断是否有足够的食物

private:
    //需要外部读取的变量
    int seatNum;//座位数量
    int maxFood;//每种食物的最大保存量
    double cost[7];//每种食物的成本
    double price[7];//每种食物的价格
    int quality[7];//每种食物的保质期 
    double freeMake;//非高峰时期制作食品的速度
    double busyMake;//高峰时期制作食品的速度

    //自有变量
    int sells[7];//每种食物的售出数量
    int throws[7];//每种食物的丢弃数量
    vector<int> foods[7];//每种食物的现存量即每个食物的生产日期

};

#endif // RESTAURANT_H
