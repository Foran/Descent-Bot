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
   float get_Value();
   void set_Value(float f);
 private:
   friend class DESCENT_VERTEX;
   friend class CRdl;
   friend istream &operator>>(istream &input, DESCENT_FIXED &fixed);
   friend ostream &operator<<(ostream &output, DESCENT_FIXED &fixed);
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
   int gameDataOffset;
   int fileSize;
 private:
   friend class CRdl;
   friend istream &operator>>(istream &input, RDL_HEADER &header);
   friend ostream &operator<<(ostream &output, RDL_HEADER &header);
} RDL_HEADER;

typedef struct RDL_GAMEDATA_HEADER {
   short signature;
   short version;
   int game_fileinfo_size;
   char mine_filename[15];
   int level;
   int player_offset;
   int player_sizeof;
   int object_offset;
   int object_howmany;
   int object_sizeof;
   int walls_offset;
   int walls_howmany;
   int walls_sizeof;
   int doors_offset;
   int doors_howmany;
   int doors_sizeof;
   int triggers_offset;
   int triggers_howmany;
   int triggers_sizeof;
   int links_offset;
   int links_howmany;
   int links_sizeof;
   int control_offset;
   int control_howmany;
   int control_sizeof;
   int matcen_offset;
   int matcen_howmany;
   int matcen_sizeof;
 private:
   friend class CRdl;
   friend istream &operator>>(istream &input, RDL_GAMEDATA_HEADER &header);
   friend ostream &operator<<(ostream &output, RDL_GAMEDATA_HEADER &header);
} RDL_GAMEDATA_HEADER;

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
   RDL_GAMEDATA_HEADER mGameDataHeader;
   
   void Init();
   void doLoad();
   friend istream &operator>>(istream &input, CRdl &rdl);
};

#endif
