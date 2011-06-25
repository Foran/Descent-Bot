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
#include "fstreamptr.h"

map<fstream *, int> fstreamptr::mReferences;

fstreamptr::fstreamptr()
{
  mPtr = new fstream();
  mReferences[mPtr] = 1;
   cout << "Initial fstreamptf() called" << endl;
}

fstreamptr::fstreamptr(const fstreamptr &source)
{
   cout << "Copy constructor for fstreamptr called" << endl;
  *this = source;
}

fstreamptr::fstreamptr(const char *filename, const ios_base::openmode mode)
{
  mPtr = new fstream(filename, mode);
  mReferences[mPtr] = 1;
   cout << "Initial fstreamptr(filename, mode) called" << endl;
}

fstreamptr::~fstreamptr()
{
  mReferences[mPtr]--;
   cout << "Destructor for fstreamptr called with a reference count of " << mReferences[mPtr] << endl;
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
