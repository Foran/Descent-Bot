#ifndef __LOG_H__
#define __LOG_H__

#include <string>
#include <vector>

#include "log_driver.h"

class CLog 
{
 public:
   void add_Logger(iLogDriver *log_driver);
 protected:
 private:
};

#endif
