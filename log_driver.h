#ifndef __LOG_DRIVER_H__
#define __LOG_DRIVER_H__

#include <string>

using namespace std;

enum LogType 
{
     LogType_Fatal,
     LogType_Error,
     LogType_Warning,
     LogType_Debug,
     LogType_Info
};

typedef struct iLogDriver
{
   virtual bool Write(LogType type, int level, const string &message) = 0;
} iLogDriver;

#endif
