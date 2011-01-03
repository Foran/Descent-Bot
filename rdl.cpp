#include "rdl.h"

CRdl::CRdl()
{
   Init();
}

CRdl::CRdl(const string &filename)
{
   Init();
   if(!Load(filename)) Reset();
}

CRdl::CRdl(const CHog &hog, const string &filename)
{
   Init();
   if(!Load(hog, filename)) Reset();
}

CRdl::CRdl(const string &hog, const string &filename)
{
   Init();
   if(!Load(hog, filename)) Reset();
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

bool CRdl::LoadByFP(FILE *fp)
{
   bool retval = false;
   long basePos = -1;
   
   if(fp != NULL) {
      basePos = ftell(fp) + 1;
      if(1 == fread(&mHeader, sizeof(mHeader), 1, fp) &&
	 !memcmp(mHeader.signature, "LVLP", 4) &&
	 mHeader.version == 1) {
	 printf("%c%c%c%c %li\n", mHeader.signature[0], mHeader.signature[1], mHeader.signature[2], mHeader.signature[3], mHeader.version);
	 fseek(fp, basePos + mHeader.mineDataOffset, SEEK_SET);
	 unsigned short vertexCount;
	 unsigned short cubeCount;
	 if(1 == fread(&vertexCount, sizeof(vertexCount), 1, fp) && 1 == fread(&cubeCount, sizeof(cubeCount), 1, fp)) {
	    printf("%i verticies, %i cubes\n", vertexCount, cubeCount);
	    DESCENT_VERTEX *list = new DESCENT_VERTEX[vertexCount];
	    size_t count;
	    printf("sizeof(DESCENT_VERTEX) is %lu, ftell() returned %li\n", sizeof(DESCENT_VERTEX), ftell(fp));
	    if(vertexCount == (unsigned short)(count = fread(list, sizeof(DESCENT_VERTEX), vertexCount, fp))) {
	       for(unsigned int i = 0; i < vertexCount; i++) {
		  global_Log.Write(Debug, 200, "Added a vertex");
		  mDescentVerticies.push_back(list[i]);
	       }
	    }
	    printf("fread() returned %zi, ftell() returned %li\n", count, ftell(fp));
	    delete list;

	    for(unsigned int i = 0; i < cubeCount; i++) {
	       DESCENT_CUBE cube;
	       memset(&cube, 0, sizeof(cube));
	       unsigned char mask;
	       if(1 == fread(&mask, sizeof(mask), 1, fp)) {
		  if(mask & 0x01) {
		     unsigned short value;
		     if(1 == fread(&value, sizeof(value), 1, fp)) cube.left = value;
		     else break;
		  }
		  if(mask & 0x02) {
		     unsigned short value;
		     if(1 == fread(&value, sizeof(value), 1, fp)) cube.top = value;
		     else break;
		  }
		  if(mask & 0x04) {
		     unsigned short value;
		     if(1 == fread(&value, sizeof(value), 1, fp)) cube.right = value;
		     else break;
		  }
		  if(mask & 0x08) {
		     unsigned short value;
		     if(1 == fread(&value, sizeof(value), 1, fp)) cube.bottom = value;
		     else break;
		  }
		  if(mask & 0x10) {
		     unsigned short value;
		     if(1 == fread(&value, sizeof(value), 1, fp)) cube.back = value;
		     else break;
		  }
		  if(mask & 0x20) {
		     unsigned short value;
		     if(1 == fread(&value, sizeof(value), 1, fp)) cube.front = value;
		     else break;
		  }
		  if(mask & 0x40) cube.energy = true;
		  if(8 != fread(cube.verticies, sizeof(unsigned short), 8, fp)) break;
		  char buffer[4];
		  if(cube.energy && 4 != fread(buffer, sizeof(char), 4, fp)) break;	
		  if(2 != fread(buffer, sizeof(char), 2, fp)) break;
		  unsigned char walls;
		  if(1 != fread(&walls, sizeof(walls), 1, fp)) break;
		  if(walls & 0x01) fread(buffer, 1, 1, fp);
		  if(walls & 0x02) fread(buffer, 1, 1, fp);
		  if(walls & 0x04) fread(buffer, 1, 1, fp);
		  if(walls & 0x08) fread(buffer, 1, 1, fp);
		  if(walls & 0x10) fread(buffer, 1, 1, fp);
		  if(walls & 0x20) fread(buffer, 1, 1, fp);
		  if(!(mask & 0x01) || walls & 0x01) {
		     unsigned short texture;
		     if(1 == fread(&texture, sizeof(texture), 1, fp) && texture & 0x8000) {
			fread(&texture, sizeof(texture), 1, fp);
		     }
		     fread(&texture, sizeof(texture), 1, fp);
		     fread(&texture, sizeof(texture), 1, fp);
		     fread(&texture, sizeof(texture), 1, fp);
		  }
		  
		  mDescentCubes.push_back(cube);
	       }
	    }
	 }
      }
      
      fclose(fp);
   }
   
   printf("Vertex Count: %zi, Cube Count: %zi\n", mDescentVerticies.size(), mDescentCubes.size());
      
   return retval;
}

void CRdl::Init()
{
   memset(&mHeader, 0, sizeof(mHeader));
}
