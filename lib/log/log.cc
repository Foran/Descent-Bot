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
#include "lib/log/log.h"

#include <memory>

using ::std::make_pair;
using ::std::string;
using ::std::stringstream;
using ::std::ostream;
using ::std::stringbuf;
using ::std::cout;
using ::std::endl;
using ::std::flush;
using ::std::unique_ptr;
using ::std::make_unique;

using ::DESCENT_BOT::LIB::CONTEXT::CContext;

namespace DESCENT_BOT {
namespace LIB {
namespace LOG {

CLog_Chain::CLog_Chain(CContext *context, const LogType type) {
  mContext = context;
  mType = type;
}

CLog_Chain::~CLog_Chain() {
  for (auto& driver : mDrivers) {
    delete driver;
  }
}

LogType CLog_Chain::get_Type() const {
  return mType;
}

void CLog_Chain::add_Logger(CLogDriverBase *log_driver) {
  if (log_driver) mDrivers.push_back(log_driver);
}

void CLog_Chain::Write(int level, const string &message) {
  for (auto& driver : mDrivers) {
    dynamic_cast<CLogDriverBase *>(driver)->Write(level, message);
  }
}

CLog::CLog(CContext *context) {
  mCacheEnabled = false;
  mContext = context;
}

CLog::~CLog() {
  for (auto& pair : mChains) {
    if (pair.second != nullptr) {
      delete pair.second;
    }
  }
}

string CLog::getName() const {
  return "Log";
}

void CLog::add_Logger(const LogType type, CLogDriverBase *log_driver) {
  if (log_driver) {
    if (mChains.find(type) == mChains.end()) {
      mChains.insert(make_pair(type, new CLog_Chain(mContext, type)));
    }
    if (mChains[type] != NULL) {
      mChains[type]->add_Logger(log_driver);
    }
  }
}

void CLog::Write(const LogType type, int level, const string &message) {
  if (mCacheEnabled) {
    CLog_Cached_Entry entry;
    entry.type = type;
    entry.level = level;
    entry.message = message;
    entry.timestamp = time(nullptr);
    mCache.push_back(entry);
  } else if (mChains.find(type) != mChains.end() && mChains[type] != nullptr) {
    mChains[type]->Write(level, message);
  }
}

unique_ptr<CLogger> CLog::Write(const LogType type, int level) {
  return unique_ptr<CLogger>(new CLogger(this, type, level));
}

void CLog::FlushCache() {
  bool temp = mCacheEnabled;
  mCacheEnabled = false;

  for (auto& cache : mCache) {
    Write(cache.type, cache.level,
          string("[Cached at ") + cache.timestamp + "] " + cache.message);
  }

  mCacheEnabled = temp;
}


CLog *CLog::fromContext(CContext *context) {
  return dynamic_cast<CLog *>(context->getComponent("Log"));
}

string operator+(string input, int number) {
  stringstream ss;
  ss << number;
  return input + ss.str();
}

}  // namespace LOG
}  // namespace LIB
}  // namespace DESCENT_BOT
