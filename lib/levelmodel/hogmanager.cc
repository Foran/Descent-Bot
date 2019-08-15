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

#include <memory>
#include <vector>

#include "lib/context/context.h"

using ::std::string;
using ::std::vector;
using ::std::make_unique;
using ::std::move;

namespace DESCENT_BOT {
namespace LIB {
namespace LEVELMODEL {

using DESCENT_BOT::LIB::CONTEXT::CContext;

CHogManager::CHogManager(CContext *context) {
  mContext = context;
}

CHogManager::~CHogManager() {
}

string CHogManager::getName() const {
  return "HogManager";
}

CHog &CHogManager::operator[](const string &filename) {
  CHog *retval = nullptr;

  for (auto& hog : mHogs) {
    if (hog->mFilename == filename) {
      retval = hog.get();
      break;
    }
  }

  if (retval == nullptr) {
    auto hog = make_unique<CHog>(mContext, filename);
    retval = hog.get();
    mHogs.push_back(move(hog));
  }

  return *retval;
}

CHogManager *CHogManager::fromContext(CContext *context) {
  return dynamic_cast<CHogManager *>(context->getComponent("HogManager"));
}

}  // namespace LEVELMODEL
}  // namespace LIB
}  // namespace DESCENT_BOT
