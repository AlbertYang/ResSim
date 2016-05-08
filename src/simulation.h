#ifndef SIMULATION_H
#define SIMULATION_H

#include<iostream>
#include<vector>
#include<string>
#include<queue>
#include"consumer.h"
#include"restaurant.h"
using namespace std;

class simulation
{
public:
    simulation(){}
    simulation(const char* filename);
    ~simulation();
    bool isBusy();
    void newConsumers();
    void updateQueue();
    void updateFoodQueue();
    void updateSeatQueue();
    void updateSeats();
    string simulate(int time);//一次模拟过程

private:
    //需要外部获取的数据(顾客)
    double leaveQueueProb; //队伍每增加一人所增加的离开概率
    double leaveNoFood; //没有食物时选择离开的概率
    double leaveHasFood; //获取食物后离开就餐的概率
    double leaveNoSeat; //没有座位时离开的概率
    //需要外部读取的变量（餐厅）
    int seatNum;//座位数量
    int maxFood;//每种食物的最大保存量
    double freeMake;//非高峰时期制作食品的速度
    double busyMake;//高峰时期制作食品的速度
    double cost[7];//每种食物的成本
    double price[7];//每种食物的价格
    int quality[7];//每种食物的保质期
    //需要外部读取的变量（模拟）
    int freeConsumers;//非高峰期每分钟顾客数最大值
    int busyConsumers;//高峰期每分钟的顾客数

    //自有变量
    int nowTime;//当前时间
    int wait[7];//每种食物的当前等待数量
    int waitFoodTime[7];//等待食物所用时间
    int waitSeatTime;//等待座位的时间
    int noFoodCount[7];//无法满足的次数
    int noSeatLeave;//因为没有用餐位离开的顾客数量
    int otherLeave;//因为其他原因离开的顾客数量
    int leaveQueue;//因为队伍过长而离开的顾客数量
    int leaveNoF;//因无法立即获得食物而离开的顾客数
    int waitSeat;//等待座位的人数
    vector<double> freeSeat;//非高峰时段座位利用率
    vector<double> busySeat;//高峰时段座位利用率
    restaurant* shop;
    vector<consumer*> consumerQueue;
    vector<consumer*> waitFoodQueue;
    vector<consumer*> waitSeatQueue;
    vector<consumer*> seats;
};

#endif // SIMULATION_H
