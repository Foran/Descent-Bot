#ifndef __HOGMANAGER_H__
#define __HOGMANAGER_H__

#include <string>
#include <vector>

using namespace std;

class CHog;

#include "hog.h"

class CHogManager {
public:
  CHogManager();
  ~CHogManager();
  
  CHog &operator[](const string &filename);
   static CHogManager get_Instance();
protected:
private:
  static vector<CHog *> mHogs;
  static unsigned int mReferences;
};

#endif
