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
#ifndef SRC_LIB_LEVELMODEL_HOGMANAGER_H_
#define SRC_LIB_LEVELMODEL_HOGMANAGER_H_

#include <string>
#include <vector>

class CHog;

#include "src/lib/context/component.h"
#include "src/lib/context/context.h"
#include "src/lib/levelmodel/hog.h"

namespace DESCENT_BOT {
namespace SRC {
namespace LIB {
namespace LEVELMODEL {

class CHogManager : public DESCENT_BOT::SRC::LIB::CONTEXT::CComponent {
 public:
  explicit CHogManager(const DESCENT_BOT::SRC::LIB::CONTEXT::CContext &context);
  ~CHogManager();

  ::std::string getName() const override;
  CHog &operator[](const ::std::string &filename);
 private:
  DESCENT_BOT::SRC::LIB::CONTEXT::CContext *mContext;
  ::std::vector<CHog *> mHogs;
};

}  // namespace LEVELMODEL
}  // namespace LIB
}  // namespace SRC
}  // namespace DESCENT_BOT

#endif  // SRC_LIB_LEVELMODEL_HOGMANAGER_H_
