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
#include "src/lib/context/application_context.h"

#include <iostream>
#include <utility>

namespace DESCENT_BOT {
namespace SRC {
namespace LIB {
namespace CONTEXT {

CApplicationContext::CApplicationContext() {
}

CApplicationContext::~CApplicationContext() {
}

CContext &CApplicationContext::getContext() {
  return *this;
}

void CApplicationContext::registerComponent(CComponent *component) {
  registerComponent(component->getName(), component);
}

void CApplicationContext::registerComponent(const ::std::string &name, CComponent *component) {
  CContext::registerComponent(name, component);
}

}  // namespace CONTEXT
}  // namespace LIB
}  // namespace SRC
}  // namespace DESCENT_BOT
