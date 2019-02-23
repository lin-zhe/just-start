#include <iostream>
#include <fstream>
#include <cstdlib>
#include <string>
#include <cstring>
#include <queue>
#include "MEM.h"
#include "LOG.h"



MEM::MEM(){
  MemUsageFree=0.0;
  MemUsageAvailable=0.0;
  MemTot=0;
  MemAvail=0;
  MemFileStatus=true;
}


MEM::~MEM(){ }
     LOG LogM;
const void MEM::GetMemData(){
     FILE *MemData=NULL;
     char buff[64];
     char *LineReturn=NULL;
     char NameTemporary[32];
     /*define some constances*/
     const int MemTotalLine =0;
     const int MemFreeLine =1;
     const int MemAvailableLine=2;
     /*--------end-----------*/
     MemFileStatus=true;
     MemData =fopen("/proc/meminfo","r");
     if(MemData ==NULL) {
         std::cerr<<"error"<<std::endl;
         LogM.ShowTime();
         LogM.FileOpenFail(7);
         FileStatus(false,0);
     }
     for(int i=0;i<3;i++){
          LineReturn=fgets(buff,sizeof(buff),MemData);
          if(LineReturn!=NULL){
               if(i==MemTotalLine) {sscanf(buff,"%s%d",NameTemporary,&MemTot);}
               if(i==MemFreeLine) {sscanf(buff,"%s%d",NameTemporary,&MemFree);}
               if(i==MemAvailableLine) {sscanf(buff,"%s%d",NameTemporary,&MemAvail);}
          }
         else{
               if(i==MemTotalLine) {std::cout<<"Read file in"<<i<<" line,error";}
               if(i==MemFreeLine) {std::cout<<"Read file in"<<i<<" line,error";}
               if(i==MemAvailableLine) {std::cout<<"Read file in"<<i<<" line,error";}
               LogM.FileOpenFail(9);
               FileStatus(false,1);
         }
     }
     fclose(MemData);
     MemUsageAvailable=float(MemAvail)/float(MemTot)*100;
     MemUsageFree=float(MemFree)/float(MemTot);
}
void MEM::ShowMemUsage(const std::string & InfoFile){
  std::ofstream fout;
  fout.open(InfoFile.c_str(),std::ios::app|std::ios::out);
  if(!fout.is_open()){
      std::cerr<<"Can't open"<<InfoFile<<"file for output"<<std::endl;
      LogM.ShowTime();
      LogM.FileOpenFail(2);
      FileStatus(false,2);
  }
  std::cout<<"***************************************"<<std::endl;
  std::cout<<"Memory information list"<<std::endl;
  fout<<"***************************************"<<std::endl; 
  fout<<"Memory information list"<<std::endl;
  std::cout<<"************"<<std::endl; 
  std::cout<<"Memory usage"<<std::endl;
  std::cout<<"************"<<std::endl; 
  fout<<"************"<<std::endl;
  fout<<"Memory usage"<<std::endl;
  fout<<"************"<<std::endl;   
  std::cout<<"Now system MEM Usage (Use in Free data):"<<" "
           <<MemUsageFree <<"%"<<std::endl;
  std::cout<<"Now system MEM Usage (Use in Available data):"<< " "
           <<MemUsageAvailable <<"%"<<std::endl;
  fout<<"Now system MEM total have:"<<" "
      << MemTot <<"kb"<<std::endl;
  fout<<"Now system MEM Free have:"<<" "
      << MemFree <<"kb"<<std::endl;
  fout<<"Now system MEM Available have:"<<" "
      << MemAvail<<"kb"<<std::endl;
  fout<<"Now system MEM Usage (Use in Free data):"<<" "
      <<MemUsageFree <<"%"<<std::endl;
  fout<<"Now system MEM Usage (Use in Available data):"<<" "
      <<MemUsageAvailable <<"%"<<std::endl;
  fout.close();
 }

 void MEM::MemUsageRank(const std::string & InfoFile,const int & rank){
     int DefauRank=0,DefauRankDec=0,DefauRankUnit=0;
     std::string TempStoreDataFile="MemData.txt";
     int FileNameLen;   
     char SysCallDataStr[64]={"ps -eo user,pid,%mem,cmd|sort -k3nr|head -5 >>"};      //"head -5" can change How many process will be sorted by "ps' tool
     char SysCallTitleStr[64]={"ps -eo user,pid,%mem,cmd|head -1 >>"};
     char SysCallClearStr[64]={"echo "" > "};
     MemFileStatus=true;
     std::string ReadData;
     std::ofstream fout;
     FileNameLen=TempStoreDataFile.size();  
     for(int i=0;i<FileNameLen;i++){
          SysCallDataStr[46+i]=TempStoreDataFile[i];
          SysCallTitleStr[35+i]=TempStoreDataFile[i];
          SysCallClearStr[8+i]=TempStoreDataFile[i];
     }
     if(rank!=5){                                                                         //5 is the 38th of the string
          DefauRank=rank;                                                                      //5 is default value
          DefauRankDec=DefauRank/10;                                                           //get the rank number
          DefauRankUnit=DefauRank%10;
          SysCallDataStr[42]=DefauRankDec+'0';                                                      //sort range:0-99
          SysCallDataStr[43]=DefauRankUnit+'0';                                                     //int->char
     } 
     system(SysCallTitleStr); 
     system(SysCallDataStr); 
     std::ifstream MemData(TempStoreDataFile.c_str()); 
     fout.open(InfoFile.c_str(),std::ios::app|std::ios::out);
     if(!MemData.is_open()){
        std::cerr<<"Can't open"<<TempStoreDataFile<<"file for output"<<std::endl;
        LogM.ShowTime();
        LogM.FileOpenFail(12);
        FileStatus(false,0);
     }
     if(!fout.is_open()){
          std::cerr<<"Can't open"<<InfoFile<<"file for output"<<std::endl;
          LogM.ShowTime();
          LogM.FileOpenFail(2);
          FileStatus(false,1);
     }
     //std::cout<<"*****"<<std::endl;
     //std::cout<<"Memory usage top "<<rank<<std::endl;
     //std::cout<<"*****";
     fout<<"*****************"<<std::endl; 
     fout<<"Memory usage top "<<rank<<std::endl;
     fout<<"*****************";
     while(getline(MemData,ReadData)){
         // std::cout<<ReadData<<std::endl;
          fout<<ReadData<<std::endl;
     }
     system(SysCallClearStr);
     MemData.close();
     fout.close();
 }

 void MEM::FileStatus(const bool & Status,const int & Num){
     bool EachFileStatus[3]={true,true,true};
     for(int i=0;i<3;i++){
          EachFileStatus[Num]=Status;
     }
     MemFileStatus=EachFileStatus[0]&&EachFileStatus[1];
 }

 bool MEM::GetFileValue(){
     if(MemFileStatus==true){return true;}
     if(MemFileStatus==false){return false;}
 }


