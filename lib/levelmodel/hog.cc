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
#include "lib/levelmodel/hog.h"

#include "lib/context/context.h"

using ::DESCENT_BOT::LIB::CONTEXT::CContext;
using ::DESCENT_BOT::SRC::LIB::LOG::CLog;
using ::DESCENT_BOT::SRC::LIB::LOG::LogType;
using ::std::cout;
using ::std::endl;
using ::std::flush;
using ::std::ios;
using ::std::ios_base;
using ::std::streampos;
using ::std::string;
using ::std::vector;

namespace DESCENT_BOT {
namespace LIB {
namespace LEVELMODEL {

CHog::CHog(CContext *context) {
  mContext = context;
}

CHog::CHog(CContext *context, const string &filename) {
  mContext = context;
  Load(filename);
}

CHog::CHog(const CHog &source) {
  *this = source;
}

CHog::~CHog() {
  for (auto& file : mFiles) {
    delete file;
  }
}

CHog &CHog::operator=(const CHog &source) {
  Load(source.mFilename);
  return *this;
}

bool CHog::operator==(const CHog &source) {
  return mFilename == source.mFilename;
}

CFile CHog::operator[](const string &name) const {
  CFile retval(mContext);

  for (auto& file : mFiles) {
    if (file->mFilename == name) {
      retval = *file;
      break;
    }
  }

  return retval;
}

vector<string> CHog::get_Filenames() const {
  vector<string> retval;

  for (auto& file : mFiles) {
    retval.push_back(file->mFilename);
  }

  return retval;
}

bool CHog::Load(const string &filename) {
  bool retval = true;
  fstreamptr file(mContext, ("missions/" + filename).c_str(),
                  ios::in | ios::binary);
  char signature[3];
  char file_name[13];
  int file_size;

  mFilename = "";
  mFiles.clear();

  if ((*file).is_open()) {
    mFilename = filename;
    if (!(*file).eof() && (*file).read(signature, 3)) {
      if (signature[0] == 'D' && signature[1] == 'H' && signature[2] == 'F') {
        LOG(LogType::LogType_Debug, 100) << "Found a valid signature";
        while (!(*file).eof() && (*file).read(file_name, 13)) {
          string name = file_name;
          if (!(*file).eof() &&
              (*file).read(reinterpret_cast<char *>(&file_size), 4)) {
            streampos pos = (*file).tellg();
            mFiles.push_back(new CFile(mContext, *this, name, pos, file_size));
            LOG(LogType::LogType_Debug, 60)
              << "Found file: " << name << " in hog";
            (*file).seekg(file_size, ios_base::cur);
          }
        }
        if (mFiles.size() > 0) retval = true;
      }
    }
    (*file).close();
  }

  return retval;
}

fstreamptr CHog::get_Stream() const {
  fstreamptr file(mContext, ("missions/" + mFilename).c_str(),
                  ios::in | ios::binary);

  LOG(LogType::LogType_Debug, 200) << "Attempting to open Hog (" <<
                                   mFilename << ") Stream..." <<
                                   ((*file).is_open() ?
                                    "Success" :
                                    "Failure");

  return file;
}

fstreamptr CHog::get_Stream(const string &name) const {
  fstreamptr file = get_Stream();

  if ((*file).is_open()) {
    LOG(LogType::LogType_Debug, 200) << "Before: " << (*file).tellg();
    (*file).seekg((*this)[name].mPos, ios_base::beg);
    LOG(LogType::LogType_Debug, 200) << "Attempting to open Hog (" <<
                                     mFilename << ") Entry (" << name <<
                                     ") Stream..." << (!(*file).eof() ?
                                                      "Success" :
                                                      "Failure");
    LOG(LogType::LogType_Debug, 200) << "After: " << (*file).tellg();
  }

  return file;
}

}  // namespace LEVELMODEL
}  // namespace LIB
}  // namespace DESCENT_BOT
