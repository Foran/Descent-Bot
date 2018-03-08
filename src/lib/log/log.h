/****************************************************
 * Copyright 2018 Ben M. Ward
 *
 * This work is licensed under the Creative
 * Commons Attribution-NonCommercial-ShareAlike
 * 3.0 Unported License. To view a copy of this
 * license, visit
 * http://creativecommons.org/licenses/by-nc-sa/3.0/
 * or send a letter to Creative Commons, 444
 * Castro Street, Suite 900, Mountain View,
 * California, 94041, USA.
 ***************************************************/
#ifndef SRC_LIB_LOG_LOG_H_
#define SRC_LIB_LOG_LOG_H_

#include <time.h>

#include <string>
#include <sstream>
#include <vector>
#include <map>
#include <iostream>

#include "src/lib/log/log_driver.h"

namespace DESCENT_BOT {
namespace SRC {
namespace LIB {
namespace CONFIG {
class CConfig;
}  // namespace CONFIG
namespace LOG {

/// This class represents a logging chain target
class CLog_Chain {
 public:
  explicit CLog_Chain(const LogType type);
  ~CLog_Chain();

  LogType get_Type() const;

  void add_Logger(LogDriverBase *log_driver);
  void Write(int level, const ::std::string &message);

 private:
  ::std::vector<LogDriverBase *> mDrivers;
  LogType mType;

  CLog_Chain();
  CLog_Chain(const CLog_Chain &source);
  CLog_Chain &operator=(const CLog_Chain &source);
};

struct CLog_Cached_Entry {
  LogType type;
  int level;
  ::std::string message;
  ::time_t timestamp;
};

/// This class manages all logging
class CLog {
 public:
  CLog();
  ~CLog();

  void add_Logger(const LogType type, LogDriverBase *log_driver);
  void Write(const LogType type, int level, const ::std::string &message);

 private:
  bool mCacheEnabled;
  ::std::vector<CLog_Cached_Entry> mCache;
  ::std::map<LogType, CLog_Chain *> mChains;

  CLog(const CLog &source);
  void operator=(const CLog &source);

  void FlushCache();

  friend class ::DESCENT_BOT::SRC::LIB::CONFIG::CConfig;
};

extern ::std::string operator+(::std::string input, int number);

extern CLog global_Log;

}  // namespace LOG
}  // namespace LIB
}  // namespace SRC
}  // namespace DESCENT_BOT

#endif  // SRC_LIB_LOG_LOG_H_
