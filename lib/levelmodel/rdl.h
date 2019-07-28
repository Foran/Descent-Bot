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
#ifndef LIB_LEVELMODEL_RDL_H_
#define LIB_LEVELMODEL_RDL_H_

#include <string.h>

#include <string>
#include <vector>
#include <iostream>

#include "lib/context/context.h"
#include "lib/levelmodel/hog.h"
#include "lib/levelmodel/hogmanager.h"
#include "lib/levelmodel/file.h"
#include "lib/log/log.h"
#include "lib/levelmodel/fstreamptr.h"
#include "lib/math/math.h"

namespace DESCENT_BOT {
namespace LIB {
namespace LEVELMODEL {

typedef struct DESCENT_VERTEX {
  ::DESCENT_BOT::LIB::MATH::DESCENT_FIXED x, y, z;

 private:
  friend class CRdl;
  friend ::std::istream &operator>>(::std::istream &input,
                                    DESCENT_VERTEX &vertex);
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
  ::DESCENT_BOT::LIB::MATH::DESCENT_SHORTFIXED staticLight;
  unsigned char walls[6];

 private:
  friend class CRdl;
  friend ::std::istream &operator>>(::std::istream &input, DESCENT_CUBE &cube);
  friend ::std::ostream &operator<<(::std::ostream &output, DESCENT_CUBE &cube);
} DESCENT_CUBE;

typedef struct RDL_HEADER {
  char signature[4];
  int version;
  int mineDataOffset;
  int gameDataOffset;
  int fileSize;

 private:
  friend class CRdl;
  friend ::std::istream &operator>>(::std::istream &input, RDL_HEADER &header);
  friend ::std::ostream &operator<<(::std::ostream &output, RDL_HEADER &header);
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
  friend ::std::istream &operator>>(::std::istream &input,
                                    RDL_GAMEDATA_HEADER &header);
  friend ::std::ostream &operator<<(::std::ostream &output,
                                    RDL_GAMEDATA_HEADER &header);
} RDL_GAMEDATA_HEADER;

class CRdl : public CFile {
 public:
  explicit CRdl(::DESCENT_BOT::LIB::CONTEXT::CContext *context);
  CRdl(::DESCENT_BOT::LIB::CONTEXT::CContext *context,
       const ::std::string &filename);
  CRdl(::DESCENT_BOT::LIB::CONTEXT::CContext *context,
       const CHog &hog, const ::std::string &filename);
  CRdl(::DESCENT_BOT::LIB::CONTEXT::CContext *context,
       const ::std::string &hog, const ::std::string &filename);
  CRdl(const CRdl &source);
  ~CRdl();

  CRdl &operator=(const CRdl &source);

  void Reset();
  void Load(const ::std::string &filename);
  void Load(const CHog &hog, const ::std::string &filename);
  void Load(const ::std::string &hog, const ::std::string &filename);

 private:
  RDL_HEADER mHeader;
  ::std::vector<DESCENT_VERTEX> mDescentVerticies;
  ::std::vector<DESCENT_CUBE> mDescentCubes;
  RDL_GAMEDATA_HEADER mGameDataHeader;

  void Init();
  void doLoad();
  friend ::std::istream &operator>>(::std::istream &input, CRdl &rdl);
};

}  // namespace LEVELMODEL
}  // namespace LIB
}  // namespace DESCENT_BOT

#endif  // LIB_LEVELMODEL_RDL_H_
