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
   virtual bool Write(LogType type, int level, const string &message);
 protected:
 private:
};

#endif
