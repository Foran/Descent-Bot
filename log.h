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
#ifndef __LOG_H__
#define __LOG_H__

#include <string>
#include <sstream>
#include <vector>
#include <map>
#include <iostream>

using namespace std;

#include <time.h>

#include "log_driver.h"

namespace DESCENT_BOT {
namespace SRC {
namespace LIB {
namespace CONFIG {
class CConfig;
}
}
}
}

/// This class represents a logging chain target
class CLog_Chain 
{
 public:
   CLog_Chain(const LogType type);
   ~CLog_Chain();
   
   LogType get_Type() const;
   
   void add_Logger(LogDriverBase *log_driver);
   void Write(int level, const string &message);
 protected:
 private:
     vector<LogDriverBase *> mDrivers;
   LogType mType;

   CLog_Chain();
   CLog_Chain(const CLog_Chain &source);
   CLog_Chain &operator=(const CLog_Chain &source);
};

struct CLog_Cached_Entry {
	LogType type;
	int level;
	string message;
	time_t timestamp;
};

/// This class manages all logging
class CLog 
{
 public:
   CLog();
   ~CLog();
   
   void add_Logger(const LogType type, LogDriverBase *log_driver);
   void Write(const LogType type, int level, const string &message);
 protected:
 private:
	bool mCacheEnabled;
	vector<CLog_Cached_Entry> mCache;
	map<LogType, CLog_Chain *> mChains;
   
	CLog(const CLog &source);
	void operator=(const CLog &source);

	void FlushCache();

	friend class ::DESCENT_BOT::SRC::LIB::CONFIG::CConfig;
};

extern string operator+(string input, int number);

extern CLog global_Log;

#endif
