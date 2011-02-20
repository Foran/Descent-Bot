#include "log.h"

CLog global_Log;

CLog::CLog()
{
   mDrivers.resize(10);
}

CLog::~CLog() 
{
   for(vector<vector<iLogDriver *> >::iterator j = mDrivers.begin(); j != mDrivers.end(); j++) {
      for(vector<iLogDriver *>::iterator k = j->begin(); k != j->end(); k++) {
	 delete *k;
      }
      j->clear();
   }
}

void CLog::add_Logger(const LogType type, iLogDriver *log_driver)
{
   if(log_driver) mDrivers[static_cast<int>(type)].push_back(log_driver);
}

void CLog::Write(const LogType type, int level, const string &message)
{
   for(vector<iLogDriver *>::iterator i = mDrivers[static_cast<int>(type)].begin(); i != mDrivers[static_cast<int>(type)].end(); i++) {
      if(level <= 200) dynamic_cast<iLogDriver *>(*i)->Write(type, level, message);
   }
}
