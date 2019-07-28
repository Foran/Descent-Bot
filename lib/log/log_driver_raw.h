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
#ifndef LIB_LOG_LOG_DRIVER_RAW_H_
#define LIB_LOG_LOG_DRIVER_RAW_H_

#include <stdlib.h>

#include <iostream>
#include <string>

#include "lib/context/context.h"
#include "lib/log/log_driver.h"
#include "lib/log/log_type.h"

namespace DESCENT_BOT {
namespace LIB {
namespace LOG {

class CLogDriverRaw : public CLogDriverBase {
 public:
  explicit CLogDriverRaw(::DESCENT_BOT::LIB::CONTEXT::CContext *context);
  virtual void set_Name(const ::std::string &name);
  virtual ::std::string get_Name() const;
  virtual ::std::string get_Driver() const;
  virtual void set_Type(const ::std::string &type);
  virtual void set_Type(const LogType &type);
  virtual LogType get_Type() const;
  virtual void set_Level(const ::std::string &level);
  virtual void set_Level(const int &level);
  virtual int get_Level() const;
  virtual void set_Option(const ::std::string &name,
                          const ::std::string &value);
  virtual ::std::string get_Option(const ::std::string &name);
  virtual bool Write(int level, const ::std::string &message);

 protected:
  int mLevel;
  LogType mType;
  ::std::string mName;
};

}  // namespace LOG
}  // namespace LIB
}  // namespace DESCENT_BOT

#endif  // LIB_LOG_LOG_DRIVER_RAW_H_
