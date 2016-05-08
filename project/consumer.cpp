#include "consumer.h"

#include<cstdlib>
#include<time.h>
#include <ctime>
#include<iostream>
using namespace std;

consumer::consumer(){}

consumer::consumer(double QueueProb, double NoFood, double HasFood, double NoSeat)//初始化
{
    leaveQueueProb = QueueProb;
    leaveNoFood = NoFood;
    leaveHasFood = HasFood;
    leaveNoSeat = NoSeat;

    for(int i=0;i<7;i++)
        food[i]=0;

    eatTime = rand()%11+10; //就餐时间是10~20分钟
}

bool consumer::leaveQueue(int queue)//根据队伍长度判断是否离开队伍
{
    int tmp = leaveQueueProb*queue*100;
    int random = rand()%100;
    return random<tmp;
}

void consumer::chooseFood()//选择食物
{
    for(int i=0;i<7;i++)
        food[i]=0;
    int mainFood = rand()%4;
    food[mainFood]++;
    int drink = rand()%3+4;
    food[drink]++; //至少一种主食、一种饮料

    int foodNum = rand()%3; //还可以再买0-2个主食
    for(int i=0;i<foodNum;i++){
        int tmpFood = rand()%4;
        food[tmpFood]++;
    }

    int drinkNum = rand()%2; //还可以再买0-1个主食
    for(int i=0;i<drinkNum;i++){
        int tmpDrink = rand()%3+4;
        food[tmpDrink]++;
    }
}

int consumer::whenNoFood()//某种食物不足顾客选择等待概率d1，放弃点餐概率d2，换餐概率d3(默认0.4/0.2/0.4)，
{
    int random = rand()%100;
    if(random<leaveNoFood*100)
        return 0; //选择离开
    else{
        int tmp = rand()%2;
        if(tmp==0)
            return 1; //选择等待
        else
            return 2;//选择换餐
    }
}

int consumer::isLeaveGetFood(bool noSeat)//根据座位情况选择是否离开
{
    int random = rand()%100;
    if(random<leaveHasFood*100)
        return 1; //离开

    if(noSeat){
        random = rand()%100;
        if(random<leaveNoSeat*100)
            return 2;//没有座位时选择离开
        else
            return 3;//没有座位时选择等待
    }

    return 0;//就坐
}

void consumer::waitFood(int nowTime) //开始等待食物的时间
{
    waitForFood = nowTime;
}

void consumer::waitSeat(int nowTime) //开始等待座位的时间
{
    waitForSeat = nowTime;
}

int consumer::waitFoodTime(int nowTime) //等待食物用时
{
    return nowTime-waitForFood;
}

int consumer::waitSeatTime(int nowTime)//等待座位用时
{
    return nowTime-waitForSeat;
}

void consumer::startEat(int nowTime) //开始就餐的时间
{
    startEating = nowTime;
}

bool consumer::isFinishEat(int nowTime) //是否结束就餐
{
    return nowTime-startEating==eatTime;
}
