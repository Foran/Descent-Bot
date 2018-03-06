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
#include "src/lib/log/log.h"

namespace DESCENT_BOT {
namespace SRC {
namespace LIB {
namespace LOG {

CLog global_Log;

CLog_Chain::CLog_Chain(const LogType type) {
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

void CLog_Chain::add_Logger(LogDriverBase *log_driver) {
  if (log_driver) mDrivers.push_back(log_driver);
}

void CLog_Chain::Write(int level, const string &message) {
  for (auto& driver : mDrivers) {
    dynamic_cast<LogDriverBase *>(driver)->Write(level, message);
  }
}

CLog::CLog() {
  mCacheEnabled = false;
}

CLog::~CLog() {
  for (auto& pair : mChains) {
    if (pair.second != nullptr) {
      delete pair.second;
    }
  }
}

void CLog::add_Logger(const LogType type, LogDriverBase *log_driver) {
  if (log_driver) {
    if (mChains.find(type) == mChains.end()) {
      mChains.insert(make_pair(type, new CLog_Chain(type)));
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

void CLog::FlushCache() {
  bool temp = mCacheEnabled;
  mCacheEnabled = false;

  for (auto& cache : mCache) {
    Write(cache.type, cache.level,
          string("[Cached at ") + cache.timestamp + "] " + cache.message);
  }

  mCacheEnabled = temp;
}

string operator+(string input, int number) {
  stringstream ss;
  ss << number;
  return input + ss.str();
}

}  // namespace LOG
}  // namespace LIB
}  // namespace SRC
}  // namespace DESCENT_BOT
