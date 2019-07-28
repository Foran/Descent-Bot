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
#include "src/lib/config/config.h"

#include <fcntl.h>
#include <google/protobuf/text_format.h>
#include <google/protobuf/io/zero_copy_stream_impl.h>

#include "lib/context/context.h"
#include "src/lib/log/log.h"
#include "src/lib/log/log_driver.h"
#include "src/lib/log/log_driver_raw.h"

namespace DESCENT_BOT {
namespace SRC {
namespace LIB {
namespace CONFIG {

using ::std::string;
using ::std::vector;

using PROTO::Config;
using PROTO::Logger;

using ::DESCENT_BOT::LIB::CONTEXT::CContext;
using ::DESCENT_BOT::SRC::LIB::LOG::CLog;
using ::DESCENT_BOT::SRC::LIB::LOG::CLogDriverBase;
using ::DESCENT_BOT::SRC::LIB::LOG::CLogDriverRaw;
using ::DESCENT_BOT::SRC::LIB::LOG::LogType;

/**
 * Default constructor of the CConfig class
 * @see CConfig(const string filename)
 * @see CConfig(const CConfig &source)
 *****************************************/
CConfig::CConfig(CContext *context) {
  mContext = context;
}

/**
 * Destructor
 *************************************/
CConfig::~CConfig() {
}

string CConfig::getName() const {
  return "Config";
}

bool CConfig::Load(const string filename) {
  bool retval = false;
  Reset();

  int fd = open(filename.c_str(), O_RDONLY);
  if (fd > 0) {
    ::google::protobuf::io::FileInputStream input(fd);
    if (!::google::protobuf::TextFormat::Parse(&input, &mConfig)) {
      // Log error
    } else {
      CLog *log = CLog::fromContext(mContext);
      for (int i = 0; i < mConfig.loggers_size(); i++) {
        CLogDriverBase *driver = nullptr;
        if (::std::string("Raw") == mConfig.loggers(i).driver()) {
          driver = new CLogDriverRaw(mContext);
        }
        if (driver != nullptr) {
          driver->set_Name(mConfig.loggers(i).name());
          driver->set_Level(mConfig.loggers(i).level());
          switch (mConfig.loggers(i).type()) {
            case Logger::LogType::Logger_LogType_INFO:
              log->add_Logger(LogType::LogType_Info, driver);
              break;
            case Logger::LogType::Logger_LogType_DEBUG:
              log->add_Logger(LogType::LogType_Debug, driver);
              break;
            case Logger::LogType::Logger_LogType_WARNING:
              log->add_Logger(LogType::LogType_Warning, driver);
              break;
            case Logger::LogType::Logger_LogType_ERROR:
              log->add_Logger(LogType::LogType_Error, driver);
              break;
            case Logger::LogType::Logger_LogType_FATAL:
              log->add_Logger(LogType::LogType_Fatal, driver);
              break;
            default:
              delete driver;
              break;
          }
        }
      }
      retval = true;
    }
  }

  return retval;
}

void CConfig::Reset() {
  mConfig.Clear();
}

CConfig *CConfig::fromContext(CContext *context) {
  return dynamic_cast<CConfig *>(context->getComponent("Config"));
}

}  // namespace CONFIG
}  // namespace LIB
}  // namespace SRC
}  // namespace DESCENT_BOT
