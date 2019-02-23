#ifndef DISK_H_
#define DISK_H_



class DISK{
private:
   bool DiskFileStatus;       
   //int FileLineNum;                                                          
public:
   DISK();
   ~DISK();
  void ShowDiskInfo(const std::string & InfoFile);
  void ShowContentVar(const std::string & InfoFile);
  void ShowContentchronos(const std::string & InfoFile);
  void FileStatus(const bool & Status,const int & Num);
  bool GetFileValue();
};


#endif // DISK_INFO_H_INCLUDED
