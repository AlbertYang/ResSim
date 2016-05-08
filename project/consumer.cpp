#include "consumer.h"

#include<cstdlib>
#include<time.h>
#include <ctime>
#include<iostream>
using namespace std;

consumer::consumer(){}

consumer::consumer(double QueueProb, double NoFood, double HasFood, double NoSeat)//��ʼ��
{
    leaveQueueProb = QueueProb;
    leaveNoFood = NoFood;
    leaveHasFood = HasFood;
    leaveNoSeat = NoSeat;

    for(int i=0;i<7;i++)
        food[i]=0;

    eatTime = rand()%11+10; //�Ͳ�ʱ����10~20����
}

bool consumer::leaveQueue(int queue)//���ݶ��鳤���ж��Ƿ��뿪����
{
    int tmp = leaveQueueProb*queue*100;
    int random = rand()%100;
    return random<tmp;
}

void consumer::chooseFood()//ѡ��ʳ��
{
    for(int i=0;i<7;i++)
        food[i]=0;
    int mainFood = rand()%4;
    food[mainFood]++;
    int drink = rand()%3+4;
    food[drink]++; //����һ����ʳ��һ������

    int foodNum = rand()%3; //����������0-2����ʳ
    for(int i=0;i<foodNum;i++){
        int tmpFood = rand()%4;
        food[tmpFood]++;
    }

    int drinkNum = rand()%2; //����������0-1����ʳ
    for(int i=0;i<drinkNum;i++){
        int tmpDrink = rand()%3+4;
        food[tmpDrink]++;
    }
}

int consumer::whenNoFood()//ĳ��ʳ�ﲻ��˿�ѡ��ȴ�����d1��������͸���d2�����͸���d3(Ĭ��0.4/0.2/0.4)��
{
    int random = rand()%100;
    if(random<leaveNoFood*100)
        return 0; //ѡ���뿪
    else{
        int tmp = rand()%2;
        if(tmp==0)
            return 1; //ѡ��ȴ�
        else
            return 2;//ѡ�񻻲�
    }
}

int consumer::isLeaveGetFood(bool noSeat)//������λ���ѡ���Ƿ��뿪
{
    int random = rand()%100;
    if(random<leaveHasFood*100)
        return 1; //�뿪

    if(noSeat){
        random = rand()%100;
        if(random<leaveNoSeat*100)
            return 2;//û����λʱѡ���뿪
        else
            return 3;//û����λʱѡ��ȴ�
    }

    return 0;//����
}

void consumer::waitFood(int nowTime) //��ʼ�ȴ�ʳ���ʱ��
{
    waitForFood = nowTime;
}

void consumer::waitSeat(int nowTime) //��ʼ�ȴ���λ��ʱ��
{
    waitForSeat = nowTime;
}

int consumer::waitFoodTime(int nowTime) //�ȴ�ʳ����ʱ
{
    return nowTime-waitForFood;
}

int consumer::waitSeatTime(int nowTime)//�ȴ���λ��ʱ
{
    return nowTime-waitForSeat;
}

void consumer::startEat(int nowTime) //��ʼ�Ͳ͵�ʱ��
{
    startEating = nowTime;
}

bool consumer::isFinishEat(int nowTime) //�Ƿ�����Ͳ�
{
    return nowTime-startEating==eatTime;
}
