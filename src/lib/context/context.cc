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
#include "src/lib/context/context.h"

namespace DESCENT_BOT {
namespace SRC {
namespace LIB {
namespace CONTEXT {

using ::std::string;

CContext::CContext() {
}

CContext::~CContext() {
}

CComponent *CContext::getComponent(const string &name) {
  return mComponentMap[name];
}

void CContext::registerComponent(const string &name, CComponent *component) {
  mComponentMap.emplace(name, component);
}

}  // namespace CONTEXT
}  // namespace LIB
}  // namespace SRC
}  // namespace DESCENT_BOT
