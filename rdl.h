#ifndef __RDL_H__
#define __RDL_H__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <string>
#include <vector>

using namespace std;

#include "hog.h"
#include "file.h"

typedef struct CUBE {
   struct {
      short hi;
      short lo;
   } fixedX;
   struct {
      short hi;
      short lo;
   } fixedY;
   struct {
      short hi;
      short lo;
   } fixedZ;
} CUBE;

class CRdl : public CFile {
 public:
   CRdl();
   CRdl(const string &filename);
   CRdl(const CHog &hog, const string &filename);
   CRdl(const string &hog, const string &filename);
   CRdl(const CRdl &source);
   ~CRdl();
   
   CRdl &operator=(const CRdl &source);
   
   void Reset();
 protected:
   virtual bool LoadByFP(FILE *fp);
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

