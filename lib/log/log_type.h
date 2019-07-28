/****************************************************
 * Copyright 2018 Ben M. Ward
 *
 * This work is licensed under the Creative
 * Commons Attribution-NonCommercial-ShareAlike
 * 3.0 Unported License. To view a copy of this
 * license, visit
 * http://creativecommons.org/licenses/by-nc-sa/3.0/
 * or send a letter to Creative Commons, 444
 * Castro Street, Suite 900, Mountain View,
 * California, 94041, USA.
 ***************************************************/
#ifndef LIB_LOG_LOG_TYPE_H_
#define LIB_LOG_LOG_TYPE_H_

namespace DESCENT_BOT {
namespace LIB {
namespace LOG {

enum LogType {
  LogType_Fatal,
  LogType_Error,
  LogType_Warning,
  LogType_Debug,
  LogType_Info
};

}  // namespace LOG
}  // namespace LIB
}  // namespace DESCENT_BOT

#endif  // LIB_LOG_LOG_TYPE_H_
