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
#include "lib/levelmodel/hogmanager.h"

#include "lib/context/context.h"

using ::std::string;
using ::std::vector;

namespace DESCENT_BOT {
namespace LIB {
namespace LEVELMODEL {

using DESCENT_BOT::LIB::CONTEXT::CContext;

CHogManager::CHogManager(CContext *context) {
  mContext = context;
}

CHogManager::~CHogManager() {
  for (auto& hog : mHogs) {
    delete hog;
  }
}

string CHogManager::getName() const {
  return "HogManager";
}

CHog &CHogManager::operator[](const string &filename) {
  CHog *retval = nullptr;

  for (auto& hog : mHogs) {
    if (hog->mFilename == filename) {
      retval = hog;
      break;
    }
  }

  if (retval == nullptr) {
    retval = new CHog(mContext, filename);
    mHogs.push_back(retval);
  }

  return *retval;
}

CHogManager *CHogManager::fromContext(CContext *context) {
  return dynamic_cast<CHogManager *>(context->getComponent("HogManager"));
}

}  // namespace LEVELMODEL
}  // namespace LIB
}  // namespace DESCENT_BOT
