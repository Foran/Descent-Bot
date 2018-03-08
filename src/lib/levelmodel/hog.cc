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
#include "src/lib/levelmodel/hog.h"

using ::DESCENT_BOT::SRC::LIB::LOG::global_Log;

namespace DESCENT_BOT {
namespace SRC {
namespace LIB {
namespace LEVELMODEL {

CHog::CHog() {
}

CHog::CHog(const string &filename) {
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
  CFile retval;

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
  fstreamptr file(("missions/" + filename).c_str(), ios::in | ios::binary);
  char signature[3];
  char file_name[13];
  int file_size;

  mFilename = "";
  mFiles.clear();

  if ((*file).is_open()) {
    mFilename = filename;
    if (!(*file).eof() && (*file).read(signature, 3)) {
      if (signature[0] == 'D' && signature[1] == 'H' && signature[2] == 'F') {
        global_Log.Write(LogType_Debug, 100, "Found a valid signature");
        while (!(*file).eof() && (*file).read(file_name, 13)) {
          string name = file_name;
          if (!(*file).eof() &&
              (*file).read(reinterpret_cast<char *>(&file_size), 4)) {
            streampos pos = (*file).tellg();
            mFiles.push_back(new CFile(*this, name, pos, file_size));
            global_Log.Write(LogType_Debug, 60, "Found file: " + name +
                                                " in hog");
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
  fstreamptr file(("missions/" + mFilename).c_str(), ios::in | ios::binary);

  global_Log.Write(LogType_Debug, 200, "Attempting to open Hog (" + mFilename +
                                       ") Stream..." + ((*file).is_open() ?
                                                        "Success" :
                                                        "Failure"));

  return file;
}

fstreamptr CHog::get_Stream(const string &name) const {
  fstreamptr file = get_Stream();

  if ((*file).is_open()) {
    cout << "Before: " << (*file).tellg() << endl;
    (*file).seekg((*this)[name].mPos, ios_base::beg);
    global_Log.Write(LogType_Debug, 200, "Attempting to open Hog (" +
                                         mFilename + ") Entry (" + name +
                                         ") Stream..." + (!(*file).eof() ?
                                                          "Success" :
                                                          "Failure"));
    cout << "After: " << (*file).tellg() << endl;
  }

  return file;
}

}  // namespace LEVELMODEL
}  // namespace LIB
}  // namespace SRC
}  // namespace DESCENT_BOT
