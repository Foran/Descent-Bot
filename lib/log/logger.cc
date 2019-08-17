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
#include "lib/log/logger.h"

#include <memory>

using ::std::ostream;
using ::std::unique_ptr;

namespace DESCENT_BOT {
namespace LIB {
namespace LOG {

CLogger::CLogger(CLog *log, const LogType type, int level)
  : ostream(new CLoggerStringBuf(log, type, level)) {
}

CLogger::~CLogger() {
  delete rdbuf();
}

CLogger::CLoggerStringBuf::CLoggerStringBuf(CLog *log, const LogType type,
  int level) : mLog(log), mType(type), mLevel(level) {
}

CLogger::CLoggerStringBuf::~CLoggerStringBuf() {
  sync();
}

int CLogger::CLoggerStringBuf::sync() {
  mLog->Write(mType, mLevel, str());
  str("");
  return 0;
}

unique_ptr<CLogger> CLogger::createInstance(CLog *log, const LogType type,
                                            int level) {
  // using new instead of make_unique because the constructor is private
  return unique_ptr<CLogger>(new CLogger(log, type, level));
}

}  // namespace LOG
}  // namespace LIB
}  // namespace DESCENT_BOT

