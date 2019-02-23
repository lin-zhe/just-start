#ifndef LOG_H
#define LOG_H



class LOG{


public:
   LOG();
   ~LOG();
   std::string ShowTime();
   void OrderSuccess();
   void FileOpenFail(const int & DistunguishModule);
   void TimeShowData(const std::string & FileInfo);
};



#endif // LOG_H_INCLUDED
