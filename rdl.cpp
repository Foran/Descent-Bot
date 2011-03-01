#include "rdl.h"

istream &operator>>(istream &input, DESCENT_CUBE &cube)
{
   memset(&cube, 0, sizeof(cube));
   unsigned char mask;
   input.read((char *)&mask, 1);
   if(!input.eof()) {
      if(mask & 0x01) {
	 unsigned short value;
	 input.read((char *)&value, sizeof(value));
	 if(!input.eof()) cube.left = value;
	 else return input; //**FIXME: this should set the fail bit **//
      }
      if(mask & 0x02) {
	 unsigned short value;
	 input.read((char *)&value, sizeof(value));
	 if(!input.eof()) cube.top = value;
	 else return input;
      }
      if(mask & 0x04) {
	 unsigned short value;
	 input.read((char *)&value, sizeof(value));
	 if(!input.eof()) cube.right = value;
	 else return input;
      }
      if(mask & 0x08) {
	 unsigned short value;
	 input.read((char *)&value, sizeof(value));
	 if(!input.eof()) cube.bottom = value;
	 else return input;
      }
      if(mask & 0x10) {
	 unsigned short value;
	 input.read((char *)&value, sizeof(value));
	 if(!input.eof()) cube.back = value;
	 else return input;
      }
      if(mask & 0x20) {
	 unsigned short value;
	 input.read((char *)&value, sizeof(value));
	 if(!input.eof()) cube.front = value;
	 else return input;
      }
      if(mask & 0x40) cube.energy = true;
      input.read((char *)cube.verticies, sizeof(DESCENT_VERTEX) * 8);
      if(input.eof()) return input;
      char buffer[4];
      if(cube.energy) {
	 input.read(buffer, 4);
	 if(input.eof()) return input;
      }
      input.read(buffer, 2);
      if(input.eof()) return input;
      unsigned char walls;
      input.read((char *)&walls, 1);
      if(input.eof()) return input;
      if(walls & 0x01) input.read(buffer, 1);
      if(walls & 0x02) input.read(buffer, 1);
      if(walls & 0x04) input.read(buffer, 1);
      if(walls & 0x08) input.read(buffer, 1);
      if(walls & 0x10) input.read(buffer, 1);
      if(walls & 0x20) input.read(buffer, 1);
      if(!(mask & 0x01) || walls & 0x01) {
	 unsigned short texture;
	 input.read((char *)&texture, sizeof(texture));
	 if(!input.eof() && texture & 0x8000) {
	    input.read((char *)&texture, sizeof(texture));
	 }
	 input.read((char *)&texture, sizeof(texture));
	 input.read((char *)&texture, sizeof(texture));
	 input.read((char *)&texture, sizeof(texture));
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
      (*file).read((char *)&mHeader, sizeof(mHeader));
      cout << "File position is now: " << (*file).tellg() << endl << "Version is: " << mHeader.version << endl;
      if(!memcmp(mHeader.signature, "LVLP", 4) &&
	 mHeader.version == 1) {
	 cout << mHeader.signature[0] << mHeader.signature[1] << mHeader.signature[2] << mHeader.signature[3] << mHeader.version << endl;
	 (*file).seekg(static_cast<unsigned short>(mPos) + mHeader.mineDataOffset, ios_base::beg);
	 unsigned short vertexCount = 0;
	 unsigned short cubeCount = 0;
	 (*file).read((char *)&vertexCount, sizeof(vertexCount));
	 (*file).read((char *)&cubeCount, sizeof(cubeCount));
	 if(!(*file).eof()) {
	    cout << vertexCount << " verticies, " << cubeCount << " cubes" << endl;
	    DESCENT_VERTEX *list = new DESCENT_VERTEX[vertexCount];
	    size_t count = vertexCount;
	    cout << "sizeof(DESCENT_VERTEX) is " << sizeof(DESCENT_VERTEX) << ", file.tellg() returned " << (*file).tellg() << endl;
	    if((*file).read((char *)list, sizeof(vertexCount) * vertexCount)) {
	       for(unsigned int i = 0; i < vertexCount; i++) {
		  global_Log.Write(LogType_Debug, 200, "Added a vertex");
		  mDescentVerticies.push_back(list[i]);
	       }
	    }
	    cout << "fread() returned " << count << ", file.tellg() returned " << (*file).tellg() << endl;
	    delete list;
	    
	    unsigned short i;
	    for(i = 0; i < cubeCount; i++) {
	       DESCENT_CUBE cube;
	       (*file) >> cube;
	       if(!(*file).eof()) mDescentCubes.push_back(cube);
	    }
	    cout << "Processed " << i << " of " << cubeCount << " Cubes" << endl;
	 }
	 else cout << "Failed to read Vertix and Cube counts" << endl;
      }
      else cout << "Failed to read a valid signature (" << mHeader.signature[0] << mHeader.signature[1] << mHeader.signature[2] << mHeader.signature[3] << ")" << endl;
      
      (*file).close();
   }
   else cout << "Failed to open " << mFilename << endl;
   
   cout << "Vertex Count: " << mDescentVerticies.size() << ", Cube Count: " << mDescentCubes.size() << endl;
}

void CRdl::Init()
{
   memset(&mHeader, 0, sizeof(mHeader));
}
