#ifndef CONSUMER_H
#define CONSUMER_H

using namespace std;

class consumer
{
public:
    consumer();
    consumer(double QueueProb,double NoFood,double HasFood,double NoSeat);//初始化
    bool leaveQueue(int queue);//根据队伍长度判断是否离开队伍.
    void chooseFood();//选择食物
    int  whenNoFood();//没有食物时选择等待、换食物、离开
    int isLeaveGetFood(bool noSeat);//根据座位情况选择是否离开.
    void waitFood(int nowTime); //开始等待食物的时间
    void waitSeat(int nowTime); //开始等待座位的时间.
    int waitFoodTime(int nowTime); //等待食物用时.
    int waitSeatTime(int nowTime);//等待座位用时.
    void startEat(int nowTime);  //开始就餐的时间.
    bool isFinishEat(int nowTime); //是否结束就餐.

    int food[7];  //选择的食物

private:
    int eatTime;  //就餐所需时间
    int startEating;  //开始就餐的时间
    int waitForFood; //开始等待食物的时间
    int waitForSeat; //开始等待座位的时间

    //需要外部获取的数据
    double leaveQueueProb; //队伍每增加一人所增加的离开概率
    double leaveNoFood; //没有食物时选择离开的概率
    double leaveHasFood; //获取食物后离开就餐的概率
    double leaveNoSeat; //没有座位时离开的概率
};

#endif // CONSUMER_H
