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
