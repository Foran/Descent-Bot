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
#ifndef SRC_LIB_LEVELMODEL_FSTREAMPTR_H_
#define SRC_LIB_LEVELMODEL_FSTREAMPTR_H_

#include <fstream>
#include <iostream>
#include <map>

#include "src/lib/log/log.h"

namespace DESCENT_BOT {
namespace SRC {
namespace LIB {
namespace LEVELMODEL {

class fstreamptr {
 public:
  fstreamptr();
  fstreamptr(const fstreamptr &source);
  fstreamptr(const char *filename, const ::std::ios_base::openmode mode);
  ~fstreamptr();

  fstreamptr &operator=(const fstreamptr &source);

  ::std::fstream &operator*();
  ::std::fstream const &operator*() const;

 private:
  ::std::fstream *mPtr;
  static ::std::map<::std::fstream *, int> mReferences;
};

}  // namespace LEVELMODEL
}  // namespace LIB
}  // namespace SRC
}  // namespace DESCENT_BOT

#endif  // SRC_LIB_LEVELMODEL_FSTREAMPTR_H_
