#ifndef NET_H_
#define NET_H_

class NET{
private:
    double NetReceSpeed[100];
    double NetTranSPeed[100];
    long long Recekb[100];
    long long Trankb[100];
    bool NetFileStatus;
    bool RunFirst;

public:
    NET();
    ~NET();
    const void GetNetData(const std::string & InfoFile,const int & Sec);
    void FileStatus(const bool & Status,const int & Num);
    bool GetFileValue();

};
#endif // NET_H_INCLUDED
