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
#include "src/lib/config/config.pb.h"

namespace DESCENT_BOT {
namespace SRC {
namespace LIB {
namespace CONFIG {

using ::DESCENT_BOT::SRC::LIB::LOG::CLogDriverFile;
using ::DESCENT_BOT::SRC::LIB::LOG::CLogDriverRaw;
using ::DESCENT_BOT::SRC::LIB::LOG::global_Log;
using PROTO::Config;

CConfig *CConfig::mSingleton = NULL;

/**
 * Default constructor of the CConfig class
 * @see CConfig(const string filename)
 * @see CConfig(const CConfig &source)
 *****************************************/
CConfig::CConfig() {
  atexit(clearInstance);
  Initialize();
  Reset();
}

/**
 * Destructor
 *************************************/
CConfig::~CConfig() {
  xmlCleanupParser();
}

/**
 * Clear Instance called at exit
 *************************************/
void CConfig::clearInstance() {
  if (mSingleton != nullptr) {
    delete mSingleton;
    mSingleton = nullptr;
  }
}

/**
 * Singleton getter
 *************************************/
CConfig &CConfig::getInstance() {
  if (mSingleton == nullptr) {
    mSingleton = new CConfig();
  }

  return *mSingleton;
}

void CConfig::Initialize() {
  LIBXML_TEST_VERSION
}

bool CConfig::Load(const string filename) {
  bool retval = false;
  CXML document;

  Reset();
  global_Log.mCacheEnabled = true;
  if (document.Load(filename)) {
    retval = true;
    global_Log.Write(LogType_Info, 10, "Starting new Instance of Descent-Bot");
    if (string("Configuration") == document.get_Root().get_Name()) {
      global_Log.Write(LogType_Debug, 150,
                       string("Found root config node (") +
                       document.get_Root().get_Name() + ")");
      for (auto& child : document.get_Root().get_Children()) {
        global_Log.Write(LogType_Debug, 150,
                         string("Found child node (") + child.get_Name() + ")");
        if (string("Logging") == child.get_Name()) {
          retval &= Logging.Load_Logging(&child);
        }
      }
    }
  }
  global_Log.FlushCache();
  global_Log.mCacheEnabled = false;

  return retval;
}

LogType CConfig_Logging::get_LogType(CXMLNode *node) {
  LogType retval = LogType_Fatal;

  if (static_cast<string>("Logger") == node->get_Name()) {
    if ((*node)["Type"] == "Fatal") retval = LogType_Fatal;
    else if ((*node)["Type"] == "Error") retval = LogType_Error;
    else if ((*node)["Type"] == "Warning") retval = LogType_Warning;
    else if ((*node)["Type"] == "Debug") retval = LogType_Debug;
    else if ((*node)["Type"] == "Info") retval = LogType_Info;
  }

  return retval;
}

bool CConfig_Logging::Load_Logging(CXMLNode *node) {
  bool retval = false;

  if (static_cast<string>("Logging") == node->get_Name()) {
    retval = true;
    for (auto& child : node->get_Children()) {
      if (static_cast<string>("Logger") == child.get_Name()) {
        CConfig_Logging_Logger logger(&child);
        if (logger.is_Valid()) {
          retval &= true;
        } else {
          retval &= false;
        }
      }
    }
  }

  return retval;
}

void CConfig::Reset() {
}

CConfig_Logging::CConfig_Logging() {
}

CConfig_Logging::CConfig_Logging(const CConfig_Logging &source) {
  *this = source;
}

CConfig_Logging::~CConfig_Logging() {
  for (auto& pair : mLoggers) {
    delete pair.second;
  }
}

CConfig_Logging &CConfig_Logging::operator=(const CConfig_Logging &source) {
  return *this;
}

CConfig_Logging_Logger::CConfig_Logging_Logger() {
  mLevel = 0;
}

CConfig_Logging_Logger::CConfig_Logging_Logger(CXMLNode *node) {
  if (static_cast<string>("Logger") == node->get_Name()) {
    global_Log.Write(LogType_Debug, 150,
                     string("Scanning Configuration->Logging->") +
                     node->get_Name() + " for attributes");
    for (auto& pair : node->get_Attributes()) {
      global_Log.Write(LogType_Debug, 150,
                       string("Configuration->Logging->") + node->get_Name() +
                       "[" + pair.first + "]=" + pair.second);
    }
    LogDriverBase *driver = nullptr;
    if ((*node)["Driver"] == "Raw") driver = new CLogDriverRaw();
    else if ((*node)["Driver"] == "File") driver = new CLogDriverFile();
    if (driver) {
      driver->set_Name((*node)["Name"]);
      driver->set_Level((*node)["Level"]);
      driver->set_Type((*node)["Type"]);
    }
    for (auto& child : node->get_Children()) {
      if (static_cast<string>("Option") == child.get_Name()) {
        global_Log.Write(LogType_Debug, 150,
                         string("Option ") + child["Name"] + " = " +
                         child["Value"]);
        if (driver) driver->set_Option(child["Name"], child["Value"]);
      }
    }
    if (driver) {
      global_Log.add_Logger(driver->get_Type(), driver);
    }
  } else {
    global_Log.Write(LogType_Debug, 50,
                     string("Was passed a node not of type Logger but of "
                            "type ") + node->get_Name());
  }
}

string CConfig_Logging_Logger::get_Name() const {
  return mName;
}

LogType CConfig_Logging_Logger::get_Type() const {
  return mType;
}

int CConfig_Logging_Logger::get_Level() const {
  return mLevel;
}

string CConfig_Logging_Logger::get_Driver() const {
  return mDriver;
}

string CConfig_Logging_Logger::operator[](const string &key) {
  return mOptions[key];
}

vector<string> CConfig_Logging_Logger::get_Option_Names() {
  vector<string> retval;

  for (auto& pair : mOptions) {
    retval.push_back(pair.first);
  }

  return retval;
}

CConfig_Logging_Logger::~CConfig_Logging_Logger() {
}

bool CConfig_Logging_Logger::is_Valid() const {
  bool retval = true;

  return retval;
}

}  // namespace CONFIG
}  // namespace LIB
}  // namespace SRC
}  // namespace DESCENT_BOT
