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
#ifndef LIB_LEVELMODEL_FILE_H_
#define LIB_LEVELMODEL_FILE_H_

#include <string>
#include <vector>
#include <iostream>
#include <memory>

namespace DESCENT_BOT {
namespace LIB {
namespace LEVELMODEL {
class CHog;
}  // namespace LEVELMODEL
}  // namespace LIB
}  // namespace DESCENT_BOT

#include "lib/context/context.h"
#include "lib/levelmodel/hogmanager.h"
#include "lib/levelmodel/hog.h"
#include "lib/levelmodel/fstreamptr.h"

namespace DESCENT_BOT {
namespace LIB {
namespace LEVELMODEL {

/// Generic file (plain or part of a HOG)
class CFile {
 public:
  /// Default constructor
  explicit CFile(::DESCENT_BOT::LIB::CONTEXT::CContext *context);
  /// Standalone file or file in missions/descent.hog
  CFile(::DESCENT_BOT::LIB::CONTEXT::CContext *context,
        const ::std::string &filename);
  /// File in hog or missions/descent.hog
  CFile(::DESCENT_BOT::LIB::CONTEXT::CContext *context,
        const CHog &hog, const ::std::string &filename);
  CFile(::DESCENT_BOT::LIB::CONTEXT::CContext *context,
        const ::std::string &hog, const ::std::string &filename);
  CFile(const CFile &source);
  virtual ~CFile();

  CFile &operator=(const CFile &source);

  void Load(const ::std::string &filename);
  void Load(const CHog &hog, const ::std::string &filename);
  void Load(const ::std::string &hog, const ::std::string &filename);

 protected:
  ::DESCENT_BOT::LIB::CONTEXT::CContext *mContext;
  fstreamptr get_Stream();
  bool eof(::std::fstream &file);
  ::std::string mFilename;
  ::std::streampos mPos;
  int mLength;

 private:
  CHog *mHog;
  CFile(::DESCENT_BOT::LIB::CONTEXT::CContext *context,
        const CHog &hog, const ::std::string &filename,
        ::std::streampos offset, int length);
  static ::std::unique_ptr<CFile> createInstance(
        ::DESCENT_BOT::LIB::CONTEXT::CContext *context,
        const CHog &hog, const ::std::string &filename,
        ::std::streampos offset, int length);

  friend class CHog;
};

}  // namespace LEVELMODEL
}  // namespace LIB
}  // namespace DESCENT_BOT

#endif  // LIB_LEVELMODEL_FILE_H_
