#ifndef __HOGMANAGER_H__
#define __HOGMANAGER_H__

#include <stdlib.h>

#include <vector>

using namespace std;

#include "hog.h"

class HogManager {
public:
  static void Init();
  static void Cleanup();
  
  static CHog &get_Hog(const string &filename);
protected:
private:
  static vector<CHog *> mHogs;
};

#endif
