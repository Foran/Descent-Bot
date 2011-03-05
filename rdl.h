#ifndef __RDL_H__
#define __RDL_H__

#include <string.h>

#include <string>
#include <vector>
#include <iostream>

using namespace std;

#include "hog.h"
#include "hogmanager.h"
#include "file.h"
#include "log.h"
#include "fstreamptr.h"

typedef struct DESCENT_FIXED 
{
   union {
      int raw;
      struct {
	 short hi;
	 unsigned short lo;
      } parts;
   } value;
 private:
   friend class DESCENT_VERTEX;
   friend class CRdl;
   friend istream &operator>>(istream &input, DESCENT_FIXED &fixed);
} DESCENT_FIXED;

typedef struct DESCENT_SHORTFIXED
{
   union {
      short raw;
      struct {
	 signed hi: 4;
	 unsigned lo: 12;
      } parts;
   } value;
 private:
   friend class DESCENT_VERTEX;
   friend class CRdl;
   friend istream &operator>>(istream &input, DESCENT_SHORTFIXED &fixed);
} DESCENT_SHORTFIXED;

typedef struct DESCENT_VERTEX 
{
   DESCENT_FIXED x, y, z;
 private:
   friend class CRdl;
   friend istream &operator>>(istream &input, DESCENT_VERTEX &vertex);
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
   struct {
      unsigned char special;
      char energyCenterNumber;
      short value;
   } energyCenter;
   DESCENT_SHORTFIXED staticLight;
   unsigned char walls[6];
 private:
   friend class CRdl;
   friend istream &operator>>(istream &input, DESCENT_CUBE &cube);
   friend ostream &operator<<(ostream &output, DESCENT_CUBE &cube);
} DESCENT_CUBE;

typedef struct RDL_HEADER {
   char signature[4];
   int version;
   int mineDataOffset;
   int objectsOffset;
   int fileSize;
 private:
   friend class CRdl;
   friend istream &operator>>(istream &input, RDL_HEADER &header);
   friend ostream &operator<<(ostream &output, RDL_HEADER &header);
} RDL_HEADER;

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
   void Load(const string &filename);
   void Load(const CHog &hog, const string &filename);
   void Load(const string &hog, const string &filename);
 protected:
 private:
     RDL_HEADER mHeader;   
   vector<DESCENT_VERTEX> mDescentVerticies;
   vector<DESCENT_CUBE> mDescentCubes;
   
   void Init();
   void doLoad();
   friend istream &operator>>(istream &input, CRdl &rdl);
};

#endif
