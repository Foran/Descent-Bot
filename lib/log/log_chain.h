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
#ifndef LIB_LOG_LOG_CHAIN_H_
#define LIB_LOG_LOG_CHAIN_H_

#include <string>
#include <vector>

#include "lib/context/context.h"
#include "lib/log/log_driver.h"
#include "lib/log/log_type.h"

namespace DESCENT_BOT {
namespace LIB {
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

}  // namespace LOG
}  // namespace LIB
}  // namespace DESCENT_BOT

#endif  // LIB_LOG_LOG_CHAIN_H_
