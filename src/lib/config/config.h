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
#ifndef SRC_LIB_CONFIG_CONFIG_H_
#define SRC_LIB_CONFIG_CONFIG_H_

#include <map>
#include <string>
#include <vector>

#include "src/lib/log/log.h"
#include "src/lib/log/log_driver_file.h"
#include "src/lib/log/log_driver_raw.h"
#include "src/lib/config/xml.h"

namespace DESCENT_BOT {
namespace SRC {
namespace LIB {
namespace CONFIG {

class CConfig;
class CConfig_Logging;

class CConfig_Logging_Logger {
 public:
  ::std::string get_Name() const;
  ::DESCENT_BOT::SRC::LIB::LOG::LogType get_Type() const;
  int get_Level() const;
  ::std::string get_Driver() const;
  ::std::string operator[](const ::std::string &key);
  ::std::vector<::std::string> get_Option_Names();

 private:
  ::std::string mName;
  ::DESCENT_BOT::SRC::LIB::LOG::LogType mType;
  int mLevel;
  ::std::string mDriver;
  ::std::map<::std::string, ::std::string> mOptions;

  CConfig_Logging_Logger();
  CConfig_Logging_Logger(const CConfig_Logging_Logger &source);
  explicit CConfig_Logging_Logger(CXMLNode *node);
  ~CConfig_Logging_Logger();
  CConfig_Logging_Logger &operator=(const CConfig_Logging_Logger &source);

  bool is_Valid() const;

  friend class CConfig_Logging;
};


class CConfig_Logging {
 public:
  CConfig_Logging_Logger &operator[](const ::std::string &index) const;
  ::std::vector<::std::string> get_Names() const;

 private:
  ::std::map<::std::string, CConfig_Logging_Logger *> mLoggers;

  CConfig_Logging();
  CConfig_Logging(const CConfig_Logging &source);
  ~CConfig_Logging();

  ::DESCENT_BOT::SRC::LIB::LOG::LogType get_LogType(CXMLNode *node);
  CConfig_Logging &operator=(const CConfig_Logging &source);
  bool Load_Logging(CXMLNode *node);

  friend class CConfig;
};

/// This class represents the current configuration setup
class CConfig {
 public:
  ~CConfig();

  static CConfig &getInstance();

  bool Load(const ::std::string filename);
  void Reset();

  CConfig_Logging Logging;

 private:
  static CConfig *mSingleton;

  void Initialize();
  static void clearInstance();

  friend class CConfig_Logging;

  CConfig();
  CConfig(const CConfig &source);
  CConfig &operator=(const CConfig &source);
};

}  // namespace CONFIG
}  // namespace LIB
}  // namespace SRC
}  // namespace DESCENT_BOT

#endif  // SRC_LIB_CONFIG_CONFIG_H_
