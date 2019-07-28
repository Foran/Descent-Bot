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
#ifndef LIB_CONFIG_CONFIG_H_
#define LIB_CONFIG_CONFIG_H_

#include <map>
#include <string>
#include <vector>

#include "protos/lib/config/config.pb.h"
#include "lib/context/component.h"
#include "lib/context/context.h"

namespace DESCENT_BOT {
namespace LIB {
namespace CONFIG {

class CConfig : public ::DESCENT_BOT::LIB::CONTEXT::CComponent {
 public:
  explicit CConfig(::DESCENT_BOT::LIB::CONTEXT::CContext *context);
  ~CConfig();

  ::std::string getName() const override;
  bool Load(const ::std::string filename);
  void Reset();

  static CConfig *fromContext(
    ::DESCENT_BOT::LIB::CONTEXT::CContext *context);

 private:
  ::DESCENT_BOT::LIB::CONTEXT::CContext *mContext;
  PROTO::Config mConfig;

  CConfig(const CConfig &source) = delete;
  CConfig &operator=(const CConfig &source) = delete;
};

}  // namespace CONFIG
}  // namespace LIB
}  // namespace DESCENT_BOT

#endif  // LIB_CONFIG_CONFIG_H_
