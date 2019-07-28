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
#include "lib/levelmodel/rdl.h"

#include "lib/context/application_context.h"
#include "lib/context/context.h"

using ::DESCENT_BOT::LIB::CONTEXT::CApplicationContext;
using ::DESCENT_BOT::LIB::CONTEXT::CContext;
using ::DESCENT_BOT::LIB::LOG::CLog;
using ::DESCENT_BOT::LIB::LOG::LogType;
using ::DESCENT_BOT::LIB::MATH::DESCENT_SHORTFIXED;
using ::std::dec;
using ::std::endl;
using ::std::hex;
using ::std::ios;
using ::std::ios_base;
using ::std::istream;
using ::std::ostream;
using ::std::string;

namespace DESCENT_BOT {
namespace LIB {
namespace LEVELMODEL {

/**
 * This method compartmentalizes
 * the loading of vertex data in
 * an rdl
 *******************************/
istream &operator>>(istream &input, DESCENT_VERTEX &vertex) {
  input >> vertex.x;
  input >> vertex.y;
  input >> vertex.z;
  return input;
}

/**
 * Handles formatting of serializing
 * a DESCENT_CUBE
 ******************************/
ostream &operator<<(ostream &output, DESCENT_CUBE &cube) {
  output << "Cube.Left = " << cube.left << endl;
  output << "Cube.Top = " << cube.top << endl;
  output << "Cube.Right = " << cube.right << endl;
  output << "Cube.Bottom = " << cube.bottom << endl;
  output << "Cube.Back = " << cube.back << endl;
  output << "Cube.Front = " << cube.front << endl;

  return output;
}

/**
 * This method compartmentalizes
 * the loading of cube data in
 * an rdl
 *******************************/
istream &operator>>(istream &input, DESCENT_CUBE &cube) {
  memset(&cube, 0, sizeof(cube));
  unsigned char mask;
  if (!(input >> mask)) {
    input.setstate(ios::failbit);
    LOG_GLOBAL(LogType::LogType_Debug, 200) << "Failed to read cube mask";
    return input;
  }
  if (mask & 0x01) {
    input.read(reinterpret_cast<char*>(&cube.left), sizeof(cube.left));
    if (input.rdstate() != ios::goodbit) {
      input.setstate(ios::failbit);
      LOG_GLOBAL(LogType::LogType_Debug, 200)
        << "Failed to read the cube.left value";
      return input;
    }
  }
  if (mask & 0x02) {
    input.read(reinterpret_cast<char*>(&cube.top), sizeof(cube.top));
    if (input.rdstate() != ios::goodbit) {
      input.setstate(ios::failbit);
      LOG_GLOBAL(LogType::LogType_Debug, 200)
        << "Failed to read the cube.top value";
      return input;
    }
  }
  if (mask & 0x04) {
    input.read(reinterpret_cast<char*>(&cube.right), sizeof(cube.right));
    if (input.rdstate() != ios::goodbit) {
      input.setstate(ios::failbit);
      LOG_GLOBAL(LogType::LogType_Debug, 200)
        << "Failed to read the cube.right value";
      return input;
    }
  }
  if (mask & 0x08) {
    input.read(reinterpret_cast<char*>(&cube.bottom), sizeof(cube.bottom));
    if (input.rdstate() != ios::goodbit) {
      input.setstate(ios::failbit);
      LOG_GLOBAL(LogType::LogType_Debug, 200)
        << "Failed to read the cube.bottom value";
      return input;
    }
  }
  if (mask & 0x10) {
    input.read(reinterpret_cast<char*>(&cube.back), sizeof(cube.back));
    if (input.rdstate() != ios::goodbit) {
      input.setstate(ios::failbit);
      LOG_GLOBAL(LogType::LogType_Debug, 200)
        << "Failed to read the cube.back value";
      return input;
    }
  }
  if (mask & 0x20) {
    input.read(reinterpret_cast<char*>(&cube.front), sizeof(cube.front));
    if (input.rdstate() != ios::goodbit) {
      input.setstate(ios::failbit);
      LOG_GLOBAL(LogType::LogType_Debug, 200)
        << "Failed to read the cube.front value";
      return input;
    }
  }
  if (mask & 0x40) cube.energy = true;
  for (int i = 0; i < 8; i++) {
    input.read(reinterpret_cast<char *>(&cube.verticies[i]),
               sizeof(cube.verticies[i]));
    if (input.rdstate() != ios::goodbit) {
      input.setstate(ios::failbit);
      LOG_GLOBAL(LogType::LogType_Debug, 200)
        << "Failed to read the cube.verticies[" << i << "] value";
      return input;
    }
  }
  if (cube.energy) {
    input >> cube.energyCenter.special;
    input >> cube.energyCenter.energyCenterNumber;
    input.read(reinterpret_cast<char *>(&cube.energyCenter.value),
               sizeof(cube.energyCenter.value));
    if (input.rdstate() != ios::goodbit) {
      input.setstate(ios::failbit);
      LOG_GLOBAL(LogType::LogType_Debug, 200)
        << "Failed to read the cube.energy value";
      return input;
    }
  }
  input.read(reinterpret_cast<char *>(&cube.staticLight.value.raw),
             sizeof(cube.staticLight.value.raw));
  if (input.rdstate() != ios::goodbit) {
    input.setstate(ios::failbit);
    LOG_GLOBAL(LogType::LogType_Debug, 200) << "Failed to read staticLight";
    return input;
  }
  unsigned char wallmask;
  if (!(input >> wallmask)) {
    input.setstate(ios::failbit);
    return input;
  }
  if (wallmask & 0x01 && !(input >> cube.walls[0])) {
    input.setstate(ios::failbit);
    LOG_GLOBAL(LogType::LogType_Debug, 200) << "Failed to read Wall[0]";
    return input;
  }
  if (wallmask & 0x02 && !(input >> cube.walls[1])) {
    input.setstate(ios::failbit);
    LOG_GLOBAL(LogType::LogType_Debug, 200) << "Failed to read Wall[1]";
    return input;
  }
  if (wallmask & 0x04 && !(input >> cube.walls[2])) {
    input.setstate(ios::failbit);
    LOG_GLOBAL(LogType::LogType_Debug, 200) << "Failed to read Wall[2]";
    return input;
  }
  if (wallmask & 0x08 && !(input >> cube.walls[3])) {
    input.setstate(ios::failbit);
    LOG_GLOBAL(LogType::LogType_Debug, 200) << "Failed to read Wall[3]";
    return input;
  }
  if (wallmask & 0x10 && !(input >> cube.walls[4])) {
    input.setstate(ios::failbit);
    LOG_GLOBAL(LogType::LogType_Debug, 200) << "Failed to read Wall[4]";
    return input;
  }
  if (wallmask & 0x20 && !(input >> cube.walls[5])) {
    input.setstate(ios::failbit);
    LOG_GLOBAL(LogType::LogType_Debug, 200) << "Failed to read Wall[5]";
    return input;
  }
  if (!(mask & 0x01) || wallmask & 0x01) {
    uint16_t texture;
    input.read(reinterpret_cast<char *>(&texture), sizeof(texture));
    if (input.rdstate() != ios::goodbit) {
      input.setstate(ios::failbit);
      LOG_GLOBAL(LogType::LogType_Debug, 200)
        << "Failed to read texture for walls[0]";
      return input;
    }
    if (texture & 0x8000) {
      input.read(reinterpret_cast<char *>(&texture), sizeof(texture));
      if (input.rdstate() != ios::goodbit) {
        input.setstate(ios::failbit);
        LOG_GLOBAL(LogType::LogType_Debug, 200)
          << "Failed to read texture2 for walls[0]";
        return input;
      }
    }
    DESCENT_SHORTFIXED u, v, l;
    input >> u >> v >> l;
    if (input.rdstate() != ios::goodbit) {
      LOG_GLOBAL(LogType::LogType_Debug, 200)
        << "Failed to read uvl for walls[0]";
      return input;
    }
  }
  if (!(mask & 0x02) || wallmask & 0x02) {
    uint16_t texture;
    input.read(reinterpret_cast<char *>(&texture), sizeof(texture));
    if (input.rdstate() != ios::goodbit) {
      input.setstate(ios::failbit);
      LOG_GLOBAL(LogType::LogType_Debug, 200)
        << "Failed to read texture for walls[1]";
      return input;
    }
    if (texture & 0x8000) {
      input.read(reinterpret_cast<char *>(&texture), sizeof(texture));
      if (input.rdstate() != ios::goodbit) {
        input.setstate(ios::failbit);
        LOG_GLOBAL(LogType::LogType_Debug, 200)
          << "Failed to read texture2 for walls[1]";
        return input;
      }
    }
    DESCENT_SHORTFIXED u, v, l;
    if (!(input >> u)) LOG_GLOBAL(LogType::LogType_Debug, 200)
                         << "Failed to read u for walls[1]";
    if (!(input >> v)) LOG_GLOBAL(LogType::LogType_Debug, 200)
                         << "Failed to read v for walls[1]";
    if (!(input >> l)) LOG_GLOBAL(LogType::LogType_Debug, 200)
                         << "Failed to read l for walls[1]";
    if (input.rdstate() != ios::goodbit) {
      LOG_GLOBAL(LogType::LogType_Debug, 200) << "state: "
        << (input.rdstate() & ios::eofbit);
      LOG_GLOBAL(LogType::LogType_Debug, 200)
        << "Failed to read uvl for walls[1]";
      return input;
    }
  }
  if (!(mask & 0x04) || wallmask & 0x04) {
    uint16_t texture;
    input.read(reinterpret_cast<char *>(&texture), sizeof(texture));
    if (input.rdstate() != ios::goodbit) {
      input.setstate(ios::failbit);
      LOG_GLOBAL(LogType::LogType_Debug, 200)
        << "Failed to read texture for walls[2]";
      return input;
    }
    if (texture & 0x8000) {
      input.read(reinterpret_cast<char *>(&texture), sizeof(texture));
      if (input.rdstate() != ios::goodbit) {
        input.setstate(ios::failbit);
        LOG_GLOBAL(LogType::LogType_Debug, 200)
          << "Failed to read texture2 for walls[2]";
        return input;
      }
    }
    DESCENT_SHORTFIXED u, v, l;
    input >> u >> v >> l;
    if (input.rdstate() != ios::goodbit) {
      LOG_GLOBAL(LogType::LogType_Debug, 200)
        << "Failed to read uvl for walls[2]";
      return input;
    }
  }
  if (!(mask & 0x08) || wallmask & 0x08) {
    uint16_t texture;
    input.read(reinterpret_cast<char *>(&texture), sizeof(texture));
    if (input.rdstate() != ios::goodbit) {
      input.setstate(ios::failbit);
      LOG_GLOBAL(LogType::LogType_Debug, 200)
        << "Failed to read texture for walls[3]";
      return input;
    }
    if (texture & 0x8000) {
      input.read(reinterpret_cast<char *>(&texture), sizeof(texture));
      if (input.rdstate() != ios::goodbit) {
        input.setstate(ios::failbit);
        LOG_GLOBAL(LogType::LogType_Debug, 200)
          << "Failed to read texture2 for walls[3]";
        return input;
      }
    }
    DESCENT_SHORTFIXED u, v, l;
    input >> u >> v >> l;
    if (input.rdstate() != ios::goodbit) {
      LOG_GLOBAL(LogType::LogType_Debug, 200)
        << "Failed to read uvl for walls[3]";
      return input;
    }
  }
  if (!(mask & 0x10) || wallmask & 0x10) {
    uint16_t texture;
    input.read(reinterpret_cast<char *>(&texture), sizeof(texture));
    if (input.rdstate() != ios::goodbit) {
      input.setstate(ios::failbit);
      LOG_GLOBAL(LogType::LogType_Debug, 200)
        << "Failed to read texture for walls[4]";
      return input;
    }
    if (texture & 0x8000) {
      input.read(reinterpret_cast<char *>(&texture), sizeof(texture));
      if (input.rdstate() != ios::goodbit) {
        input.setstate(ios::failbit);
        LOG_GLOBAL(LogType::LogType_Debug, 200)
          << "Failed to read texture2 for walls[4]";
        return input;
      }
    }
    DESCENT_SHORTFIXED u, v, l;
    input >> u >> v >> l;
    if (input.rdstate() != ios::goodbit) {
      LOG_GLOBAL(LogType::LogType_Debug, 200)
        << "Failed to read uvl for walls[4]";
      return input;
    }
  }
  if (!(mask & 0x20) || wallmask & 0x20) {
    uint16_t texture;
    input.read(reinterpret_cast<char *>(&texture), sizeof(texture));
    if (input.rdstate() != ios::goodbit) {
      input.setstate(ios::failbit);
      LOG_GLOBAL(LogType::LogType_Debug, 200)
        << "Failed to read texture for walls[4]";
      return input;
    }
    if (texture & 0x8000) {
      input.read(reinterpret_cast<char *>(&texture), sizeof(texture));
      if (input.rdstate() != ios::goodbit) {
        input.setstate(ios::failbit);
        LOG_GLOBAL(LogType::LogType_Debug, 200)
          << "Failed to read texture2 for walls[4]";
        return input;
      }
    }
    DESCENT_SHORTFIXED u, v, l;
    input >> u >> v >> l;
    if (input.rdstate() != ios::goodbit) {
     LOG_GLOBAL(LogType::LogType_Debug, 200)
       << "Failed to read uvl for walls[5]";
     return input;
    }
  }

  return input;
}

/**
 * Default Contructor
 * @see CRdl(const string &filename)
 * @see CRdl(const CHog &hog, const string &filename)
 * @see CRdl(const string &hog, const string &filename)
 * @see CRdl(const CRdl &source)
 ****************************************************/
CRdl::CRdl(CContext *context) : CFile(context) {
  Init();
}

/**
 * Contructor for standalone file
 * @param filename the filename releative to the missions folder
 * @see CRdl()
 * @see CRdl(const CHog &hog, const string &filename)
 * @see CRdl(const string &hog, const string &filename)
 * @see CRdl(const CRdl &source)
 ****************************************************/
CRdl::CRdl(CContext *context, const string &filename) : CFile(context) {
  Init();
  Load(filename);
}

/**
 * Contructor for hog contained file
 * @param hog The hog file that contains the rdl
 * @param filename The name of the file within the hog
 * @see CRdl()
 * @see CRdl(const string &filename)
 * @see CRdl(const string &hog, const string &filename)
 * @see CRdl(const CRdl &source)
 ****************************************************/
CRdl::CRdl(CContext *context, const CHog &hog,
           const string &filename) : CFile(context) {
  Init();
  Load(hog, filename);
}

/**
 * Alternate contructor for hog contained file
 * @param hog Path to the hog file that contains the rdl
 * @param filename The name of the file within the hog
 * @see CRdl()
 * @see CRdl(const string &filename)
 * @see CRdl(const CHog &hog, const string &filename)
 * @see CRdl(const CRdl &source)
 ****************************************************/
CRdl::CRdl(CContext *context, const string &hog,
           const string &filename) : CFile(context) {
  Init();
  Load(hog, filename);
}


/**
 * Default Copy Constructor
 * @param source The source instance to copy
 * @see CRdl()
 * @see CRdl(const string &filename)
 * @see CRdl(const CHog &hog, const string &filename)
 * @see CRdl(const string &hog, const string &filename)
 ****************************************************/
CRdl::CRdl(const CRdl &source) : CFile(source) {
  Init();
  *this = source;
}

CRdl::~CRdl() {
  Reset();
}

CRdl &CRdl::operator=(const CRdl &source) {
  memcpy(&mHeader, &source.mHeader, sizeof(mHeader));

  return *this;
}

void CRdl::Reset() {
  memset(&mHeader, 0, sizeof(mHeader));
  mDescentVerticies.clear();
}

void CRdl::Load(const string &filename) {
  CFile::Load(filename);
  doLoad();
}

void CRdl::Load(const CHog &hog, const string &filename) {
  CFile::Load(hog, filename);
  doLoad();
}

void CRdl::Load(const string &hog, const string &filename) {
  CFile::Load(hog, filename);
  doLoad();
}

void CRdl::doLoad() {
  fstreamptr file = get_Stream();
  LOG(LogType::LogType_Debug, 200) << "Loading " << mFilename << "...";

  if ((*file).is_open()) {
    (*file) >> *this;
    (*file).close();
  } else {
    LOG(LogType::LogType_Debug, 200) << "Failed to open " << mFilename;
  }

  LOG(LogType::LogType_Debug, 200) << "Vertex Count: "
    << mDescentVerticies.size() << ", Cube Count: "
    << mDescentCubes.size();
}

istream &operator>>(istream &input, RDL_HEADER &header) {
  input.read(reinterpret_cast<char *>(&header), sizeof(header));
  return input;
}

ostream &operator<<(ostream &output, RDL_HEADER &header) {
  output << header.signature[0] << header.signature[1] << header.signature[2]
         << header.signature[3] << header.version;
  return output;
}

istream &operator>>(istream &input, RDL_GAMEDATA_HEADER &header) {
  input.read(reinterpret_cast<char *>(&header), 8);
  input.seekg(-8, ios_base::cur);
  if (static_cast<size_t>(header.fileinfo_sizeof) > sizeof(header)) {
    input.setstate(ios::failbit);
  }
  input.read(reinterpret_cast<char *>(&header), header.fileinfo_sizeof);
  return input;
}

ostream &operator<<(ostream &output, RDL_GAMEDATA_HEADER &header) {
  output << "Signature: 0x" << hex << header.fileinfo_signature << "(" << dec
         << header.fileinfo_signature << ")";
  output << "Version: " << header.fileinfo_version;
  output << "FileInfo Size: " << header.fileinfo_sizeof;
  return output;
}

istream &operator>>(istream &input, CRdl &rdl) {
  LOG_GLOBAL(LogType::LogType_Debug, 200) << "File position is now: 0x"
    << hex << input.tellg() << "(" << dec << input.tellg() << ")";
  LOG_GLOBAL(LogType::LogType_Debug, 200) << "Hog pos is: 0x" << hex
    << rdl.mPos << "(" << dec << rdl.mPos << ")";
  LOG_GLOBAL(LogType::LogType_Debug, 200) << "rdl length is: 0x" << hex
    << rdl.mLength << "(" << dec << rdl.mLength << ")";
  input >> rdl.mHeader;
  LOG_GLOBAL(LogType::LogType_Debug, 200) << "File position is now: 0x" << hex
    << input.tellg() << "(" << dec << input.tellg() << ")"  << "Version is: "
    << rdl.mHeader.version;
  if (!memcmp(rdl.mHeader.signature, "LVLP", 4) && rdl.mHeader.version == 1) {
    LOG_GLOBAL(LogType::LogType_Debug, 200) << rdl.mHeader;
    input.seekg(static_cast<uint16_t>(rdl.mPos) +
                rdl.mHeader.mineDataOffset, ios_base::beg);
    LOG_GLOBAL(LogType::LogType_Debug, 200) << "File position is now: 0x"
      << hex << input.tellg() << "(" << dec << input.tellg() << ")";
    char version;
    input >> version;
    uint16_t vertexCount = 0;
    uint16_t cubeCount = 0;
    input.read(reinterpret_cast<char *>(&vertexCount), sizeof(vertexCount));
    input.read(reinterpret_cast<char *>(&cubeCount), sizeof(cubeCount));
    if (!input.eof()) {
      LOG_GLOBAL(LogType::LogType_Debug, 200) << vertexCount << " verticies, "
        << cubeCount << " cubes";
      LOG_GLOBAL(LogType::LogType_Debug, 200) << "File position is now: 0x"
        << hex << input.tellg() << "(" << dec << input.tellg() << ")";
      LOG_GLOBAL(LogType::LogType_Debug, 200) << "Minedata version: "
        << static_cast<int>(version);
      LOG_GLOBAL(LogType::LogType_Debug, 200) << "sizeof(DESCENT_VERTEX) is "
        << sizeof(DESCENT_VERTEX) << ", file.tellg() returned "
        << input.tellg();
      for (unsigned int i = 0; i < vertexCount; i++) {
        LOG_GLOBAL(LogType::LogType_Debug, 200) << "Added a vertex";
        DESCENT_VERTEX vertex;
        if (!(input >> vertex)) break;
        rdl.mDescentVerticies.push_back(vertex);
      }
      LOG_GLOBAL(LogType::LogType_Debug, 200) << "First vertex is: "
        << rdl.mDescentVerticies[0].x << ", " << rdl.mDescentVerticies[0].y
        << ", " << rdl.mDescentVerticies[0].z;
      LOG_GLOBAL(LogType::LogType_Debug, 200) << "Second vertex is: "
        << rdl.mDescentVerticies[1].x << ", " << rdl.mDescentVerticies[1].y
        << ", " << rdl.mDescentVerticies[1].z;
      LOG_GLOBAL(LogType::LogType_Debug, 200) << "Third vertex is: "
        << rdl.mDescentVerticies[2].x << ", " << rdl.mDescentVerticies[2].y
        << ", " << rdl.mDescentVerticies[2].z;
      LOG_GLOBAL(LogType::LogType_Debug, 200) << "Fourth vertex is: "
        << rdl.mDescentVerticies[3].x << ", " << rdl.mDescentVerticies[3].y
        << ", " << rdl.mDescentVerticies[3].z;
      LOG_GLOBAL(LogType::LogType_Debug, 200) << "Fifth vertex is: "
        << rdl.mDescentVerticies[4].x << ", " << rdl.mDescentVerticies[4].y
        << ", " << rdl.mDescentVerticies[4].z;
      LOG_GLOBAL(LogType::LogType_Debug, 200) << "Sixth vertex is: "
        << rdl.mDescentVerticies[5].x << ", " << rdl.mDescentVerticies[5].y
        << ", " << rdl.mDescentVerticies[5].z;
      LOG_GLOBAL(LogType::LogType_Debug, 200) << "Seventh vertex is: "
        << rdl.mDescentVerticies[6].x << ", " << rdl.mDescentVerticies[6].y
        << ", " << rdl.mDescentVerticies[6].z;
      LOG_GLOBAL(LogType::LogType_Debug, 200) << "Eigth vertex is: "
           << rdl.mDescentVerticies[7].x << ", " << rdl.mDescentVerticies[7].y
           << ", " << rdl.mDescentVerticies[7].z;
      LOG_GLOBAL(LogType::LogType_Debug, 200) << "File position is now: "
        << input.tellg() << ", state bit is: " << input.rdstate();
      LOG_GLOBAL(LogType::LogType_Debug, 200) << "We expect to be at: "
        << (static_cast<uint16_t>(rdl.mPos) + rdl.mHeader.mineDataOffset +
            5 + (12 * vertexCount));
      uint16_t i;
      for (i = 0; i < cubeCount && input.rdstate() == ios::goodbit; i++) {
        DESCENT_CUBE cube;
        if (input >> cube) {
          rdl.mDescentCubes.push_back(cube);
        } else {
          LOG_GLOBAL(LogType::LogType_Debug, 200)
            << "An error occured during processing";
          LOG_GLOBAL(LogType::LogType_Debug, 200) << "Dumping cube data: "
            << cube;
        }
      }
      LOG_GLOBAL(LogType::LogType_Debug, 200) << "File position is now: 0x"
        << hex << input.tellg() << "(" << dec << input.tellg() << ")";
      LOG_GLOBAL(LogType::LogType_Debug, 200) << "Processed " << i << " of "
        << cubeCount << " Cubes";

      input.seekg(static_cast<uint16_t>(rdl.mPos) + rdl.mHeader.gameDataOffset,
                  ios_base::beg);
      LOG_GLOBAL(LogType::LogType_Debug, 200) << "File position is now: 0x"
        << hex << input.tellg() << "(" << dec << input.tellg() << ")";
      input >> rdl.mGameDataHeader;
      LOG_GLOBAL(LogType::LogType_Debug, 200) << rdl.mGameDataHeader;
      LOG_GLOBAL(LogType::LogType_Debug, 200) << "File position is now: 0x"
        << hex << input.tellg() << "(" << dec << input.tellg() << ")";
    } else {
      LOG_GLOBAL(LogType::LogType_Debug, 200)
        << "Failed to read Vertix and Cube counts";
    }
  } else {
    LOG_GLOBAL(LogType::LogType_Debug, 200)
      << "Failed to read a valid signature (" << rdl.mHeader << ")";
  }
  return input;
}

void CRdl::Init() {
  memset(&mHeader, 0, sizeof(mHeader));
}

}  // namespace LEVELMODEL
}  // namespace LIB
}  // namespace DESCENT_BOT
