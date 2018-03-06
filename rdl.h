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
#include "src/lib/log/log.h"
#include "fstreamptr.h"
#include "src/lib/math/math.h"

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
   short fileinfo_signature;
   short fileinfo_version;
   int fileinfo_sizeof;
   int header_offset;
   int header_size;
   int editor_offset;
   int editor_size;
   int segment_offset;
   int segment_howmany;
   int segment_sizeof;
   int newseg_verts_offset;
   int newseg_verts_howmany;
   int newseg_verts_sizeof;
   int group_offset;
   int group_howmany;
   int group_sizeof;
   int vertex_offset;
   int vertex_howmany;
   int vertex_sizeof;
   int texture_offset;
   int texture_howmany;
   int texture_sizeof;
   int walls_offset;
   int walls_howmany;
   int walls_sizeof;
   int triggers_offset;
   int triggers_howmany;
   int triggers_sizeof;
   int links_offset;
   int links_howmany;
   int links_sizeof;
   int object_offset;
   int object_howmany;
   int object_sizeof;
   int unused_offset;
   int unused_howmamy;
   int unused_sizeof;
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
