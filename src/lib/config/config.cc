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
#include "src/lib/config/config.h"

#include <fcntl.h>
#include <google/protobuf/text_format.h>
#include <google/protobuf/io/zero_copy_stream_impl.h>


namespace DESCENT_BOT {
namespace SRC {
namespace LIB {
namespace CONFIG {

using ::std::string;
using ::std::vector;
using PROTO::Config;

using ::DESCENT_BOT::SRC::LIB::CONTEXT::CContext;

/**
 * Default constructor of the CConfig class
 * @see CConfig(const string filename)
 * @see CConfig(const CConfig &source)
 *****************************************/
CConfig::CConfig(CContext &context) {
  Initialize();
  Reset();
}

/**
 * Destructor
 *************************************/
CConfig::~CConfig() {
  clearInstance();
}

string CConfig::getName() const {
  return "Config";
}

/**
 * Clear Instance called at exit
 *************************************/
void CConfig::clearInstance() {
}

void CConfig::Initialize() {
}

bool CConfig::Load(const string filename) {
  bool retval = false;

  Reset();
  int fd = open(filename.c_str(), O_RDONLY);
  if (fd > 0) {
    ::google::protobuf::io::FileInputStream input(fd);
    if (!::google::protobuf::TextFormat::Parse(&input, &mConfig)) {
      // Log error
    } else {
      retval = true;
    }
  }

  return retval;
}

void CConfig::Reset() {
  mConfig.Clear();
}

}  // namespace CONFIG
}  // namespace LIB
}  // namespace SRC
}  // namespace DESCENT_BOT
