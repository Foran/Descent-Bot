#include "log_driver_raw.h"

CLogDriverRaw::CLogDriverRaw() 
{
}

bool CLogDriverRaw::Write(LogType type, int level, const string &message)
{
   bool retval = true;
   
   switch(type) {
    case LogType_Fatal:
      cout << "Fatal";
      break;
    case LogType_Error:
      cout << "Error";
      break;
    case LogType_Warning:
      cout << "Warning";
      break;
    case LogType_Debug:
      cout << "Debug";
      break;
    case LogType_Info:
      cout << "Info";
      break;
    default:
      cout << "Unknown Type";
      break;
   }
   
   cout << "(" << level << "): " <<  message << endl;
   
   return retval;
}
