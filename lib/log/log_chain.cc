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
#include "lib/log/log_chain.h"

#include <string>
#include <vector>

#include "lib/context/context.h"
#include "lib/log/log_driver.h"
#include "lib/log/log_type.h"

using ::std::string;
using ::std::vector;

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

}  // namespace LOG
}  // namespace LIB
}  // namespace DESCENT_BOT
