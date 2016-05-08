#include "simulation.h"
#include"consumer.h"
#include"restaurant.h"
#include<iostream>
#include<sstream>
#include<fstream>
#include<vector>
#include<string>
#include<queue>
#include<cstdlib>
using namespace std;

simulation::simulation(const char *filename)
{
    for(int i=0;i<7;i++){
        noFoodCount[i]=0;
        waitFoodTime[i]=0;
        wait[i]=0;
    }
    waitSeatTime=0;
    noSeatLeave=0;
    otherLeave=0;
    leaveQueue=0;
    leaveNoF=0;
    waitSeat=0;

    ifstream infile;
    infile.open(filename);

    string tmpLine;
    while(getline(infile,tmpLine)){
        if(tmpLine=="CONSUMER_INFO"){
            getline(infile,tmpLine);
            istringstream istring(tmpLine);
            string tmp[4];
            istring>>tmp[0]>>tmp[1]>>tmp[2]>>tmp[3];
            leaveQueueProb = atof(tmp[0].c_str());
            leaveNoFood = atof(tmp[1].c_str());
            leaveHasFood = atof(tmp[2].c_str());
            leaveNoSeat = atof(tmp[3].c_str());
        }

        if(tmpLine=="SIMULATION_INFO"){
            getline(infile,tmpLine);
            istringstream istring(tmpLine);
            string tmp[4];
            istring>>tmp[0]>>tmp[1]>>tmp[2]>>tmp[3];
            freeConsumers = atoi(tmp[0].c_str());
            busyConsumers = atoi(tmp[1].c_str());
            freeMake = atof(tmp[2].c_str());
            busyMake = atof(tmp[3].c_str());
        }

        if(tmpLine=="RESTAURANT_INFO"){
            string temp;

            string tmp[2];
            getline(infile,tmpLine);
            istringstream istring(tmpLine);
            istring>>temp>>tmp[0];
            getline(infile,tmpLine);
            istringstream istring2(tmpLine);
            istring2>>temp>>tmp[1];
            seatNum = atoi(tmp[0].c_str());
            maxFood = atoi(tmp[1].c_str());

            string tmp2[7][3];
            for(int i=0;i<7;i++){
                getline(infile,tmpLine);
                istringstream istring(tmpLine);
                istring>>temp>>tmp2[i][0]>>tmp2[i][1]>>tmp2[i][2];
                cost[i] = atof(tmp2[i][0].c_str());
                price[i] = atof(tmp2[i][1].c_str());
                quality[i] = atof(tmp2[i][2].c_str());
//cout<<cost[i]<<"　"<<price[i]<<" "<<quality[i]<<endl;
            }
        }
    }
    infile.close();

    shop = new restaurant(seatNum,maxFood,cost,price,quality,freeMake,busyMake);

}
simulation::~simulation()
{
    delete shop;
}

bool simulation::isBusy()
{
    int hour = nowTime/60;
    if( (hour>=7 && hour<=8) || (hour>=11 && hour<=12) || (hour>=17 && hour<=18) )
        return true;
    else
        return false;
}

void simulation::newConsumers(){
    if(isBusy()){
        for(int i=0;i<busyConsumers;i++){
            consumer* tmpConsumer = new consumer(leaveQueueProb,leaveNoFood,leaveHasFood,leaveNoSeat);
            if(tmpConsumer->leaveQueue(consumerQueue.size())){//根据队伍长度判断是否离开，如果不需要，可将接下来三行注释掉。
                delete tmpConsumer;
                leaveQueue++;
            }else
                consumerQueue.push_back(tmpConsumer);
        }
    }else{
        int tmpRand = rand()%(freeConsumers+1);
        for(int i=0;i<tmpRand;i++){
            consumer* tmpConsumer = new consumer(leaveQueueProb,leaveNoFood,leaveHasFood,leaveNoSeat);
            if(tmpConsumer->leaveQueue(consumerQueue.size())){//根据队伍长度判断是否离开，如果不需要，可将接下来三行注释掉。
                delete tmpConsumer;
                leaveQueue++;
            }else
                consumerQueue.push_back(tmpConsumer);
        }
    }
}

void simulation::updateQueue(){}

void simulation::updateFoodQueue(){
    if(waitFoodQueue.size()==0)
        return;
    for(vector<consumer*>::iterator vi=waitFoodQueue.begin();vi!=waitFoodQueue.end();){
        bool hasfood = shop->hasFood((*vi)->food);
        if(hasfood){
            int tmp=(*vi)->waitFoodTime(nowTime);
            for(int i=0;i<7;i++){
                if((*vi)->food[i]>0){
                    waitFoodTime[i]+=tmp;
                    wait[i]-=(*vi)->food[i];
                }
            }
            bool noSeat = (seats.size()==seatNum);
            int choice = (*vi)->isLeaveGetFood(noSeat);
            if(choice==1){
                delete (*vi);
                otherLeave++;
            }else if(choice==3){
                (*vi)->waitSeat(nowTime);
                waitSeatQueue.push_back((*vi));
            }else if(choice==0){
                (*vi)->startEat(nowTime);
                seats.push_back((*vi));
            }else{
                delete (*vi);
                cout<<"uhu\n";
                noSeatLeave++;
            }
            vi = waitFoodQueue.erase(vi);
        }else
            ++vi;
    }
}

void simulation::updateSeatQueue(){
    int tmp = seatNum-seats.size();
    for(int i=0;i<tmp;i++){
        if(waitSeatQueue.size()==0)
            break;
        vector<consumer*>::iterator vi=waitSeatQueue.begin();
        (*vi)->startEat(nowTime);
        seats.push_back((*vi));
        int tmp = (*vi)->waitSeatTime(nowTime);
        waitSeatTime+=tmp;
        waitSeat++;
        waitSeatQueue.erase(vi);
    }
}

void simulation::updateSeats(){
    for(vector<consumer*>::iterator vi=seats.begin();vi!=seats.end();){
        bool finish = (*vi)->isFinishEat(nowTime);
        if(finish){
            delete(*vi);
            seats.erase(vi);
        }else
            ++vi;
    }
}

string simulation::simulate(int time){
    nowTime = time;

    shop->throwsFood(nowTime);
    shop->makeFood(nowTime,wait);
    updateFoodQueue();
    updateSeatQueue();
    updateSeats();

    newConsumers();
    if(consumerQueue.size()>0){
        vector<consumer*>::iterator vi=consumerQueue.begin();
        consumer* firstConsumer = *vi;
        consumerQueue.erase(vi);
        choose:
        firstConsumer->chooseFood();
        bool hasfood = shop->hasFood(firstConsumer->food);


        if(hasfood){
            bool noSeat = (seats.size()==seatNum);
            int choice = (firstConsumer->isLeaveGetFood(noSeat));
            if(choice==1){
                delete firstConsumer;
                otherLeave++;
            }else if(choice==3){
                firstConsumer->waitSeat(nowTime);
                waitSeatQueue.push_back(firstConsumer);
            }else if(choice==0){
                firstConsumer->startEat(nowTime);
                seats.push_back(firstConsumer);
            }else{
                delete firstConsumer;
                noSeatLeave++;
            }
        }else{
            int tmp = firstConsumer->whenNoFood();
            if(tmp==0){
                delete firstConsumer;
                leaveNoF++;
            }else if(tmp==1){
                firstConsumer->waitFood(nowTime);
                waitFoodQueue.push_back(firstConsumer);
                for(int i=0;i<7;i++){
                    wait[i]+=firstConsumer->food[i];
                    if(firstConsumer->food[i]>0)
                        noFoodCount[i]++;
                }
            }else{
                goto choose;
            }
        }
    }

    if(isBusy()){//若为高峰时段，则计算此时座位利用率
        double tmp = double(seats.size())/double(seatNum);
        busySeat.push_back(tmp);
    }else{
        double tmp = double(seats.size())/double(seatNum);
        freeSeat.push_back(tmp);
    }

    string foodName[7]={"汉堡","薯条","蛋挞","鸡块","橙汁","可乐","咖啡"};
    int hour = nowTime/60;
    int min = nowTime%60;
    if(hour==23 && min==0){
        ostringstream ostring;
        int tmp[7];

        shop->getSells(tmp);
        ostring<<"销售数量："<<endl;
        for(int i=0;i<7;i++)
            ostring<<foodName[i]<<tmp[i]<<" ";
        ostring<<endl<<endl;

        shop->getThrows(tmp);
        ostring<<"丢弃数量："<<endl;
        for(int i=0;i<7;i++)
            ostring<<foodName[i]<<tmp[i]<<" ";
        ostring<<endl<<endl;

        double tmp2[7];
        shop->getProfit(tmp2);
        double totalProfit=0.0;
        ostring<<"利润（元）："<<endl;
        for(int i=0;i<7;i++){
            ostring<<foodName[i]<<tmp2[i]<<" ";
            totalProfit+=tmp2[i];
        }
        ostring<<endl<<endl;

        ostring<<"总利润（元）："<<totalProfit<<endl<<endl;

        ostring<<"因没有用餐位离开的总人数："<<noSeatLeave<<endl<<endl;
        ostring<<"因队伍太长而离开的总人数："<<leaveQueue<<endl<<endl;
        ostring<<"因无法立即获得食物而离开的总人数："<<leaveNoF<<endl<<endl;
        ostring<<"因其他原因离开的总人数："<<otherLeave<<endl<<endl;
        if(waitSeatTime!=0)
            ostring<<"顾客等待用餐位置的时间（分钟/人）："<<double(waitSeatTime)/double(waitSeat)<<endl<<endl;
        else
            ostring<<"顾客等待用餐位置的时间（分钟/人）："<<0<<endl<<endl;

        ostring<<"顾客等待食物的总时间（分钟）："<<endl;
        for(int i=0;i<7;i++)
            ostring<<foodName[i]<<waitFoodTime[i]<<" ";
        ostring<<endl<<endl;

        ostring<<"每种食物不能满足顾客点餐要求的次数："<<endl;
        for(int i=0;i<7;i++)
            ostring<<foodName[i]<<noFoodCount[i]<<" ";
        ostring<<endl<<endl;

        double temp = 0.0;
        for(int i=0;i<freeSeat.size();i++){
            temp+=freeSeat[i];
        }
        ostring<<"非高峰时段座位利用率："<<temp/freeSeat.size()<<endl<<endl;

        temp = 0.0;
        for(int i=0;i<busySeat.size();i++){
            temp+=busySeat[i];
        }
        ostring<<"高峰时段座位利用率："<<temp/busySeat.size()<<endl<<endl;

        return ostring.str();

    }else
       return "";
}
