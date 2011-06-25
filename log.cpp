/****************************************************
 * This work is licensed under the Creative
 * Commons Attribution-NonCommercial-ShareAlike
 * 3.0 Unported License. To view a copy of this
 * license, visit
 * http://creativecommons.org/licenses/by-nc-sa/3.0/
 * or send a letter to Creative Commons, 444
 * Castro Street, Suite 900, Mountain View,
 * California, 94041, USA.
 ***************************************************/
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
	   dynamic_cast<iLogDriver *>(*i)->Write(level, message);
   }
}

CLog::CLog()
{
	mCacheEnabled = false;
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

void CLog::Write(const LogType type, int level, const string &message) {
	if(mCacheEnabled) {
		CLog_Cached_Entry entry;
		entry.type = type;
		entry.level = level;
		entry.message = message;
		entry.timestamp = time(NULL);
		mCache.push_back(entry);
	}
	else if(mChains.find(type) != mChains.end() && mChains[type] != NULL) {
		mChains[type]->Write(level, message);
	}
}

void CLog::FlushCache() {
	bool temp = mCacheEnabled;
	mCacheEnabled = false;

	for(vector<CLog_Cached_Entry>::iterator i = mCache.begin(); i != mCache.end(); i++) {
		Write(i->type, i->level, string("[Cached at ") + i->timestamp + "] " + i->message);
	}

	mCacheEnabled = temp;
}

string operator+(string input, int number) 
{
   stringstream ss;
   ss << number;
   return input + ss.str();
}
