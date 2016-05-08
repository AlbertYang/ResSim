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
    string simulate(int time);//һ��ģ�����

private:
    //��Ҫ�ⲿ��ȡ������(�˿�)
    double leaveQueueProb; //����ÿ����һ�������ӵ��뿪����
    double leaveNoFood; //û��ʳ��ʱѡ���뿪�ĸ���
    double leaveHasFood; //��ȡʳ����뿪�Ͳ͵ĸ���
    double leaveNoSeat; //û����λʱ�뿪�ĸ���
    //��Ҫ�ⲿ��ȡ�ı�����������
    int seatNum;//��λ����
    int maxFood;//ÿ��ʳ�����󱣴���
    double freeMake;//�Ǹ߷�ʱ������ʳƷ���ٶ�
    double busyMake;//�߷�ʱ������ʳƷ���ٶ�
    double cost[7];//ÿ��ʳ��ĳɱ�
    double price[7];//ÿ��ʳ��ļ۸�
    int quality[7];//ÿ��ʳ��ı�����
    //��Ҫ�ⲿ��ȡ�ı�����ģ�⣩
    int freeConsumers;//�Ǹ߷���ÿ���ӹ˿������ֵ
    int busyConsumers;//�߷���ÿ���ӵĹ˿���

    //���б���
    int nowTime;//��ǰʱ��
    int wait[7];//ÿ��ʳ��ĵ�ǰ�ȴ�����
    int waitFoodTime[7];//�ȴ�ʳ������ʱ��
    int waitSeatTime;//�ȴ���λ��ʱ��
    int noFoodCount[7];//�޷�����Ĵ���
    int noSeatLeave;//��Ϊû���ò�λ�뿪�Ĺ˿�����
    int otherLeave;//��Ϊ����ԭ���뿪�Ĺ˿�����
    int leaveQueue;//��Ϊ����������뿪�Ĺ˿�����
    int leaveNoF;//���޷��������ʳ����뿪�Ĺ˿���
    int waitSeat;//�ȴ���λ������
    vector<double> freeSeat;//�Ǹ߷�ʱ����λ������
    vector<double> busySeat;//�߷�ʱ����λ������
    restaurant* shop;
    vector<consumer*> consumerQueue;
    vector<consumer*> waitFoodQueue;
    vector<consumer*> waitSeatQueue;
    vector<consumer*> seats;
};

#endif // SIMULATION_H
