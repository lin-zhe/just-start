#include <iostream>
#include <cstdio>
#include <unistd.h>
#include "CPU.h"
#include "LOG.h"
#include <fstream>
#include <cstdlib>
#include <string>

CPU::CPU(){
   CpuUsage=0.0;
   CpuFileStatus=true;
   Total=0;
   Idle=0;
}

CPU::~CPU(){}
LOG LogC;
const void CPU::GetCpuData(){
    FILE *CpuData =NULL;
    char buff[128];
    unsigned long long int TotalB=0,IdleB=0;                                     //get cpu idle and total time 
    CpuFileStatus=true;
    CpuData =fopen("/proc/stat","r");
    if(CpuData ==NULL) {
      std::cerr<<"error"<<std::endl;
      LogC.ShowTime();
      LogC.FileOpenFail(1);
      FileStatus(false,0);
    }
   for(int i=0;i<11;i++){
        if(i==0){}
           fscanf(CpuData,"%s",buff);
           TotalB +=atoi(buff);
           if(i==4){ IdleB +=atoi(buff);}       
    }
    fclose(CpuData);
    CpuUsage=100-float(IdleB-Idle)/float(TotalB-Total)*100;                                           //formula of computation
    Total=TotalB;
    Idle=IdleB;
}
void CPU::ShowCpuUsage(const std::string & InfoFile){
      std::ofstream fout;
      fout.open(InfoFile.c_str(),std::ios::app|std::ios::out);
      if(!fout.is_open()){
          std::cerr<<"Can't open"<<InfoFile<<"file for output"<<std::endl;
          LogC.ShowTime();
          LogC.FileOpenFail(2);
          FileStatus(false,1);
      }
     std::cout<<"***************************************"<<std::endl;
     std::cout<<"Cpu information list"<<std::endl;
     std::cout<<"**********"<<std::endl;
     fout<<"***************************************"<<std::endl; 
     fout<<"Cpu information list"<<std::endl;
     fout<<"**********"<<std::endl; 
     std::cout<<"Cpu usage:"<<CpuUsage<<"%"<<std::endl;                                                   //show data in teminal and output data into file
     fout<<"Cpu Usage:"<<CpuUsage<<"%"<<std::endl;
     fout.close();
}


void CPU::CpuUsageRank(const std::string & InfoFile,const int & rank){
     int DefauRank=0,DefauRankDec=0,DefauRankUnit=0; 
     std::string TempStoreDataFile="CpuData.txt";
     int FileNameLen;
     char SysCallDataStr[64]={"ps -eo user,pid,%cpu,cmd|sort -k3nr|head -5 >>"};      //"head -5" can change How many process will be sorted by order:ps 
     char SysCallTitleStr[64]={"ps -eo user,pid,%cpu,cmd|head -1 >>"};
     char SysCallClearStr[64]={"echo "" > "};
     std::string ReadData;
     std::ofstream fout;
     CpuFileStatus=true;
     FileNameLen=TempStoreDataFile.size();
     for(int i=0;i<FileNameLen;i++){
          SysCallDataStr[46+i]=TempStoreDataFile[i];
          SysCallTitleStr[35+i]=TempStoreDataFile[i];
          SysCallClearStr[8+i]=TempStoreDataFile[i];
     }
     if(rank!=5){
     DefauRank=rank;
     DefauRankDec=DefauRank/10;
     DefauRankUnit=DefauRank%10;
     SysCallDataStr[42]=DefauRankDec+'0';
     SysCallDataStr[43]=DefauRankUnit+'0';
     }
     system(SysCallTitleStr);
     system(SysCallDataStr);
     std::ifstream CpuData(TempStoreDataFile.c_str());
     fout.open(InfoFile.c_str(),std::ios::app|std::ios::out);
     if(!CpuData.is_open()){
          std::cerr<<"Can't open"<<TempStoreDataFile<<"file for output"<<std::endl;
          LogC.ShowTime();
          LogC.FileOpenFail(10);
          FileStatus(false,0);
     }
     if(!fout.is_open()){
          std::cerr<<"Can't open"<<InfoFile<<"file for output"<<std::endl;
          LogC.ShowTime();
          LogC.FileOpenFail(2);
          FileStatus(false,1);
     }
     fout<<"***************"<<std::endl; 
     fout<<"Cpu usage top "<<rank<<std::endl;
     fout<<"***************"; 
     while(getline(CpuData,ReadData)){
          //std::cout<<ReadData<<std::endl;
          fout<<ReadData<<std::endl;
     }
     system(SysCallClearStr);
     CpuData.close();
     fout.close();
}

void CPU::FileStatus(const bool & Status,const int & Num){
     bool EachFileStatus[2]={true,true};
     for(int i=0;i<2;i++){
          EachFileStatus[Num]=Status;
     }
     CpuFileStatus=EachFileStatus[0]&&EachFileStatus[1];
}

bool CPU::GetFileValue(){
     if(CpuFileStatus==true){return true;}
     if(CpuFileStatus==false){return false;}
}
