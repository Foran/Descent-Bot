#include "log_driver.h"

ostream &operator<<(ostream &output, const LogType &type) 
{
   switch(type) {
    case LogType_Fatal:
      output << "Fatal";
      break;
    case LogType_Error:
      output << "Error";
      break;
    case LogType_Warning:
      output << "Warning";
      break;
    case LogType_Debug:
      output << "Debug";
    case LogType_Info:
      output << "Info";
      break;
    default:
      output << "Unknown";
      break;
   }
   
   return output;
}
