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
#include "src/lib/levelmodel/rdl.h"

using ::DESCENT_BOT::SRC::LIB::CONTEXT::CContext;
using ::DESCENT_BOT::SRC::LIB::LOG::CLog;
using ::DESCENT_BOT::SRC::LIB::LOG::LogType;
using ::DESCENT_BOT::SRC::LIB::MATH::DESCENT_SHORTFIXED;
using ::std::cout;
using ::std::dec;
using ::std::endl;
using ::std::hex;
using ::std::ios;
using ::std::ios_base;
using ::std::istream;
using ::std::ostream;
using ::std::string;

namespace DESCENT_BOT {
namespace SRC {
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
    cout << "Failed to read cube mask" << endl;
    return input;
  }
  if (mask & 0x01) {
    input.read(reinterpret_cast<char*>(&cube.left), sizeof(cube.left));
    if (input.rdstate() != ios::goodbit) {
      input.setstate(ios::failbit);
      cout << "Failed to read the cube.left value" << endl;
      return input;
    }
  }
  if (mask & 0x02) {
    input.read(reinterpret_cast<char*>(&cube.top), sizeof(cube.top));
    if (input.rdstate() != ios::goodbit) {
      input.setstate(ios::failbit);
      cout << "Failed to read the cube.top value" << endl;
      return input;
    }
  }
  if (mask & 0x04) {
    input.read(reinterpret_cast<char*>(&cube.right), sizeof(cube.right));
    if (input.rdstate() != ios::goodbit) {
      input.setstate(ios::failbit);
      cout << "Failed to read the cube.right value" << endl;
      return input;
    }
  }
  if (mask & 0x08) {
    input.read(reinterpret_cast<char*>(&cube.bottom), sizeof(cube.bottom));
    if (input.rdstate() != ios::goodbit) {
      input.setstate(ios::failbit);
      cout << "Failed to read the cube.bottom value" << endl;
      return input;
    }
  }
  if (mask & 0x10) {
    input.read(reinterpret_cast<char*>(&cube.back), sizeof(cube.back));
    if (input.rdstate() != ios::goodbit) {
      input.setstate(ios::failbit);
      cout << "Failed to read the cube.back value" << endl;
      return input;
    }
  }
  if (mask & 0x20) {
    input.read(reinterpret_cast<char*>(&cube.front), sizeof(cube.front));
    if (input.rdstate() != ios::goodbit) {
      input.setstate(ios::failbit);
      cout << "Failed to read the cube.front value" << endl;
      return input;
    }
  }
  if (mask & 0x40) cube.energy = true;
  for (int i = 0; i < 8; i++) {
    input.read(reinterpret_cast<char *>(&cube.verticies[i]),
               sizeof(cube.verticies[i]));
    if (input.rdstate() != ios::goodbit) {
      input.setstate(ios::failbit);
      cout << "Failed to read the cube.verticies[" << i << "] value" << endl;
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
      cout << "Failed to read the cube.energy value" << endl;
      return input;
    }
  }
  input.read(reinterpret_cast<char *>(&cube.staticLight.value.raw),
             sizeof(cube.staticLight.value.raw));
  if (input.rdstate() != ios::goodbit) {
    input.setstate(ios::failbit);
    cout << "Failed to read staticLight" << endl;
    return input;
  }
  unsigned char wallmask;
  if (!(input >> wallmask)) {
    input.setstate(ios::failbit);
    return input;
  }
  if (wallmask & 0x01 && !(input >> cube.walls[0])) {
    input.setstate(ios::failbit);
    cout << "Failed to read Wall[0]" << endl;
    return input;
  }
  if (wallmask & 0x02 && !(input >> cube.walls[1])) {
    input.setstate(ios::failbit);
    cout << "Failed to read Wall[1]" << endl;
    return input;
  }
  if (wallmask & 0x04 && !(input >> cube.walls[2])) {
    input.setstate(ios::failbit);
    cout << "Failed to read Wall[2]" << endl;
    return input;
  }
  if (wallmask & 0x08 && !(input >> cube.walls[3])) {
    input.setstate(ios::failbit);
    cout << "Failed to read Wall[3]" << endl;
    return input;
  }
  if (wallmask & 0x10 && !(input >> cube.walls[4])) {
    input.setstate(ios::failbit);
    cout << "Failed to read Wall[4]" << endl;
    return input;
  }
  if (wallmask & 0x20 && !(input >> cube.walls[5])) {
    input.setstate(ios::failbit);
    cout << "Failed to read Wall[5]" << endl;
    return input;
  }
  if (!(mask & 0x01) || wallmask & 0x01) {
    uint16_t texture;
    input.read(reinterpret_cast<char *>(&texture), sizeof(texture));
    if (input.rdstate() != ios::goodbit) {
      input.setstate(ios::failbit);
      cout << "Failed to read texture for walls[0]" << endl;
      return input;
    }
    if (texture & 0x8000) {
      input.read(reinterpret_cast<char *>(&texture), sizeof(texture));
      if (input.rdstate() != ios::goodbit) {
        input.setstate(ios::failbit);
        cout << "Failed to read texture2 for walls[0]" << endl;
        return input;
      }
    }
    DESCENT_SHORTFIXED u, v, l;
    input >> u >> v >> l;
    if (input.rdstate() != ios::goodbit) {
      cout << "Failed to read uvl for walls[0]" << endl;
      return input;
    }
  }
  if (!(mask & 0x02) || wallmask & 0x02) {
    uint16_t texture;
    input.read(reinterpret_cast<char *>(&texture), sizeof(texture));
    if (input.rdstate() != ios::goodbit) {
      input.setstate(ios::failbit);
      cout << "Failed to read texture for walls[1]" << endl;
      return input;
    }
    if (texture & 0x8000) {
      input.read(reinterpret_cast<char *>(&texture), sizeof(texture));
      if (input.rdstate() != ios::goodbit) {
        input.setstate(ios::failbit);
        cout << "Failed to read texture2 for walls[1]" << endl;
        return input;
      }
    }
    DESCENT_SHORTFIXED u, v, l;
    if (!(input >> u)) cout << "Failed to read u for walls[1]" << endl;
    if (!(input >> v)) cout << "Failed to read v for walls[1]" << endl;
    if (!(input >> l)) cout << "Failed to read l for walls[1]" << endl;
    if (input.rdstate() != ios::goodbit) {
      cout << "state: " << (input.rdstate() & ios::eofbit) << endl;
      cout << "Failed to read uvl for walls[1]" << endl;
      return input;
    }
  }
  if (!(mask & 0x04) || wallmask & 0x04) {
    uint16_t texture;
    input.read(reinterpret_cast<char *>(&texture), sizeof(texture));
    if (input.rdstate() != ios::goodbit) {
      input.setstate(ios::failbit);
      cout << "Failed to read texture for walls[2]" << endl;
      return input;
    }
    if (texture & 0x8000) {
      input.read(reinterpret_cast<char *>(&texture), sizeof(texture));
      if (input.rdstate() != ios::goodbit) {
        input.setstate(ios::failbit);
        cout << "Failed to read texture2 for walls[2]" << endl;
        return input;
      }
    }
    DESCENT_SHORTFIXED u, v, l;
    input >> u >> v >> l;
    if (input.rdstate() != ios::goodbit) {
      cout << "Failed to read uvl for walls[2]" << endl;
      return input;
    }
  }
  if (!(mask & 0x08) || wallmask & 0x08) {
    uint16_t texture;
    input.read(reinterpret_cast<char *>(&texture), sizeof(texture));
    if (input.rdstate() != ios::goodbit) {
      input.setstate(ios::failbit);
      cout << "Failed to read texture for walls[3]" << endl;
      return input;
    }
    if (texture & 0x8000) {
      input.read(reinterpret_cast<char *>(&texture), sizeof(texture));
      if (input.rdstate() != ios::goodbit) {
        input.setstate(ios::failbit);
        cout << "Failed to read texture2 for walls[3]" << endl;
        return input;
      }
    }
    DESCENT_SHORTFIXED u, v, l;
    input >> u >> v >> l;
    if (input.rdstate() != ios::goodbit) {
      cout << "Failed to read uvl for walls[3]" << endl;
      return input;
    }
  }
  if (!(mask & 0x10) || wallmask & 0x10) {
    uint16_t texture;
    input.read(reinterpret_cast<char *>(&texture), sizeof(texture));
    if (input.rdstate() != ios::goodbit) {
      input.setstate(ios::failbit);
      cout << "Failed to read texture for walls[4]" << endl;
      return input;
    }
    if (texture & 0x8000) {
      input.read(reinterpret_cast<char *>(&texture), sizeof(texture));
      if (input.rdstate() != ios::goodbit) {
        input.setstate(ios::failbit);
        cout << "Failed to read texture2 for walls[4]" << endl;
        return input;
      }
    }
    DESCENT_SHORTFIXED u, v, l;
    input >> u >> v >> l;
    if (input.rdstate() != ios::goodbit) {
      cout << "Failed to read uvl for walls[4]" << endl;
      return input;
    }
  }
  if (!(mask & 0x20) || wallmask & 0x20) {
    uint16_t texture;
    input.read(reinterpret_cast<char *>(&texture), sizeof(texture));
    if (input.rdstate() != ios::goodbit) {
      input.setstate(ios::failbit);
      cout << "Failed to read texture for walls[4]" << endl;
      return input;
    }
    if (texture & 0x8000) {
      input.read(reinterpret_cast<char *>(&texture), sizeof(texture));
      if (input.rdstate() != ios::goodbit) {
        input.setstate(ios::failbit);
        cout << "Failed to read texture2 for walls[4]" << endl;
        return input;
      }
    }
    DESCENT_SHORTFIXED u, v, l;
    input >> u >> v >> l;
    if (input.rdstate() != ios::goodbit) {
     cout << "Failed to read uvl for walls[5]" << endl;
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
CRdl::CRdl(CContext &context) : CFile(context) {
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
CRdl::CRdl(CContext &context, const string &filename) : CFile(context) {
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
CRdl::CRdl(CContext &context, const CHog &hog, const string &filename) : CFile(context) {
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
CRdl::CRdl(CContext &context, const string &hog, const string &filename) : CFile(context) {
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
  cout << "Loading " << mFilename << "..." << endl;

  if ((*file).is_open()) {
    (*file) >> *this;
    (*file).close();
  } else {
    cout << "Failed to open " << mFilename << endl;
  }

  cout << "Vertex Count: " << mDescentVerticies.size() << ", Cube Count: "
       << mDescentCubes.size() << endl;
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
         << header.fileinfo_signature << ")" << endl;
  output << "Version: " << header.fileinfo_version << endl;
  output << "FileInfo Size: " << header.fileinfo_sizeof << endl;
  return output;
}

istream &operator>>(istream &input, CRdl &rdl) {
  cout << "File position is now: 0x" << hex << input.tellg() << "(" << dec
       << input.tellg() << ")" << endl;
  cout << "Hog pos is: 0x" << hex << rdl.mPos << "(" << dec << rdl.mPos
       << ")"  << endl;
  cout << "rdl length is: 0x" << hex << rdl.mLength << "(" << dec
       << rdl.mLength << ")"  << endl;
  input >> rdl.mHeader;
  cout << "File position is now: 0x" << hex << input.tellg() << "(" << dec
       << input.tellg() << ")" << endl << "Version is: "
       << rdl.mHeader.version << endl;
  if (!memcmp(rdl.mHeader.signature, "LVLP", 4) && rdl.mHeader.version == 1) {
    cout << rdl.mHeader << endl;
    input.seekg(static_cast<uint16_t>(rdl.mPos) +
                rdl.mHeader.mineDataOffset, ios_base::beg);
    cout << "File position is now: 0x" << hex << input.tellg() << "(" << dec
         << input.tellg() << ")" << endl;
    char version;
    input >> version;
    uint16_t vertexCount = 0;
    uint16_t cubeCount = 0;
    input.read(reinterpret_cast<char *>(&vertexCount), sizeof(vertexCount));
    input.read(reinterpret_cast<char *>(&cubeCount), sizeof(cubeCount));
    if (!input.eof()) {
      cout << vertexCount << " verticies, " << cubeCount << " cubes" << endl;
      cout << "File position is now: 0x" << hex << input.tellg() << "("
           << dec << input.tellg() << ")" << endl;
      cout << "Minedata version: " << static_cast<int>(version) << endl;
      cout << "sizeof(DESCENT_VERTEX) is " << sizeof(DESCENT_VERTEX)
           << ", file.tellg() returned " << input.tellg() << endl;
      for (unsigned int i = 0; i < vertexCount; i++) {
        dynamic_cast<CLog*>(rdl.mContext->getComponent("Log"))->Write(LogType::LogType_Debug, 200, "Added a vertex");
        DESCENT_VERTEX vertex;
        if (!(input >> vertex)) break;
        rdl.mDescentVerticies.push_back(vertex);
      }
      cout << "First vertex is: " << rdl.mDescentVerticies[0].x << ", "
           << rdl.mDescentVerticies[0].y << ", "
           << rdl.mDescentVerticies[0].z << endl;
      cout << "Second vertex is: " << rdl.mDescentVerticies[1].x << ", "
           << rdl.mDescentVerticies[1].y << ", "
           << rdl.mDescentVerticies[1].z << endl;
      cout << "Third vertex is: " << rdl.mDescentVerticies[2].x << ", "
           << rdl.mDescentVerticies[2].y << ", "
           << rdl.mDescentVerticies[2].z << endl;
      cout << "Fourth vertex is: " << rdl.mDescentVerticies[3].x << ", "
           << rdl.mDescentVerticies[3].y << ", "
           << rdl.mDescentVerticies[3].z << endl;
      cout << "Fifth vertex is: " << rdl.mDescentVerticies[4].x << ", "
           << rdl.mDescentVerticies[4].y << ", "
           << rdl.mDescentVerticies[4].z << endl;
      cout << "Sixth vertex is: " << rdl.mDescentVerticies[5].x << ", "
           << rdl.mDescentVerticies[5].y << ", "
           << rdl.mDescentVerticies[5].z << endl;
      cout << "Seventh vertex is: " << rdl.mDescentVerticies[6].x << ", "
           << rdl.mDescentVerticies[6].y << ", "
           << rdl.mDescentVerticies[6].z << endl;
      cout << "Eigth vertex is: " << rdl.mDescentVerticies[7].x << ", "
           << rdl.mDescentVerticies[7].y << ", "
           << rdl.mDescentVerticies[7].z << endl;
      cout << "File position is now: " << input.tellg() << ", state bit is: "
           << input.rdstate() << endl;
      cout << "We expect to be at: "
           << (static_cast<uint16_t>(rdl.mPos) + rdl.mHeader.mineDataOffset +
               5 + (12 * vertexCount)) << endl;
      uint16_t i;
      for (i = 0; i < cubeCount && input.rdstate() == ios::goodbit; i++) {
        DESCENT_CUBE cube;
        if (input >> cube) {
          rdl.mDescentCubes.push_back(cube);
        } else {
          cout << "An error occured during processing" << endl;
          cout << "Dumping cube data: " << cube << endl;
        }
      }
      cout << "File position is now: 0x" << hex << input.tellg() << "("
           << dec << input.tellg() << ")" << endl;
      cout << "Processed " << i << " of " << cubeCount << " Cubes" << endl;

      input.seekg(static_cast<uint16_t>(rdl.mPos) + rdl.mHeader.gameDataOffset,
                  ios_base::beg);
      cout << "File position is now: 0x" << hex << input.tellg() << "("
           << dec << input.tellg() << ")" << endl;
      input >> rdl.mGameDataHeader;
      cout << rdl.mGameDataHeader << endl;
      cout << "File position is now: 0x" << hex << input.tellg() << "("
           << dec << input.tellg() << ")" << endl;
    } else {
      cout << "Failed to read Vertix and Cube counts" << endl;
    }
  } else {
    cout << "Failed to read a valid signature (" << rdl.mHeader << ")" << endl;
  }
  return input;
}

void CRdl::Init() {
  memset(&mHeader, 0, sizeof(mHeader));
}

}  // namespace LEVELMODEL
}  // namespace LIB
}  // namespace SRC
}  // namespace DESCENT_BOT
