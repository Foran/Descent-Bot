/****************************************************
 * This work is licensed under the Creative
 * Commons Attribution-NonCommercial-ShareAlike
 * 3.0 Unported License. To view a copy of this
 * license, visit
 * http://creativecommons.org/licenses/by-nc-sa/3.0/
 * or send a letter to Creative Commons, 444
 * Castro Street, Suite 900, Mountain View,
 * California, 94041, USA.
 ***************************************************/
#include "src/lib/log/log_driver_file.h"

namespace DESCENT_BOT {
namespace SRC {
namespace LIB {
namespace LOG {

/**
 * Default Constructor
 **********************************************/
CLogDriverFile::CLogDriverFile() {
  mLevel = 100;
  mType = LogType_Debug;
  mName = "Default File";
}

/**
 * Setter for the Name property.
 * @param name Unique name of the log driver instance.
 * @see get_Name
 **********************************************/
void CLogDriverFile::set_Name(const string &name) {
  mName = name;
}

/**
 * Getter for the Name property.
 * @returns Unique name of the log driver instance.
 * @see get_Name
 **********************************************/
string CLogDriverFile::get_Name() const {
  return mName;
}

string CLogDriverFile::get_Driver() const {
  return "File";
}

void CLogDriverFile::set_Type(const string &type) {
  mType = GetLogType(type);
}

void CLogDriverFile::set_Type(const LogType &type) {
  mType = type;
}

LogType CLogDriverFile::get_Type() const {
  return mType;
}

void CLogDriverFile::set_Level(const string &level) {
  mLevel = atol(level.c_str());
}

void CLogDriverFile::set_Level(const int &level) {
  mLevel = level;
}

int CLogDriverFile::get_Level() const {
  return mLevel;
}

void CLogDriverFile::set_Option(const string &name, const string &value) {
  if ("File" == name) {
    mFilename = value;
    remove((string("logs/") + mFilename).c_str());
  }
}

string CLogDriverFile::get_Option(const string &name) {
  string retval;

  if ("File" == name) {
    retval = mFilename;
  }

  return retval;
}

bool CLogDriverFile::Write(int level, const string &message) {
  bool retval = false;
  ofstream file((string("logs/") + mFilename).c_str(),
                ofstream::out | ofstream::app);
  if (file.is_open()) {
    retval = true;
    if (level <= mLevel) {
      file << "[" << mName << ": " << mType << "(" << level << ")]: "
           <<  message << endl;
    }
    file.close();
  }

  return retval;
}

}  // namespace LOG
}  // namespace LIB
}  // namespace SRC
}  // namespace DESCENT_BOT
