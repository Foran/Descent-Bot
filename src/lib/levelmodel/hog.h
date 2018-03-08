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
#ifndef __HOG_H__
#define __HOG_H__

#include <string>
#include <vector>

namespace DESCENT_BOT {
namespace SRC {
namespace LIB {
namespace LEVELMODEL {
class CFile;
}  // namespace LEVELMODEL
}  // namespace LIB
}  // namespace SRC
}  // namespace DESCENT_BOT

#include "src/lib/log/log.h"
#include "src/lib/levelmodel/file.h"
#include "src/lib/levelmodel/fstreamptr.h"

namespace DESCENT_BOT {
namespace SRC {
namespace LIB {
namespace LEVELMODEL {
class CHogManager;
}  // namespace LEVELMODEL
}  // namespace LIB
}  // namespace SRC
}  // namespace DESCENT_BOT

#include "hogmanager.h"

namespace DESCENT_BOT {
namespace SRC {
namespace LIB {
namespace LEVELMODEL {

class CHog {
 public:
  CHog();
  CHog(const string &filename);
  CHog(const CHog &source);

  ~CHog();

  CHog &operator=(const CHog &source);
  bool operator==(const CHog &source);

  CFile operator[](const string &name) const;

  bool Load(const string &filename);

  vector<string> get_Filenames() const;

 private:
  string mFilename;
  vector<CFile *> mFiles;
  fstreamptr get_Stream() const;
  fstreamptr get_Stream(const string &name) const;

  friend class CFile;
  friend class CHogManager;
};

}  // namespace LEVELMODEL
}  // namespace LIB
}  // namespace SRC
}  // namespace DESCENT_BOT

#endif
