#ifndef MEM_H_
#define MEM_H_



class MEM{
private:
    float MemUsageFree;
    float MemUsageAvailable;
    int MemTot;
    int MemFree;
    int MemAvail;
    bool MemFileStatus;
    int FileLineNum;
public:
    MEM();
    ~MEM();
    const void GetMemData();
    void ShowMemUsage(const std::string & InfoFile);
    void MemUsageRank(const std::string & InfoFile,const int & rank);
    void FileStatus(const bool & Status,const int & Num);
    bool GetFileValue();
};


#endif // MEM_INFO_H_INCLUDED
