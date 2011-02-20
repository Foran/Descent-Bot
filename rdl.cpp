#include "rdl.h"

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
   
   if((*file).is_open()) {
      if((*file).read((char *)&mHeader, 4) &&
	 !memcmp(mHeader.signature, "LVLP", 4) &&
	 mHeader.version == 1) {
	 printf("%c%c%c%c %li\n", mHeader.signature[0], mHeader.signature[1], mHeader.signature[2], mHeader.signature[3], mHeader.version);
	 (*file).seekg(static_cast<unsigned short>(mPos) + mHeader.mineDataOffset, ios_base::beg);
	 unsigned short vertexCount;
	 unsigned short cubeCount;
	 if((*file).read((char *)&vertexCount, sizeof(vertexCount)) && (*file).read((char *)&cubeCount, sizeof(cubeCount))) {
	    printf("%i verticies, %i cubes\n", vertexCount, cubeCount);
	    DESCENT_VERTEX *list = new DESCENT_VERTEX[vertexCount];
	    size_t count = vertexCount;
	    printf("sizeof(DESCENT_VERTEX) is %u, ftell() returned %i\n", sizeof(DESCENT_VERTEX), static_cast<int>((*file).tellg()));
	    if((*file).read((char *)list, sizeof(vertexCount) * vertexCount)) {
	       for(unsigned int i = 0; i < vertexCount; i++) {
		  global_Log.Write(Debug, 200, "Added a vertex");
		  mDescentVerticies.push_back(list[i]);
	       }
	    }
	    printf("fread() returned %i, ftell() returned %i\n", static_cast<int>(count), static_cast<int>((*file).tellg()));
	    delete list;

	    for(unsigned int i = 0; i < cubeCount; i++) {
	       DESCENT_CUBE cube;
	       memset(&cube, 0, sizeof(cube));
	       unsigned char mask;
	       if((*file).read((char *)&mask, 1)) {
		  if(mask & 0x01) {
		     unsigned short value;
		     if((*file).read((char *)&value, sizeof(value))) cube.left = value;
		     else break;
		  }
		  if(mask & 0x02) {
		     unsigned short value;
		     if((*file).read((char *)&value, sizeof(value))) cube.top = value;
		     else break;
		  }
		  if(mask & 0x04) {
		     unsigned short value;
		     if((*file).read((char *)&value, sizeof(value))) cube.right = value;
		     else break;
		  }
		  if(mask & 0x08) {
		     unsigned short value;
		     if((*file).read((char *)&value, sizeof(value))) cube.bottom = value;
		     else break;
		  }
		  if(mask & 0x10) {
		     unsigned short value;
		     if((*file).read((char *)&value, sizeof(value))) cube.back = value;
		     else break;
		  }
		  if(mask & 0x20) {
		     unsigned short value;
		     if((*file).read((char *)&value, sizeof(value))) cube.front = value;
		     else break;
		  }
		  if(mask & 0x40) cube.energy = true;
		  if((*file).read((char *)cube.verticies, sizeof(DESCENT_VERTEX) * 8)) break;
		  char buffer[4];
		  if(cube.energy && (*file).read(buffer, 4)) break;	
		  if((*file).read(buffer, 2)) break;
		  unsigned char walls;
		  if((*file).read((char *)&walls, 1)) break;
		  if(walls & 0x01) (*file).read(buffer, 1);
		  if(walls & 0x02) (*file).read(buffer, 1);
		  if(walls & 0x04) (*file).read(buffer, 1);
		  if(walls & 0x08) (*file).read(buffer, 1);
		  if(walls & 0x10) (*file).read(buffer, 1);
		  if(walls & 0x20) (*file).read(buffer, 1);
		  if(!(mask & 0x01) || walls & 0x01) {
		     unsigned short texture;
		     if((*file).read((char *)&texture, sizeof(texture)) && texture & 0x8000) {
			(*file).read((char *)&texture, sizeof(texture));
		     }
		      (*file).read((char *)&texture, sizeof(texture));
		      (*file).read((char *)&texture, sizeof(texture));
		      (*file).read((char *)&texture, sizeof(texture));
		  }
		  
		  mDescentCubes.push_back(cube);
	       }
	    }
	 }
      }
      
      (*file).close();
   }
   
   printf("Vertex Count: %i, Cube Count: %i\n", static_cast<int>(mDescentVerticies.size()), static_cast<int>(mDescentCubes.size()));
}

void CRdl::Init()
{
   memset(&mHeader, 0, sizeof(mHeader));
}
