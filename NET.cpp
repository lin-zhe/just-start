#include <iostream>
#include "NET.h"
#include "LOG.h"
#include <fstream>
#include <unistd.h>
#include <cstdlib>
#include <string>
#include <vector>
 
NET::NET(){
    for(int i=0;i<100;i++){
        NetReceSpeed[i]=0;
        NetTranSPeed[i]=0;
        Recekb[i]=0;
        Trankb[i]=0;
    }
    RunFirst=false;
    NetFileStatus=true;  
}

NET::~NET(){

}
LOG LogN;
const void NET::GetNetData(const std::string & InfoFile,const int & Sec){
    char buff[512]; 
    char UserName[64];
    char *LineReturn=NULL;
    int PortNum=0;
    std::ofstream fout;
    NetFileStatus=true;
    fout.open(InfoFile.c_str(),std::ios::app|std::ios::out);
    if(!fout.is_open()){
          std::cerr<<"Can't open"<<InfoFile<<"file for output"<<std::endl;
          LogN.ShowTime();
          LogN.FileOpenFail(2);
          FileStatus(false,0);
     }
    FILE *NetData =fopen("/proc/net/dev","r");
    if(NetData ==NULL) {
          std::cerr<<"error"<<std::endl;
          LogN.ShowTime();
          LogN.FileOpenFail(8);
          FileStatus(false,1);
     }
     while(fgets(buff,sizeof(buff),NetData)){
          PortNum++;
     }
     fseek(NetData,0,SEEK_SET);
     std::vector<long long> ColNetDataB(16*(PortNum-1));
     std::vector<long long> TrankbB(PortNum-2);
     std::vector<long long> RecekbB(PortNum-2);
     std::vector<std::string> SeeName(PortNum-2);
     for(int i=0;i<PortNum;i++){
             LineReturn=fgets(buff,sizeof(buff),NetData);
             if(LineReturn!=NULL&&i>=2){
              sscanf(buff,"%s%lld%lld%lld%lld%lld%lld%lld%lld%lld%lld%lld%lld%lld%lld%lld%lld",UserName,&ColNetDataB[16*(i-2)],&ColNetDataB[16*(i-2)+1],&ColNetDataB[16*(i-2)+2],&ColNetDataB[16*(i-2)+3],
                     &ColNetDataB[16*(i-2)+4],&ColNetDataB[16*(i-2)+5],&ColNetDataB[16*(i-2)+6],&ColNetDataB[16*(i-2)+7],&ColNetDataB[16*(i-2)+8],&ColNetDataB[16*(i-2)+9],
                     &ColNetDataB[16*(i-2)+10],&ColNetDataB[16*(i-2)+11],&ColNetDataB[16*(i-2)+12],&ColNetDataB[16*(i-2)+13],&ColNetDataB[16*(i-2)+14],&ColNetDataB[16*(i-2)+15]);
              SeeName[i-2]=UserName;
             }          
     }
     for(int i=0;i<PortNum-2;i++){
         RecekbB[i]=ColNetDataB[16*i];
         TrankbB[i]=ColNetDataB[16*i+8];
     }
     for(int i=0;i<PortNum-2;i++){
          NetReceSpeed[i]=((RecekbB[i]-Recekb[i])/Sec)/1024;
          NetTranSPeed[i]=((TrankbB[i]-Trankb[i])/Sec)/1024;

      }
     if(RunFirst==false){                                                                //avoid excessive network speed value
          for(int i=0;i<PortNum-2;i++){
          NetReceSpeed[i]=0;
          NetTranSPeed[i]=0;
          }
          RunFirst=true;
      }   
     for(int i=0;i<PortNum-2;i++){
          Recekb[i]=RecekbB[i];
          Trankb[i]=TrankbB[i];
      }
     std::cout<<"***************************************"<<std::endl;
     std::cout<<"Net information list"<<std::endl;
     std::cout<<"*********"<<std::endl;
     std::cout<<"Net speed"<<std::endl;
     std::cout<<"*********"<<std::endl;
     fout<<"***************************************"<<std::endl;
     fout<<"Net information list"<<std::endl;
     fout<<"*********"<<std::endl;
     fout<<"Net speed"<<std::endl;
     fout<<"*********"<<std::endl;   
     std::cout<<"port"<<'\t'<<"Receive"<<'\t'<<"transmit"<<std::endl;
     fout<<"port"<<'\t'<<"Receive"<<'\t'<<"transmit"<<std::endl;
     for(int i=0;i<PortNum-2;i++){
         std::cout<<SeeName[i]<<'\t'<<NetReceSpeed[i]<<"kb/s"<<'\t'<<NetTranSPeed[i]<<"kb/s"<<std::endl;
         fout<<SeeName[i]<<'\t'<<NetReceSpeed[i]<<"kb/s"<<'\t'<<NetTranSPeed[i]<<"kb/s"<<std::endl;
     }
     fclose(NetData);
     fout.close();
  }

  void NET::FileStatus(const bool & Status,const int & Num){
     bool EachFileStatus[3]={true,true};
     for(int i=0;i<3;i++){
          EachFileStatus[Num]=Status;
     }
     NetFileStatus=EachFileStatus[0]&&EachFileStatus[1];
  }

  bool NET::GetFileValue(){
     if(NetFileStatus==true){return true;}
     if(NetFileStatus==false){return false;}
  }

























