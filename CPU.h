#ifndef CPU_H_
#define CPU_H_


class CPU{
private:

    float CpuUsage;
    bool CpuFileStatus;
    unsigned long long int Total,Idle;
public:
    CPU();
    ~CPU();
    const void GetCpuData();
    void ShowCpuUsage(const std::string & InfoFile);
    void CpuUsageRank(const std::string & InfoFile,const int & rank);
    void FileStatus(const bool & Status,const int & Num);
    bool GetFileValue();
};

#endif
