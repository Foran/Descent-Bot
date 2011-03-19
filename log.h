#ifndef __LOG_H__
#define __LOG_H__

#include <string>
#include <vector>
#include <map>
#include <iostream>

using namespace std;

#include "log_driver.h"

class CLog_Chain 
{
 public:
   CLog_Chain(const LogType type);
   ~CLog_Chain();
   
   LogType get_Type() const;
   
   void add_Logger(iLogDriver *log_driver);
   void Write(int level, const string &message);
 protected:
 private:
     vector<iLogDriver *> mDrivers;
   LogType mType;

   CLog_Chain();
   CLog_Chain(const CLog_Chain &source);
   CLog_Chain &operator=(const CLog_Chain &source);
};

class CLog 
{
 public:
   CLog();
   ~CLog();
   
   void add_Logger(const LogType type, iLogDriver *log_driver);
   void Write(const LogType type, int level, const string &message);
 protected:
 private:
   map<LogType, CLog_Chain *> mChains;
   
   CLog(const CLog &source);
   void operator=(const CLog &source);
};

extern CLog global_Log;

#endif
