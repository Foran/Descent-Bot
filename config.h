#ifndef __CONFIG_H__
#define __CONFIG_H__

#include <libxml/parser.h>
#include <libxml/tree.h>

#include <string>
#include <vector>
#include <map>

using namespace std;

#include "log.h"
#include "log_driver_raw.h"

class CConfig;
class CConfig_Logging;

class CConfig_Logging_Logger
{
 public:
   CConfig_Logging_Logger();
   string get_Name() const;
   string get_Type() const;
   int get_Level() const;
   string get_Driver() const;
 protected:
 private:
     string mName;
   string mType;
   int mLevel;
   string mDriver;
   
     friend class CConfig_Logging;
};


class CConfig_Logging
{
 public:
   CConfig_Logging();
   CConfig_Logging(const CConfig_Logging &source);
   ~CConfig_Logging();
   
   CConfig_Logging &operator=(const CConfig_Logging &source);
   CConfig_Logging_Logger &operator[](const string &index) const;
   vector<string> get_Names() const;
 protected:
 private:
     map<string, CConfig_Logging_Logger *> mLoggers;

     friend class CConfig;
};

class CConfig 
{
 public:
   CConfig();
   CConfig(const string filename);
   CConfig(const CConfig &source);
   ~CConfig();
   
   CConfig &operator=(const CConfig &source);
   
   bool Load(const string filename);
   
   void Reset();
 protected:
 private:
     static unsigned int mReferences;
   
   void Init();
   bool Load_Logging(const xmlNodePtr node);
   
   string xmlChar2string(const xmlChar *value);
};

extern CConfig global_Config;

#endif
