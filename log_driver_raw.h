#ifndef __LOG_DRIVER_RAW_H__
#define __LOG_DRIVER_RAW_H__

#include <stdio.h>
#include <string>

using namespace std;

#include "log_driver.h"

class CLogDriverRaw : public iLogDriver 
{
 public:
   virtual bool Write(LogType type, int level, const string &message);
 protected:
 private:
};

#endif
