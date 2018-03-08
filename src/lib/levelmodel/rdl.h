/****************************************************
 * Copyright 2018 Ben M. Ward
 *
 * This work is licensed under the Creative
 * Commons Attribution-NonCommercial-ShareAlike
 * 3.0 Unported License. To view a copy of this
 * license, visit
 * http://creativecommons.org/licenses/by-nc-sa/3.0/
 * or send a letter to Creative Commons, 444
 * Castro Street, Suite 900, Mountain View,
 * California, 94041, USA.
 ***************************************************/
#ifndef SRC_LIB_LEVELMODEL_RDL_H_
#define SRC_LIB_LEVELMODEL_RDL_H_

#include <string.h>

#include <string>
#include <vector>
#include <iostream>

#include "src/lib/levelmodel/hog.h"
#include "src/lib/levelmodel/hogmanager.h"
#include "src/lib/levelmodel/file.h"
#include "src/lib/log/log.h"
#include "src/lib/levelmodel/fstreamptr.h"
#include "src/lib/math/math.h"

namespace DESCENT_BOT {
namespace SRC {
namespace LIB {
namespace LEVELMODEL {

typedef struct DESCENT_VERTEX {
  DESCENT_FIXED x, y, z;

 private:
  friend class CRdl;
  friend istream &operator>>(istream &input, DESCENT_VERTEX &vertex);
} DESCENT_VERTEX;

typedef struct DESCENT_CUBE {
  uint16_t left;
  uint16_t top;
  uint16_t right;
  uint16_t bottom;
  uint16_t back;
  uint16_t front;
  bool energy;
  uint16_t verticies[8];
  struct {
    unsigned char special;
    char energyCenterNumber;
    int16_t value;
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
  int16_t fileinfo_signature;
  int16_t fileinfo_version;
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
  explicit CRdl(const string &filename);
  CRdl(const CHog &hog, const string &filename);
  CRdl(const string &hog, const string &filename);
  CRdl(const CRdl &source);
  ~CRdl();

  CRdl &operator=(const CRdl &source);

  void Reset();
  void Load(const string &filename);
  void Load(const CHog &hog, const string &filename);
  void Load(const string &hog, const string &filename);

 private:
  RDL_HEADER mHeader;
  vector<DESCENT_VERTEX> mDescentVerticies;
  vector<DESCENT_CUBE> mDescentCubes;
  RDL_GAMEDATA_HEADER mGameDataHeader;

  void Init();
  void doLoad();
  friend istream &operator>>(istream &input, CRdl &rdl);
};

}  // namespace LEVELMODEL
}  // namespace LIB
}  // namespace SRC
}  // namespace DESCENT_BOT

#endif  // SRC_LIB_LEVELMODEL_RDL_H_
