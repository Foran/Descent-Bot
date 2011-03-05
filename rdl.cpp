#include "rdl.h"

float DESCENT_FIXED::get_Value()
{
   float retval = value.parts.hi;
   retval += value.parts.lo / 65536.0;
   return retval;
}

void DESCENT_FIXED::set_Value(float f)
{
}

/********************************
 * This method compartmentalizes
 * the loading of fixed data types
 *******************************/
istream &operator>>(istream &input, DESCENT_FIXED &fixed)
{
   input.read((char *)&fixed.value.raw, sizeof(fixed.value.raw));
   return input;
}

/********************************
 * This method compartmentalizes
 * the displaying of fixed data types
 *******************************/
ostream &operator<<(ostream &output, DESCENT_FIXED &fixed)
{
   output << fixed.get_Value();
   return output;
}

/********************************
 * This method compartmentalizes
 * the loading of fixed data types
 *******************************/
istream &operator>>(istream &input, DESCENT_SHORTFIXED &fixed)
{
   input.read((char *)&fixed.value.raw, sizeof(fixed.value.raw));
   return input;
}

/********************************
 * This method compartmentalizes
 * the loading of vertex data in
 * an rdl
 *******************************/
istream &operator>>(istream &input, DESCENT_VERTEX &vertex)
{
   input >> vertex.x;
   input >> vertex.y;
   input >> vertex.z;
   return input;
}

ostream &operator<<(ostream &output, DESCENT_CUBE &cube) 
{
   output << "Cube.Left = " << cube.left << endl;
   output << "Cube.Top = " << cube.top << endl;
   output << "Cube.Right = " << cube.right << endl;
   output << "Cube.Bottom = " << cube.bottom << endl;
   output << "Cube.Back = " << cube.back << endl;
   output << "Cube.Front = " << cube.front << endl;
   
   return output;
}

/********************************
 * This method compartmentalizes
 * the loading of cube data in
 * an rdl
 *******************************/
istream &operator>>(istream &input, DESCENT_CUBE &cube)
{
   memset(&cube, 0, sizeof(cube));
   unsigned char mask;
   if(!(input >> mask)) {
      input.setstate(ios::failbit);
      cout << "Failed to read cube mask" << endl;
      return input;
   }
   if(mask & 0x01) {
      input.read((char*)&cube.left, sizeof(cube.left));
      if(input.rdstate() != ios::goodbit) {
	 input.setstate(ios::failbit);
	 cout << "Failed to read the cube.left value" << endl;
	 return input;
      }
   }
   if(mask & 0x02) {
      input.read((char*)&cube.top, sizeof(cube.top));
      if(input.rdstate() != ios::goodbit) {
	 input.setstate(ios::failbit);
	 cout << "Failed to read the cube.top value" << endl;
	 return input;
      }
   }
   if(mask & 0x04) {
      input.read((char*)&cube.right, sizeof(cube.right));
      if(input.rdstate() != ios::goodbit) {
	 input.setstate(ios::failbit);
	 cout << "Failed to read the cube.right value" << endl;
	 return input;
      }
   }
   if(mask & 0x08) {
      input.read((char*)&cube.bottom, sizeof(cube.bottom));
      if(input.rdstate() != ios::goodbit) {
	 input.setstate(ios::failbit);
	 cout << "Failed to read the cube.bottom value" << endl;
	 return input;
      }
   }
   if(mask & 0x10) {
      input.read((char*)&cube.back, sizeof(cube.back));
      if(input.rdstate() != ios::goodbit) {
	 input.setstate(ios::failbit);
	 cout << "Failed to read the cube.back value" << endl;
	 return input;
      }
   }
   if(mask & 0x20) {
      input.read((char*)&cube.front, sizeof(cube.front));
      if(input.rdstate() != ios::goodbit) {
	 input.setstate(ios::failbit);
	 cout << "Failed to read the cube.front value" << endl;
	 return input;
      }
   }
   if(mask & 0x40) cube.energy = true;
   for(int i = 0; i < 8; i++) {
      input.read((char *)&cube.verticies[i], sizeof(cube.verticies[i]));
      if(input.rdstate() != ios::goodbit) {
	 input.setstate(ios::failbit);
	 cout << "Failed to read the cube.verticies[" << i << "] value" << endl;
	 return input;
      }
   }
   if(cube.energy) {
      input >> cube.energyCenter.special;
      input >> cube.energyCenter.energyCenterNumber;
      input.read((char *)&cube.energyCenter.value, sizeof(cube.energyCenter.value));
      if(input.rdstate() != ios::goodbit) {
	 input.setstate(ios::failbit);
	 cout << "Failed to read the cube.energy value" << endl;
	 return input;
      }
   }
   input.read((char *)&cube.staticLight.value.raw, sizeof(cube.staticLight.value.raw));
   if(input.rdstate() != ios::goodbit) {
      input.setstate(ios::failbit);
      cout << "Failed to read staticLight" << endl;
      return input;
   }
   unsigned char wallmask;
   if(!(input >> wallmask)) {
      input.setstate(ios::failbit);
      return input;
   }
   if(wallmask & 0x01 && !(input >> cube.walls[0])) {
      input.setstate(ios::failbit);
      cout << "Failed to read Wall[0]" << endl;
      return input;
   }
   if(wallmask & 0x02 && !(input >> cube.walls[1])) {
      input.setstate(ios::failbit);
      cout << "Failed to read Wall[1]" << endl;
      return input;
   }
   if(wallmask & 0x04 && !(input >> cube.walls[2])) {
      input.setstate(ios::failbit);
      cout << "Failed to read Wall[2]" << endl;
      return input;
   }
   if(wallmask & 0x08 && !(input >> cube.walls[3])) {
      input.setstate(ios::failbit);
      cout << "Failed to read Wall[3]" << endl;
      return input;
   }
   if(wallmask & 0x10 && !(input >> cube.walls[4])) {
      input.setstate(ios::failbit);
      cout << "Failed to read Wall[4]" << endl;
      return input;
   }
   if(wallmask & 0x20 && !(input >> cube.walls[5])) {
      input.setstate(ios::failbit);
      cout << "Failed to read Wall[5]" << endl;
      return input;
   }
   if(!(mask & 0x01) || wallmask & 0x01) {
      unsigned short texture;
      input.read((char *)&texture, sizeof(texture));
      if(input.rdstate() != ios::goodbit) {
	 input.setstate(ios::failbit);
	 cout << "Failed to read texture for walls[0]" << endl;
	 return input;
      }
      if(texture & 0x8000) {
	 input.read((char *)&texture, sizeof(texture));
	 if(input.rdstate() != ios::goodbit) {
	    input.setstate(ios::failbit);
	    cout << "Failed to read texture2 for walls[0]" << endl;
	    return input;
	 }
      }
      DESCENT_SHORTFIXED u,v,l;
      input >> u >> v >> l;
      if(input.rdstate() != ios::goodbit) {
	 cout << "Failed to read uvl for walls[0]" << endl;
	 return input;
      }
   }
   if(!(mask & 0x02) || wallmask & 0x02) {
      unsigned short texture;
      input.read((char *)&texture, sizeof(texture));
      if(input.rdstate() != ios::goodbit) {
	 input.setstate(ios::failbit);
	 cout << "Failed to read texture for walls[1]" << endl;
	 return input;
      }
      if(texture & 0x8000) {
	 input.read((char *)&texture, sizeof(texture));
	 if(input.rdstate() != ios::goodbit) {
	    input.setstate(ios::failbit);
	    cout << "Failed to read texture2 for walls[1]" << endl;
	    return input;
	 }
      }
      DESCENT_SHORTFIXED u,v,l;
      if(!(input >> u)) cout << "Failed to read u for walls[1]" << endl;
      if(!(input >> v)) cout << "Failed to read v for walls[1]" << endl;
      if(!(input >> l)) cout << "Failed to read l for walls[1]" << endl;
      if(input.rdstate() != ios::goodbit) {
	 cout << "state: " << (input.rdstate() & ios::eofbit) << endl;
	 cout << "Failed to read uvl for walls[1]" << endl;
	 return input;
      }
   }
   if(!(mask & 0x04) || wallmask & 0x04) {
      unsigned short texture;
      input.read((char *)&texture, sizeof(texture));
      if(input.rdstate() != ios::goodbit) {
	 input.setstate(ios::failbit);
	 cout << "Failed to read texture for walls[2]" << endl;
	 return input;
      }
      if(texture & 0x8000) {
	 input.read((char *)&texture, sizeof(texture));
	 if(input.rdstate() != ios::goodbit) {
	    input.setstate(ios::failbit);
	    cout << "Failed to read texture2 for walls[2]" << endl;
	    return input;
	 }
      }
      DESCENT_SHORTFIXED u,v,l;
      input >> u >> v >> l;
      if(input.rdstate() != ios::goodbit) {
	 cout << "Failed to read uvl for walls[2]" << endl;
	 return input;
      }
   }
   if(!(mask & 0x08) || wallmask & 0x08) {
      unsigned short texture;
      input.read((char *)&texture, sizeof(texture));
      if(input.rdstate() != ios::goodbit) {
	 input.setstate(ios::failbit);
	 cout << "Failed to read texture for walls[3]" << endl;
	 return input;
      }
      if(texture & 0x8000) {
	 input.read((char *)&texture, sizeof(texture));
	 if(input.rdstate() != ios::goodbit) {
	    input.setstate(ios::failbit);
	    cout << "Failed to read texture2 for walls[3]" << endl;
	    return input;
	 }
      }
      DESCENT_SHORTFIXED u,v,l;
      input >> u >> v >> l;
      if(input.rdstate() != ios::goodbit) {
	 cout << "Failed to read uvl for walls[3]" << endl;
	 return input;
      }
   }
   if(!(mask & 0x10) || wallmask & 0x10) {
      unsigned short texture;
      input.read((char *)&texture, sizeof(texture));
      if(input.rdstate() != ios::goodbit) {
	 input.setstate(ios::failbit);
	 cout << "Failed to read texture for walls[4]" << endl;
	 return input;
      }
      if(texture & 0x8000) {
	 input.read((char *)&texture, sizeof(texture));
	 if(input.rdstate() != ios::goodbit) {
	    input.setstate(ios::failbit);
	    cout << "Failed to read texture2 for walls[4]" << endl;
	    return input;
	 }
      }
      DESCENT_SHORTFIXED u,v,l;
      input >> u >> v >> l;
      if(input.rdstate() != ios::goodbit) {
	 cout << "Failed to read uvl for walls[4]" << endl;
	 return input;
      }
   }
   if(!(mask & 0x20) || wallmask & 0x20) {
      unsigned short texture;
      input.read((char *)&texture, sizeof(texture));
      if(input.rdstate() != ios::goodbit) {
	 input.setstate(ios::failbit);
	 cout << "Failed to read texture for walls[4]" << endl;
	 return input;
      }
      if(texture & 0x8000) {
	 input.read((char *)&texture, sizeof(texture));
	 if(input.rdstate() != ios::goodbit) {
	    input.setstate(ios::failbit);
	    cout << "Failed to read texture2 for walls[4]" << endl;
	    return input;
	 }
      }
      DESCENT_SHORTFIXED u,v,l;
      input >> u >> v >> l;
      if(input.rdstate() != ios::goodbit) {
	 cout << "Failed to read uvl for walls[5]" << endl;
	 return input;
      }
   }

   return input;
}

CRdl::CRdl()
{
   Init();
}

CRdl::CRdl(const string &filename)
{
   Init();
   Load(filename);
}

CRdl::CRdl(const CHog &hog, const string &filename)
{
   Init();
   Load(hog, filename);
}

CRdl::CRdl(const string &hog, const string &filename)
{
   Init();
   Load(hog, filename);
}

CRdl::CRdl(const CRdl &source)
{
   Init();
   *this = source;
}

CRdl::~CRdl()
{
   Reset();
}

CRdl &CRdl::operator=(const CRdl &source)
{
   memcpy(&mHeader, &source.mHeader, sizeof(mHeader));
   
   return *this;
}

void CRdl::Reset()
{
   memset(&mHeader, 0, sizeof(mHeader));
   mDescentVerticies.clear();
}

void CRdl::Load(const string &filename)
{
  CFile::Load(filename);
  doLoad();
}

void CRdl::Load(const CHog &hog, const string &filename)
{
  CFile::Load(hog, filename);
  doLoad();
}

void CRdl::Load(const string &hog, const string &filename)
{
  CFile::Load(hog, filename);
  doLoad();
}

void CRdl::doLoad()
{
  fstreamptr file = get_Stream();
   cout << "Loading " << mFilename << "..." << endl;
   
   if((*file).is_open()) {
      (*file) >> *this;
      (*file).close();
   }
   else cout << "Failed to open " << mFilename << endl;
   
   cout << "Vertex Count: " << mDescentVerticies.size() << ", Cube Count: " << mDescentCubes.size() << endl;
}

istream &operator>>(istream &input, RDL_HEADER &header)
{
   input.read((char *)&header, sizeof(header));
   return input;
}

ostream &operator<<(ostream &output, RDL_HEADER &header)
{
   output << header.signature[0] << header.signature[1] << header.signature[2] << header.signature[3] << header.version;
   return output;
}

istream &operator>>(istream &input, CRdl &rdl) 
{
   cout << "File position is now: " << input.tellg() << endl;
   cout << "Hog pos is: " << rdl.mPos << endl;
   cout << "rdl length is: " << rdl.mLength << endl;
   input >> rdl.mHeader;
   cout << "File position is now: " << input.tellg() << endl << "Version is: " << rdl.mHeader.version << endl;
   if(!memcmp(rdl.mHeader.signature, "LVLP", 4) &&
      rdl.mHeader.version == 1) {
      cout << rdl.mHeader << endl;
      input.seekg(static_cast<unsigned short>(rdl.mPos) + rdl.mHeader.mineDataOffset, ios_base::beg);
      cout << "File position is now: " << input.tellg() << endl;
      char version;
      input >> version;
      unsigned short vertexCount = 0;
      unsigned short cubeCount = 0;
      input.read((char *)&vertexCount, sizeof(vertexCount));
      input.read((char *)&cubeCount, sizeof(cubeCount));
      if(!input.eof()) {
	 cout << vertexCount << " verticies, " << cubeCount << " cubes" << endl;
	 cout << "File position is now: " << input.tellg() << endl;
	 cout << "Minedata version: " << static_cast<int>(version) << endl;
	 cout << "sizeof(DESCENT_VERTEX) is " << sizeof(DESCENT_VERTEX) << ", file.tellg() returned " << input.tellg() << endl;
	 for(unsigned int i = 0; i < vertexCount; i++) {
	    global_Log.Write(LogType_Debug, 200, "Added a vertex");
	    DESCENT_VERTEX vertex;
	    if(!(input >> vertex)) break;
	    rdl.mDescentVerticies.push_back(vertex);
	 }
	 cout << "First vertex is: " << rdl.mDescentVerticies[0].x << ", " << rdl.mDescentVerticies[0].y << ", " << rdl.mDescentVerticies[0].z << endl;
	 cout << "Second vertex is: " << rdl.mDescentVerticies[1].x << ", " << rdl.mDescentVerticies[1].y << ", " << rdl.mDescentVerticies[1].z << endl;
	 cout << "Third vertex is: " << rdl.mDescentVerticies[2].x << ", " << rdl.mDescentVerticies[2].y << ", " << rdl.mDescentVerticies[2].z << endl;
	 cout << "Fourth vertex is: " << rdl.mDescentVerticies[3].x << ", " << rdl.mDescentVerticies[3].y << ", " << rdl.mDescentVerticies[3].z << endl;
	 cout << "File position is now: " << input.tellg() << ", state bit is: " << input.rdstate() << endl;
	 cout << "We expect to be at: " << (static_cast<unsigned short>(rdl.mPos) + rdl.mHeader.mineDataOffset + 5 + (12 * vertexCount)) << endl;
	 unsigned short i;
	 for(i = 0; i < cubeCount && input.rdstate() == ios::goodbit; i++) {
	    DESCENT_CUBE cube;
	    if(input >> cube) rdl.mDescentCubes.push_back(cube);
	    else cout << "An error occured during processing" << endl << "Dumping cube data: " << cube << endl;
	 }
	 cout << "File position is now: " << input.tellg() << endl;
	 cout << "Processed " << i << " of " << cubeCount << " Cubes" << endl;
      }
      else cout << "Failed to read Vertix and Cube counts" << endl;
   }
   else cout << "Failed to read a valid signature (" << rdl.mHeader << ")" << endl;
   return input;
}

void CRdl::Init()
{
   memset(&mHeader, 0, sizeof(mHeader));
}
