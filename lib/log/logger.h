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
#ifndef LIB_LOG_LOGGER_H_
#define LIB_LOG_LOGGER_H_

#include <iostream>

#include "lib/log/log.h"

namespace DESCENT_BOT {
namespace LIB {
namespace LOG {

class CLog;

class CLogger : public ::std::ostream {
 public:
  ~CLogger();

 private:
  class CLoggerStringBuf : public ::std::stringbuf {
   public:
    CLoggerStringBuf(CLog *log, const LogType type, int level);
    ~CLoggerStringBuf();

   protected:
    int sync() override;
   private:
    CLog *mLog;
    LogType mType;
    int mLevel;

    CLoggerStringBuf() = delete;
    CLoggerStringBuf(const CLoggerStringBuf &source) = delete;

    CLoggerStringBuf &operator=(const CLoggerStringBuf &source) = delete;
  };

  CLogger() = delete;
  CLogger(const CLogger &source) = delete;
  CLogger(CLog *log, const LogType type, int level);

  CLogger &operator=(const CLogger &source) = delete;

  friend class CLog;
};

}  // namespace LOG
}  // namespace LIB
}  // namespace DESCENT_BOT

#endif  // LIB_LOG_LOGGER_H_
