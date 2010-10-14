#ifndef __HOG_H__
#define __HOG_H__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <string>
#include <vector>

using namespace std;

class CHog
{
 public:
   CHog();
   CHog(const string &filename);
   CHog(const CHog &source);
   
   ~CHog();
   
   CHog &operator=(const CHog &source);
   
   vector<string> get_Filenames() const;
 protected:
 private:
   string mFilename;
   FILE *get_FilePointer();
};

#endif

