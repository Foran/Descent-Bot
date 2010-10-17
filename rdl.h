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

typedef struct DESCENT_FIXED 
{
   union {
      int raw;
      struct {
	 short hi;
	 unsigned short lo;
      } parts;
   } value;
} DESCENT_FIXED;

typedef struct DESCENT_VERTEX 
{
   DESCENT_FIXED x, y, z;
} DESCENT_VERTEX;

typedef struct DESCENT_CUBE 
{
   unsigned short left;
   unsigned short top;
   unsigned short right;
   unsigned short bottom;
   unsigned short back;
   unsigned short front;
   bool energy;
   unsigned short verticies[8];
   unsigned char special;
   char energyCenterNumber;
   short value;
   struct {
      signed hi: 4;
      unsigned lo: 12;
   } staticLight;
   
} DESCENT_CUBE;

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
   
   vector<DESCENT_VERTEX> mDescentVerticies;
   vector<DESCENT_CUBE> mDescentCubes;
   
   void Init();
};

#endif

