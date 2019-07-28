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
#include "lib/levelmodel/fstreamptr.h"

#include "lib/context/context.h"
#include "src/lib/log/log.h"

using ::std::cout;
using ::std::endl;
using ::std::fstream;
using ::std::map;

using ::DESCENT_BOT::LIB::CONTEXT::CContext;
using ::DESCENT_BOT::SRC::LIB::LOG::CLog;
using ::DESCENT_BOT::SRC::LIB::LOG::LogType;

namespace DESCENT_BOT {
namespace LIB {
namespace LEVELMODEL {

map<fstream *, int> fstreamptr::mReferences;

fstreamptr::fstreamptr(CContext *context) {
  mContext = context;
  mPtr = new fstream();
  mReferences[mPtr] = 1;
  LOG(LogType::LogType_Debug, 200) << "Initial fstreamptf() called";
}

fstreamptr::fstreamptr(const fstreamptr &source) {
  LOG(LogType::LogType_Debug, 200) << "Copy constructor for fstreamptr called";
  *this = source;
}

fstreamptr::fstreamptr(CContext *context, const char *filename,
                       const ::std::ios_base::openmode mode) {
  mContext = context;
  mPtr = new fstream(filename, mode);
  mReferences[mPtr] = 1;
  LOG(LogType::LogType_Debug, 200)
    << "Initial fstreamptr(filename, mode) called";
}

fstreamptr::~fstreamptr() {
  mReferences[mPtr]--;
  LOG(LogType::LogType_Debug, 200)
    << "Destructor for fstreamptr called with a reference count of "
    << mReferences[mPtr];
  if (mReferences[mPtr] == 0) {
    mReferences.erase(mPtr);
    delete mPtr;
  }
}

fstreamptr &fstreamptr::operator=(const fstreamptr &source) {
  mContext = source.mContext;
  mPtr = source.mPtr;
  mReferences[mPtr]++;

  return *this;
}

fstream &fstreamptr::operator*() {
  return *mPtr;
}

fstream const &fstreamptr::operator*() const {
  return *mPtr;
}

}  // namespace LEVELMODEL
}  // namespace LIB
}  // namespace DESCENT_BOT
