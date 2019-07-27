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
#ifndef SRC_LIB_CONFIG_CONFIG_H_
#define SRC_LIB_CONFIG_CONFIG_H_

#include <map>
#include <string>
#include <vector>

#include "src/lib/config/config.pb.h"
#include "src/lib/context/component.h"
#include "src/lib/context/context.h"

namespace DESCENT_BOT {
namespace SRC {
namespace LIB {
namespace CONFIG {

class CConfig : public ::DESCENT_BOT::SRC::LIB::CONTEXT::CComponent {
 public:
  explicit CConfig(::DESCENT_BOT::SRC::LIB::CONTEXT::CContext *context);
  ~CConfig();

  ::std::string getName() const override;
  bool Load(const ::std::string filename);
  void Reset();

  static CConfig *fromContext(
    ::DESCENT_BOT::SRC::LIB::CONTEXT::CContext *context);

 private:
  ::DESCENT_BOT::SRC::LIB::CONTEXT::CContext *mContext;
  PROTO::Config mConfig;

  CConfig(const CConfig &source) = delete;
  CConfig &operator=(const CConfig &source) = delete;
};

}  // namespace CONFIG
}  // namespace LIB
}  // namespace SRC
}  // namespace DESCENT_BOT

#endif  // SRC_LIB_CONFIG_CONFIG_H_
