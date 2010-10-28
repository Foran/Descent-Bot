#ifndef __LOG_H__
#define __LOG_H__

#include <string>
#include <vector>

#include "log_driver.h"

class CLog 
{
 public:
   CLog();
   ~CLog();
   
   void add_Logger(const LogType type, iLogDriver *log_driver);
   void Write(const LogType type, int level, const string &message);
 protected:
 private:
   vector<vector<iLogDriver *> > mDrivers;
   
   CLog(const CLog &source);
   void operator=(const CLog &source);
};

extern CLog global_Log;

#endif
