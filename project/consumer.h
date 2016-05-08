#ifndef CONSUMER_H
#define CONSUMER_H

using namespace std;

class consumer
{
public:
    consumer();
    consumer(double QueueProb,double NoFood,double HasFood,double NoSeat);//��ʼ��
    bool leaveQueue(int queue);//���ݶ��鳤���ж��Ƿ��뿪����.
    void chooseFood();//ѡ��ʳ��
    int  whenNoFood();//û��ʳ��ʱѡ��ȴ�����ʳ��뿪
    int isLeaveGetFood(bool noSeat);//������λ���ѡ���Ƿ��뿪.
    void waitFood(int nowTime); //��ʼ�ȴ�ʳ���ʱ��
    void waitSeat(int nowTime); //��ʼ�ȴ���λ��ʱ��.
    int waitFoodTime(int nowTime); //�ȴ�ʳ����ʱ.
    int waitSeatTime(int nowTime);//�ȴ���λ��ʱ.
    void startEat(int nowTime);  //��ʼ�Ͳ͵�ʱ��.
    bool isFinishEat(int nowTime); //�Ƿ�����Ͳ�.

    int food[7];  //ѡ���ʳ��

private:
    int eatTime;  //�Ͳ�����ʱ��
    int startEating;  //��ʼ�Ͳ͵�ʱ��
    int waitForFood; //��ʼ�ȴ�ʳ���ʱ��
    int waitForSeat; //��ʼ�ȴ���λ��ʱ��

    //��Ҫ�ⲿ��ȡ������
    double leaveQueueProb; //����ÿ����һ�������ӵ��뿪����
    double leaveNoFood; //û��ʳ��ʱѡ���뿪�ĸ���
    double leaveHasFood; //��ȡʳ����뿪�Ͳ͵ĸ���
    double leaveNoSeat; //û����λʱ�뿪�ĸ���
};

#endif // CONSUMER_H
