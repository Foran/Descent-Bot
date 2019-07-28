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
#ifndef LIB_LOG_LOG_DRIVER_H_
#define LIB_LOG_LOG_DRIVER_H_

#include <string>
#include <iostream>
#include <sstream>

#include "lib/context/context.h"
#include "lib/log/log_type.h"

namespace DESCENT_BOT {
namespace LIB {
namespace LOG {

class CLogDriverBase {
 public:
  explicit CLogDriverBase(::DESCENT_BOT::LIB::CONTEXT::CContext *context) {
    mContext = context;
  }
  virtual ~CLogDriverBase() {}
  virtual void set_Name(const ::std::string &name) = 0;
  virtual ::std::string get_Name() const = 0;
  virtual ::std::string get_Driver() const = 0;
  virtual void set_Type(const ::std::string &type) = 0;
  virtual void set_Type(const LogType &type) = 0;
  virtual LogType get_Type() const = 0;
  virtual void set_Level(const ::std::string &level) = 0;
  virtual void set_Level(const int &level) = 0;
  virtual int get_Level() const = 0;
  virtual void set_Option(const ::std::string &name,
                          const ::std::string &value) = 0;
  virtual ::std::string get_Option(const ::std::string &name) = 0;
  virtual bool Write(int level, const ::std::string &message) = 0;

  // CLogDriverBase &operator<<(CLogDriverBase &source);
  // stringstream &operator<<(stringstream &source);

 protected:
  ::DESCENT_BOT::LIB::CONTEXT::CContext *mContext;
  // string getBuffer();

 private:
  ::std::stringstream mStringStream;
};

extern ::std::ostream &operator<<(::std::ostream &output, const LogType &type);

extern LogType GetLogType(::std::string type);

}  // namespace LOG
}  // namespace LIB
}  // namespace DESCENT_BOT

#endif  // LIB_LOG_LOG_DRIVER_H_
