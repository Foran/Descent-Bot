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
#include "lib/levelmodel/file.h"

#include "lib/context/context.h"

using ::DESCENT_BOT::LIB::CONTEXT::CContext;
using ::DESCENT_BOT::SRC::LIB::LOG::CLog;
using ::DESCENT_BOT::SRC::LIB::LOG::LogType;
using ::std::cout;
using ::std::endl;
using ::std::fstream;
using ::std::ios;
using ::std::streampos;
using ::std::string;

namespace DESCENT_BOT {
namespace LIB {
namespace LEVELMODEL {

CFile::CFile(CContext *context) {
  mContext = context;
  mHog = nullptr;
}

CFile::CFile(CContext *context, const string &filename) {
  mContext = context;
  Load(filename);
}

CFile::CFile(CContext *context, const CHog &hog, const string &filename) {
  mContext = context;
  Load(hog, filename);
}

CFile::CFile(CContext *context, const string &hog,
             const string &filename) {
  mContext = context;
  mHog = &(*CHogManager::fromContext(mContext))[hog];
}

CFile::CFile(CContext *context, const CHog &hog, const string &filename,
             streampos offset, int length) {
  mContext = context;
  mHog = const_cast<CHog *>(&hog);
  mFilename = filename;
  mPos = offset;
  mLength = length;
  cout << "Loading file " << hog.mFilename << "." << mFilename
       << " at offset " << mPos << " for " << mLength << " bytes" << endl;
}

CFile::CFile(const CFile &source) {
  *this = source;
}

CFile::~CFile() {
  mHog = nullptr;
}

CFile &CFile::operator=(const CFile &source) {
  mContext = source.mContext;
  mHog = source.mHog;
  mFilename = source.mFilename;
  mLength = source.mLength;
  mPos = source.mPos;

  return *this;
}

void CFile::Load(const string &filename) {
  mHog = nullptr;
  mFilename = filename;
  mLength = 0;
  mPos = 0;
}

void CFile::Load(const CHog &hog, const string &filename) {
  mHog = const_cast<CHog *>(&hog);
  mFilename = filename;
  mLength = (*mHog)[filename].mLength;
  mPos = (*mHog)[filename].mPos;
}

void CFile::Load(const string &hog, const string &filename) {
  mHog = &(*CHogManager::fromContext(mContext))[hog];
  mFilename = filename;
  mLength = (*mHog)[filename].mLength;
  mPos = (*mHog)[filename].mPos;
}

fstreamptr CFile::get_Stream() {
  fstreamptr file;

  if (mFilename.length() > 0) {
    if (mHog == nullptr) {
      dynamic_cast<CLog*>(mContext->getComponent("Log"))->Write(
        LogType::LogType_Debug, 200, "Opening " + mFilename +
                                     " in direct mode");
      (*file).open(("missions/" + mFilename).c_str(), ios::in | ios::binary);
      mPos = (*file).tellg();
    } else {
      dynamic_cast<CLog*>(mContext->getComponent("Log"))->Write(
        LogType::LogType_Debug, 200, "Opening " + mFilename +
                                     " from " + mHog->mFilename);
      file = mHog->get_Stream(mFilename);
      cout << ((*file).is_open() ? "True" : "False") << endl;
    }
  }

  return file;
}

bool CFile::eof(fstream &file) {
  bool retval = true;

  if (mHog == nullptr) {
    retval = file.eof();
  } else {
    retval = (file.tellg() - mPos) >= mLength;
  }

  return retval;
}

}  // namespace LEVELMODEL
}  // namespace LIB
}  // namespace DESCENT_BOT
