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
#ifndef __FSTREAMPTR_H__
#define __FSTREAMPTR_H__

#include <fstream>
#include <iostream>
#include <map>

using namespace std;

#include "src/lib/log/log.h"

class fstreamptr {
public:
  fstreamptr();
  fstreamptr(const fstreamptr &source);
  fstreamptr(const char *filename, const ios_base::openmode mode);
  ~fstreamptr();
  
  fstreamptr &operator=(const fstreamptr &source);
  
  fstream &operator*();
  fstream const &operator*() const;
protected:
private:
  fstream *mPtr;
  static map<fstream *, int> mReferences;
};

#endif
