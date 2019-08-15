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
using ::std::move;

using ::DESCENT_BOT::LIB::CONTEXT::CContext;

namespace DESCENT_BOT {
namespace LIB {
namespace LOG {

CLog::CLog(CContext *context) {
  mCacheEnabled = false;
  mContext = context;
}

CLog::~CLog() {
}

::std::string CLog::getName() const {
  return "Log";
}

void CLog::add_Logger(const LogType type, unique_ptr<CLogDriverBase> log_driver) {
  if (log_driver) {
    if (mChains.find(type) == mChains.end()) {
      mChains.insert(make_pair(type, make_unique<CLog_Chain>(mContext, type)));
    }
    if (mChains[type] != nullptr) {
      mChains[type]->add_Logger(move(log_driver));
    }
  }
}

void CLog::Write(const LogType type, int level, const string &message) {
  if (mCacheEnabled) {
    auto entry = make_unique<CLog_Cached_Entry>();
    entry->type = type;
    entry->level = level;
    entry->message = message;
    entry->timestamp = time(nullptr);
    mCache.push_back(move(entry));
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
    Write(cache->type, cache->level,
          string("[Cached at ") + cache->timestamp + "] " + cache->message);
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
