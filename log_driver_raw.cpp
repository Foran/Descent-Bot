#include "log_driver_raw.h"

bool CLogDriverRaw::Write(LogType type, int level, const string &message)
{
   bool retval = true;
   
   switch(type) {
    case Fatal:
      printf("Fatal");
      break;
    case Error:
      printf("Error");
      break;
    case Warning:
      printf("Warning");
      break;
    case Debug:
      printf("Debug");
      break;
    case Info:
      printf("Info");
      break;
    default:
      printf("Unknown Type");
      break;
   }
   
   printf("(%i): %s\n", level, message.c_str());
   
   return retval;
}
