/****************************************************
 * This work is licensed under the Creative
 * Commons Attribution-NonCommercial-ShareAlike
 * 3.0 Unported License. To view a copy of this
 * license, visit
 * http://creativecommons.org/licenses/by-nc-sa/3.0/
 * or send a letter to Creative Commons, 444
 * Castro Street, Suite 900, Mountain View,
 * California, 94041, USA.
 ***************************************************/
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
	  break;
    case LogType_Info:
      output << "Info";
      break;
    default:
      output << "Unknown";
      break;
   }
   
   return output;
}

LogType GetLogType(string type) {
	LogType retval = LogType_Info;

	if(type == "Fatal") retval = LogType_Fatal;
	else if(type == "Error") retval = LogType_Error;
	else if(type == "Warning") retval = LogType_Warning;
	else if(type == "Debug") retval = LogType_Debug;
	else if(type == "Info") retval = LogType_Info;

	return retval;
}
