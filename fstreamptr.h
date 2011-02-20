#ifndef __FSTREAMPTR_H__
#define __FSTREAMPTR_H__

#include <fstream>
#include <iostream>
#include <map>

using namespace std;

#include "log.h"

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
