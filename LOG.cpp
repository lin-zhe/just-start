#include <iostream>
#include <ctime>
#include <fstream>
#include <string>
#include "LOG.h"



LOG::LOG(){};
LOG::~LOG(){};


std::string LOG::ShowTime(){

  time_t Ttime;
  std::string StrFormat ="%Y-%m-%d %H:%M:%S";
  char StrDateTime[30]={'\0'};
  time(&Ttime);
  tm* TlocalTime =localtime(&Ttime);
  strftime(StrDateTime,30,StrFormat.c_str(),TlocalTime);
  std::string StrRes =StrDateTime;
  return StrRes;
}

void LOG::FileOpenFail(const int & DistingushModule){
    std::ofstream LogFout;
    std::string NowTime=ShowTime();
    LogFout.open("toolsys",std::ios::app|std::ios::out);
    LogFout<<NowTime<<"  ";
    if(DistingushModule==1){LogFout<<"/proc/stat open fail"<<std::endl;}
    if(DistingushModule==2){LogFout<<"file for output system information open fail"<<std::endl;}
    if(DistingushModule==3){LogFout<<"file for output CpuUsageRank fail"<<std::endl;}
    if(DistingushModule==4){LogFout<<"system call for df tool or create disk_data.txt file fail"<<std::endl;}
    if(DistingushModule==5){LogFout<<"system call for df tool or /home/chronos index not exist or create ContentOfDisk.txt fail"<<std::endl;}
    if(DistingushModule==6){LogFout<<"system call for df tool or /var/log index not exist or create ContentOfDisk.txt fail"<<std::endl;}
    if(DistingushModule==7){LogFout<<"/proc/meminfo open fail"<<std::endl;}
    if(DistingushModule==8){LogFout<<"/proc/net/dev open fail"<<std::endl;}
    if(DistingushModule==9){LogFout<<"Read data fail"<<std::endl;}
    if(DistingushModule==10){LogFout<<"temporary file in cpu open fail"<<std::endl;}
    if(DistingushModule==11){LogFout<<"temporary file in disk open fail"<<std::endl;}
    if(DistingushModule==12){LogFout<<"temporary file in memory open fail"<<std::endl;}
    LogFout.close();
}

void LOG::TimeShowData(const std::string & InfoFile){
    std::ofstream fout;
    std::string NowTime;
    NowTime=ShowTime();
    fout.open(InfoFile.c_str(),std::ios::app|std::ios::out);
    std::cout<<"***************************************"<<std::endl;
    std::cout<<"Record time:"<<std::endl;
    fout<<"***************************************"<<std::endl;
    fout<<"Record time"<<std::endl;
    std::cout<<NowTime<<std::endl;
    fout<<NowTime<<std::endl;
    fout<<"************************************************************"
        <<"*************************************************************"
        <<"*************************************************************"<<std::endl;
    fout.close();
}
