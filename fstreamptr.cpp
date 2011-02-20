#include "fstreamptr.h"

map<fstream *, int> fstreamptr::mReferences;

fstreamptr::fstreamptr()
{
  mPtr = new fstream();
  mReferences[mPtr] = 0;
}

fstreamptr::fstreamptr(const fstreamptr &source)
{
  *this = source;
}

fstreamptr::fstreamptr(const char *filename, const ios_base::openmode mode)
{
  mPtr = new fstream(filename, mode);
  mReferences[mPtr] = 0;
}

fstreamptr::~fstreamptr()
{
  mReferences[mPtr]--;
  if(mReferences[mPtr] == 0) {
    mReferences.erase(mPtr);
    delete mPtr;
  }
}

fstreamptr &fstreamptr::operator=(const fstreamptr &source)
{
  mPtr = source.mPtr;
  mReferences[mPtr]++;
  
  return *this;
}

fstream &fstreamptr::operator*()
{
  return *mPtr;
}

fstream const &fstreamptr::operator*() const
{
  return *mPtr;
}
