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
#ifndef LIB_LEVELMODEL_HOGMANAGER_H_
#define LIB_LEVELMODEL_HOGMANAGER_H_

#include <string>
#include <vector>

namespace DESCENT_BOT {
namespace LIB {
namespace LEVELMODEL {
class CHog;
}  // namespace LEVELMODEL
}  // namespace LIB
}  // namespace DESCENT_BOT

#include "lib/context/component.h"
#include "lib/context/context.h"
#include "lib/levelmodel/hog.h"

namespace DESCENT_BOT {
namespace LIB {
namespace LEVELMODEL {

class CHogManager : public DESCENT_BOT::LIB::CONTEXT::CComponent {
 public:
  explicit CHogManager(DESCENT_BOT::LIB::CONTEXT::CContext *context);
  ~CHogManager();

  ::std::string getName() const override;
  CHog &operator[](const ::std::string &filename);

  static CHogManager *fromContext(
    ::DESCENT_BOT::LIB::CONTEXT::CContext *context);
 private:
  DESCENT_BOT::LIB::CONTEXT::CContext *mContext;
  ::std::vector<CHog *> mHogs;
};

}  // namespace LEVELMODEL
}  // namespace LIB
}  // namespace DESCENT_BOT

#endif  // LIB_LEVELMODEL_HOGMANAGER_H_
