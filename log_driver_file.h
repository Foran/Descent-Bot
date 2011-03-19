#ifndef __LOG_DRIVER_FILE_H__
#define __LOG_DRIVER_FILE_H__

#include <iostream>
#include <string>

using namespace std;

#include "log_driver.h"

class CLogDriverFile : public iLogDriver 
{
 public:
   CLogDriverFile();
   virtual void set_Name(const string &name);
   virtual string get_Name() const;
   virtual string get_Driver() const;
   virtual void set_Type(const string &type);
   virtual void set_Type(const LogType &type);
   virtual LogType get_Type() const;
   virtual void set_Level(const string &level);
   virtual void set_Level(const int &level);
   virtual int get_Level() const;
   virtual void set_Option(const string &name, const string &value);
   virtual string get_Option(const string &name);
   virtual bool Write(LogType type, int level, const string &message);
 protected:
 private:
};

#endif
