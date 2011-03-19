#include "log.h"

CLog global_Log;

CLog_Chain::CLog_Chain(const LogType type)
{
   mType = type;
}

CLog_Chain::~CLog_Chain()
{
   for(vector<iLogDriver *>::iterator i = mDrivers.begin(); i != mDrivers.end(); i++) {
      delete *i;
   }
}

LogType CLog_Chain::get_Type() const
{
   return mType;
}

void CLog_Chain::add_Logger(iLogDriver *log_driver)
{
   if(log_driver) mDrivers.push_back(log_driver);
}

void CLog_Chain::Write(int level, const string &message){
   for(vector<iLogDriver *>::iterator i = mDrivers.begin(); i != mDrivers.end(); i++) {
      if(level <= 100) dynamic_cast<iLogDriver *>(*i)->Write(mType, level, message);
   }
}

CLog::CLog()
{
}

CLog::~CLog() 
{
   for(map<LogType, CLog_Chain *>::iterator j = mChains.begin(); j != mChains.end(); j++) {
      if(j->second != NULL) {
	 delete j->second;
      }
   }
}

void CLog::add_Logger(const LogType type, iLogDriver *log_driver)
{
   if(log_driver) {
      if(mChains.find(type) == mChains.end()) mChains.insert(make_pair(type, new CLog_Chain(type)));
      if(mChains[type] != NULL) {
	 mChains[type]->add_Logger(log_driver);
      }
   }
}

void CLog::Write(const LogType type, int level, const string &message)
{
   if(mChains.find(type) != mChains.end() && mChains[type] != NULL) {
      mChains[type]->Write(level, message);
   }
}
