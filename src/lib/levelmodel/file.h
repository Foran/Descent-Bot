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
#ifndef SRC_LIB_LEVELMODEL_FILE_H_
#define SRC_LIB_LEVELMODEL_FILE_H_

#include <string>
#include <vector>
#include <iostream>

// TODO(foran): move forward declaration down int
//              the main namespace block to avoid
//              duplicate declarations
namespace DESCENT_BOT {
namespace SRC {
namespace LIB {
namespace LEVELMODEL {
class CHog;
}  // namespace LEVELMODEL
}  // namespace LIB
}  // namespace SRC
}  // namespace DESCENT_BOT

#include "src/lib/levelmodel/hogmanager.h"
#include "src/lib/levelmodel/hog.h"
#include "src/lib/levelmodel/fstreamptr.h"

namespace DESCENT_BOT {
namespace SRC {
namespace LIB {
namespace LEVELMODEL {

/// Generic file (plain or part of a HOG)
class CFile {
 public:
  /// Default constructor
  explicit CFile(const ::DESCENT_BOT::SRC::LIB::CONTEXT::CContext &context);
  /// Standalone file or file in missions/descent.hog
  CFile(const ::DESCENT_BOT::SRC::LIB::CONTEXT::CContext &context,
        const ::std::string &filename);
  /// File in hog or missions/descent.hog
  CFile(const ::DESCENT_BOT::SRC::LIB::CONTEXT::CContext &context,
        const CHog &hog, const ::std::string &filename);
  CFile(const ::DESCENT_BOT::SRC::LIB::CONTEXT::CContext &context,
        const ::std::string &hog, const ::std::string &filename);
  CFile(const CFile &source);
  virtual ~CFile();

  CFile &operator=(const CFile &source);

  void Load(const ::std::string &filename);
  void Load(const CHog &hog, const ::std::string &filename);
  void Load(const ::std::string &hog, const ::std::string &filename);

 protected:
  ::DESCENT_BOT::SRC::LIB::CONTEXT::CContext *mContext;
  fstreamptr get_Stream();
  bool eof(::std::fstream &file);
  ::std::string mFilename;
  ::std::streampos mPos;
  int mLength;

 private:
  CHog *mHog;
  CFile(const ::DESCENT_BOT::SRC::LIB::CONTEXT::CContext &context,
        const CHog &hog, const ::std::string &filename,
        ::std::streampos offset, int length);

  friend class CHog;
};

}  // namespace LEVELMODEL
}  // namespace LIB
}  // namespace SRC
}  // namespace DESCENT_BOT

#endif  // SRC_LIB_LEVELMODEL_FILE_H_
