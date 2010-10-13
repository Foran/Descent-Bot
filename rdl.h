#ifndef __RDL_H__
#define __RDL_H__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <string>
#include <vector>

using namespace std;

#include "hog.h"

class CRdl {
 public:
   CRdl();
   CRdl(const string &filename);
   CRdl(const CHog &hog, const string &filename);
   CRdl(const string &hog, const string &filename);
   CRdl(const CRdl &source);
   ~CRdl();
   
   CRdl &operator=(const CRdl &source);
   
   void Reset();
   bool Load(const string &filename);
   bool Load(const CHog &hog, const string &filename);
   bool Load(const string &hog, const string &filename);
 protected:
 private:
   struct {
      char signature[4];
      long version;
      long mineDataOffset;
      long objectsOffset;
      long fileSize;
   } mHeader;
   
   void Init();
};

#endif

