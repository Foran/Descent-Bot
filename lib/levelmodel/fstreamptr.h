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
#ifndef LIB_LEVELMODEL_FSTREAMPTR_H_
#define LIB_LEVELMODEL_FSTREAMPTR_H_

#include <fstream>
#include <iostream>
#include <map>

#include "lib/context/context.h"

namespace DESCENT_BOT {
namespace LIB {
namespace LEVELMODEL {

class fstreamptr {
 public:
  explicit fstreamptr(::DESCENT_BOT::LIB::CONTEXT::CContext *context);
  fstreamptr(const fstreamptr &source);
  fstreamptr(::DESCENT_BOT::LIB::CONTEXT::CContext *context,
             const char *filename, const ::std::ios_base::openmode mode);
  ~fstreamptr();

  fstreamptr &operator=(const fstreamptr &source);

  ::std::fstream &operator*();
  ::std::fstream const &operator*() const;

 private:
  ::DESCENT_BOT::LIB::CONTEXT::CContext *mContext;
  ::std::fstream *mPtr;
  static ::std::map<::std::fstream *, int> mReferences;

  fstreamptr() = delete;
};

}  // namespace LEVELMODEL
}  // namespace LIB
}  // namespace DESCENT_BOT

#endif  // LIB_LEVELMODEL_FSTREAMPTR_H_
