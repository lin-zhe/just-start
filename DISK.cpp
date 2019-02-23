#include <iostream>
#include <string>
#include <fstream>
#include"DISK.h"
#include <cstdlib>
#include "LOG.h"


DISK::DISK(){
    DiskFileStatus=true;

}
DISK::~DISK(){}
LOG LogD;
void DISK::ShowDiskInfo(const std::string & InfoFile){
    std::string TempStoreDataFile="DiskData.txt";
    int  FileNameLen;
    char SysCallClearStr[64]={"echo "" > "};
    char SysCallDiskDataStr[64]=("df -h>");                                                                          //use df tool to view disk data
    std::string ReadData;
    std::ofstream fout;
    DiskFileStatus=true;
    FileNameLen=TempStoreDataFile.size();
    for(int i=0;i<FileNameLen;i++){
          SysCallDiskDataStr[6+i]=TempStoreDataFile[i];
          SysCallClearStr[8+i]=TempStoreDataFile[i];
    }
    system(SysCallDiskDataStr);
    std::ifstream DiskData(TempStoreDataFile.c_str());
    fout.open(InfoFile.c_str(),std::ios::app|std::ios::out);
    if(!fout.is_open()){
       std::cerr<<"Can't open"<<InfoFile<<"file for output"<<std::endl;
       LogD.ShowTime();
       LogD.FileOpenFail(2);
       FileStatus(false,0);
    }
    std::cout<<"***************************************"<<std::endl;
    std::cout<<"Disk information list"<<std::endl;
    fout<<"***************************************"<<std::endl;
    fout<<"Disk information list"<<std::endl;
    std::cout<<"**********"<<std::endl;
    std::cout<<"Disk total"<<std::endl;
    std::cout<<"**********"<<std::endl;
    fout<<"**********"<<std::endl; 
    fout<<"Disk total"<<std::endl;
    fout<<"**********"<<std::endl; 
    while(getline(DiskData,ReadData)){
       std::cout<<ReadData<<std::endl;
       fout<<ReadData<<std::endl;
    }
    system(SysCallClearStr);
    DiskData.close();
    fout.close();
}

void DISK::ShowContentVar(const std::string & InfoFile){
  std::string TempStoreDataFile="DiskData.txt";
  std::string ReadData;
  char SysCalldfForLogStr[64]={"df -h /var/log >"};
  char SysCallClearStr[64]={"echo "" > "};
  int  FileNameLen;
  std::ofstream fout;
  DiskFileStatus=true;
  FileNameLen=TempStoreDataFile.size();
  for(int i=0;i<FileNameLen;i++){
          SysCalldfForLogStr[16+i]=TempStoreDataFile[i];
          SysCallClearStr[8+i]=TempStoreDataFile[i];
  }
  if((system(SysCalldfForLogStr))){
      std::cout<<"open failed"<<std::endl;
      LogD.ShowTime();
      LogD.FileOpenFail(6);
      FileStatus(false,0);
  }
  std::ifstream DiskData(TempStoreDataFile.c_str());
  fout.open(InfoFile.c_str(),std::ios::app|std::ios::out);
  if(!DiskData.is_open()){
          std::cerr<<"Can't open"<<TempStoreDataFile<<"file for output"<<std::endl;
          LogD.ShowTime();
          LogD.FileOpenFail(11);
          FileStatus(false,1);
  }
  if(!fout.is_open()){
    std::cerr<<"Can't open"<<InfoFile<<"file for output"<<std::endl;
    LogD.ShowTime();
    LogD.FileOpenFail(2);
    FileStatus(false,2);
  }
  std::cout<<"********"<<std::endl;
  std::cout<<"/var/log"<<std::endl;
  std::cout<<"********"<<std::endl;
  fout<<"********"<<std::endl; 
  fout<<"/var/log"<<std::endl;
  fout<<"********"<<std::endl; 
  while(getline(DiskData,ReadData)){
       std::cout<<ReadData<<std::endl;
       fout<<ReadData<<std::endl;
  }
  system(SysCallClearStr);
  DiskData.close();
  fout.close();
}
void DISK::ShowContentchronos(const std::string & InfoFile){
  std::string ReadData;
  std::string TempStoreDataFile="DiskData.txt";
  char SysCalldfForChronosStr[64]={"df -h /home/chronos >"};
  char SysCallClearStr[64]={"echo "" > "};
  int  FileNameLen;
  std::ofstream fout;
  DiskFileStatus=true;
  FileNameLen=TempStoreDataFile.size();
  for(int i=0;i<FileNameLen;i++){
          SysCalldfForChronosStr[21+i]=TempStoreDataFile[i];
          SysCallClearStr[8+i]=TempStoreDataFile[i];
   }
  if((system(SysCalldfForChronosStr))){
      std::cout<<"open failed"<<std::endl;
      LogD.ShowTime();
      LogD.FileOpenFail(5);
      FileStatus(false,0);
   }
  std::ifstream DiskData(TempStoreDataFile.c_str());
  fout.open(InfoFile.c_str(),std::ios::app|std::ios::out);
  if(!DiskData.is_open()){
     std::cerr<<"Can't open"<<TempStoreDataFile<<"file for output"<<std::endl;
     LogD.ShowTime();
     LogD.FileOpenFail(11);
     FileStatus(false,1);
  }
  if(!fout.is_open()){
     std::cerr<<"Can't open"<<InfoFile<<"file for output"<<std::endl;
     LogD.ShowTime();
     LogD.FileOpenFail(2);
     FileStatus(false,2);
  }
  std::cout<<"*************"<<std::endl;
  std::cout<<"/home/chronos"<<std::endl;
  std::cout<<"*************"<<std::endl;
  fout<<"*************"<<std::endl; 
  fout<<"/home/chronos"<<std::endl;
  fout<<"*************"<<std::endl; 
  while(getline(DiskData,ReadData)){
        std::cout<<ReadData<<std::endl;
        fout<<ReadData<<std::endl;
  }
  system(SysCallClearStr);
  DiskData.close();
  fout.close();
}

void DISK::FileStatus(const bool & Status,const int & Num){
     bool EachFileStatus[3]={true,true,true};
     for(int i=0;i<3;i++){
          EachFileStatus[Num]=Status;
     }
     DiskFileStatus=EachFileStatus[0]&&EachFileStatus[1];
}

bool DISK::GetFileValue(){
     if(DiskFileStatus==true){return true;}
     if(DiskFileStatus==false){return false;}
}




