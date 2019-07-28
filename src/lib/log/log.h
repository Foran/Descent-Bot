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
#include <memory>

#include "lib/context/component.h"
#include "lib/context/context.h"
#include "src/lib/log/log_driver.h"
#include "src/lib/log/logger.h"

#define LOG(type, level) LOG_CONTEXT(mContext, type, level)
#define LOG_GLOBAL(type, level) \
  LOG_CONTEXT(&CApplicationContext::getInstance(), type, level)
#define LOG_CONTEXT(context, type, level) \
  *CLog::fromContext(context)->Write(type, level) << "[" << __FILE__ << ":" \
    << __LINE__ << "] "

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
  CLog_Chain(::DESCENT_BOT::LIB::CONTEXT::CContext *context,
             const LogType type);
  ~CLog_Chain();

  LogType get_Type() const;

  void add_Logger(CLogDriverBase *log_driver);
  void Write(int level, const ::std::string &message);

 private:
  ::DESCENT_BOT::LIB::CONTEXT::CContext *mContext;
  ::std::vector<CLogDriverBase *> mDrivers;
  LogType mType;

  CLog_Chain() = delete;
  CLog_Chain(const CLog_Chain &source) = delete;
  CLog_Chain &operator=(const CLog_Chain &source) = delete;
};

struct CLog_Cached_Entry {
  LogType type;
  int level;
  ::std::string message;
  ::time_t timestamp;
};

class CLogger;

/// This class manages all logging
class CLog : public ::DESCENT_BOT::LIB::CONTEXT::CComponent {
 public:
  explicit CLog(::DESCENT_BOT::LIB::CONTEXT::CContext *context);
  ~CLog();

  ::std::string getName() const override;
  void add_Logger(const LogType type, CLogDriverBase *log_driver);
  void Write(const LogType type, int level, const ::std::string &message);
  ::std::unique_ptr<CLogger> Write(const LogType type, int level);

  static CLog *fromContext(::DESCENT_BOT::LIB::CONTEXT::CContext *context);
 private:
  ::DESCENT_BOT::LIB::CONTEXT::CContext *mContext;
  bool mCacheEnabled;
  ::std::vector<CLog_Cached_Entry> mCache;
  ::std::map<LogType, CLog_Chain *> mChains;

  CLog(const CLog &source);
  void operator=(const CLog &source);

  void FlushCache();

  friend class ::DESCENT_BOT::SRC::LIB::CONFIG::CConfig;
};

extern ::std::string operator+(::std::string input, int number);

}  // namespace LOG
}  // namespace LIB
}  // namespace SRC
}  // namespace DESCENT_BOT

#endif  // SRC_LIB_LOG_LOG_H_
