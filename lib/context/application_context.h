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
#ifndef LIB_CONTEXT_APPLICATION_CONTEXT_H_
#define LIB_CONTEXT_APPLICATION_CONTEXT_H_

#include <map>
#include <string>

#include "lib/context/context.h"

namespace DESCENT_BOT {
namespace LIB {
namespace CONTEXT {

class CApplicationContext : public CContext {
 public:
  CApplicationContext();
  ~CApplicationContext() override;

  CContext &getContext();
  void registerComponent(CComponent *component);
  void registerComponent(const ::std::string &name, CComponent *component);

  static CApplicationContext &getInstance();
 protected:
 private:
  static CApplicationContext mInstance;
  explicit CApplicationContext(const CContext &source) = delete;
  explicit CApplicationContext(const CContext &&source) = delete;
  CApplicationContext &operator=(const CContext &source) = delete;
};

}  // namespace CONTEXT
}  // namespace LIB
}  // namespace DESCENT_BOT

#endif  // LIB_CONTEXT_APPLICATION_CONTEXT_H_
