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
#ifndef SRC_LIB_CONTEXT_COMPONENT_H_
#define SRC_LIB_CONTEXT_COMPONENT_H_

#include <string>

namespace DESCENT_BOT {
namespace SRC {
namespace LIB {
namespace CONTEXT {

struct CComponent {
  virtual ::std::string getName() const = 0;
};

}  // namespace CONTEXT
}  // namespace LIB
}  // namespace SRC
}  // namespace DESCENT_BOT

#endif  // SRC_LIB_CONTEXT_COMPONENT_H_
