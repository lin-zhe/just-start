#include <iostream>
#include <unistd.h>
#include <cstdlib>
#include <string>
#include <cstdio>
#include <fstream>
#include <queue>
#include <getopt.h>
#include "CPU.h"
#include "MEM.h"
#include "NET.h"
#include "DISK.h"
#include "LOG.h"

using namespace std;
const int NumberOfSaveFile=5;
queue <int> StoreLine;
extern char *optarg;
extern int optind,opterr,optopt;

static const struct option longOpts[] ={
    {"timeset",required_argument,NULL,'t'},
    {"output",required_argument,NULL,'o'},
    {"sortprocess",required_argument,NULL,'s'},
    {"help",no_argument,NULL,'h'},
    {NULL,no_argument,NULL,0},
};


std::string EnterOutputFileName(std::string NameNeedChange){
   NameNeedChange +=".txt";
   return NameNeedChange;
}

void HelpInformation(){
   std::cout<<"Usage:  ./code"<< " [--timeset/-t number=value] [--output/-o filename=value] [-s/--sortprocess number=value] [--help/-h]."<<std::endl
            <<"\t"<<"\"--timeset/-t \" mean set the sample time period \"--output/-o \"mean data will store in which file."<<std::endl
            <<"\t"<<"\"-s/--sortprocess \" mean set how many processes will be sorted according to cpu or mem usage."<<std::endl
            <<"\t"<<"You can enter parameters in any order."<<std::endl
            <<"\t"<< "But you can't enter --timeset/-t,--output/-o,-s/--sortprocess" << " without value,for example:--timeset."<<std::endl
            <<"\t"<<"If you don't enter any parameter,it will run with default value: time=5s,filename=outputinformation.txt"
            <<",rank number=5."<<std::endl;
            exit(0);
} 
int TotalLine(const std::string & s,int i){
   std::ifstream Fin(s.c_str());
   std::string ReadD;
   static int e[2]={0,0};
   int CurrentNum=0,AddNum=0;
   while(!Fin.eof()){
      getline(Fin,ReadD);
      CurrentNum++;
   }
   if(i==0){
      e[0]=CurrentNum;
   }
   if(i==1){
      e[1]=CurrentNum;
   }
   AddNum=e[1]-e[0];
   Fin.close();
   return AddNum;
}

int QueueStoreNum(int Line,queue <int> & StoreLine){     
      int ReturnNum=0;
      StoreLine.push(Line);
      if(StoreLine.size()>NumberOfSaveFile){
      ReturnNum=StoreLine.front();
      StoreLine.pop();
      }
      return ReturnNum;
}
void ControlFile(int SkipLine,const std::string & InfoFile){

   ofstream out("temporary.txt");
   ifstream in(InfoFile.c_str());
   int LineCounter=0;
   std::string LineData;
   while(!in.eof()){
      getline(in,LineData);
      if(LineCounter>=SkipLine){
         out<<LineData<<std::endl;
      }
      LineCounter +=1;
   }
   out.close();
   in.close();
}

void GetBack(const std::string & InfoFile){
   ifstream in("temporary.txt");
   ofstream out(InfoFile.c_str(),ios::out);
   std::string LineData;
   while(!in.eof()){
      getline(in,LineData);
      if(LineData.empty()){
         continue;
      }
         out<<LineData<<std::endl;
   }
   out.close();
   in.close();
   system("echo "">temporary.txt");
}

int main(int argc,char *argv[]){
   MEM Mem;
   CPU Cpu;
   DISK Disk;
   NET Net;
   LOG Log;
   int Sec=5;
   int RankNum=5,DeleteLine=0;
   int Line=0;
   int opt=0; ;
   int longIndex=0;
   bool SetFlag=true;
   bool CpuFileUsageStatus=true, CpuFileRankStatus=true;
   bool MemFileUsageStatus=true,MemFileRankStatus=true;
   bool NetFileStatus=true;
   bool DiskFileContentVarStatus=true,DiskFileStatus=true,DiskFileContentChronosStatus=true;
   std::string OutputFileName="outputinformation.txt";
   std::string ParaInfo,ConfigI;
   const char *optstring="o:t:s:h";
   while((opt=getopt_long(argc,argv,optstring,longOpts,&longIndex))!=-1){
      switch(opt){
         case 'o':
              OutputFileName=EnterOutputFileName(optarg);
              break;
         case 't':
              Sec=atoi(optarg);
              break;
         case 'h':
               HelpInformation();
               break;
         case 's':
              RankNum=atoi(optarg);
              break;
         case '?':
              SetFlag=false;
              break;
         case ':':
              SetFlag=false;
              break;
          default:
              break;
      }
   }

    if(Sec<=1||Sec>=1000){                                                                            //Limit the time of Data sampling period
        std::cout<<"Set time is too short or too long or you enter a string"<<std::endl;
        SetFlag=false;
    }
    while(SetFlag==true){
       if(StoreLine.size()==0){
          system("clear");
       }
       if(StoreLine.size()>=1){
       Line=TotalLine(OutputFileName,0);
       }
       std::cout<<"Data collect period is "<<Sec<<" second"<<std::endl;
       std::cout<<"information will show in: "<<OutputFileName<<std::endl;
       std::cout<<"the number of processes will be sorted: "<<RankNum<<std::endl;
      if(CpuFileUsageStatus==true){                                                          
         Cpu.GetCpuData();
         Cpu.ShowCpuUsage(OutputFileName);
         CpuFileUsageStatus=Cpu.GetFileValue();
      }
      if(CpuFileRankStatus==true){
         Cpu.CpuUsageRank(OutputFileName,RankNum);
         CpuFileRankStatus=Cpu.GetFileValue();
      }
      if(MemFileUsageStatus==true){
         Mem.GetMemData();
         Mem.ShowMemUsage(OutputFileName);
         MemFileUsageStatus=Mem.GetFileValue();
      }
      if((MemFileRankStatus==true)){
         Mem.MemUsageRank(OutputFileName,RankNum);
         MemFileRankStatus=Mem.GetFileValue();
      }
      if(DiskFileStatus==true){
         Disk.ShowDiskInfo(OutputFileName);
         DiskFileStatus=Disk.GetFileValue();
      }
      if(DiskFileContentVarStatus==true){
         Disk.ShowContentVar(OutputFileName);
         DiskFileContentVarStatus=Disk.GetFileValue();
      }
      if(DiskFileContentChronosStatus==true){
         Disk.ShowContentchronos(OutputFileName);
         DiskFileContentChronosStatus=Disk.GetFileValue();
      }
      if(NetFileStatus==true){
         Net.GetNetData(OutputFileName,Sec);
         NetFileStatus=Net.GetFileValue();
      }  
      Log.TimeShowData(OutputFileName);
      Line=TotalLine(OutputFileName,1); 
      DeleteLine=QueueStoreNum(Line,StoreLine);
      if(StoreLine.size()>=NumberOfSaveFile){ 
         ControlFile(DeleteLine,OutputFileName);
         GetBack(OutputFileName);
      }
      for(int i=0;i<70;i++){
          printf("\033[1A");
          printf("\033[K");
      }
      sleep(Sec); 
   }
   if(SetFlag==false){
       for(int i=0;i<argc;i++){                                                                      //if enter wrong order print order and exit
           cout<<argv[i]<<" ";
       }
       std::cout<<"is not a order"<<std::endl;
       std::cout<<"you can enter ./code --help to see how to enter command line"<<std::endl;
   }
   return 0;
}



