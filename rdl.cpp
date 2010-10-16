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
}

bool CRdl::LoadByFP(FILE *fp)
{
   bool retval = false;
   long basePos = -1;
   
   if(fp != NULL) {
      basePos = ftell(fp);
      if(1 == fread(&mHeader, sizeof(mHeader), 1, fp) &&
	 !memcmp(mHeader.signature, "LVLP", 4) &&
	 mHeader.version == 1) {
	 printf("%c%c%c%c %li\n", mHeader.signature[0], mHeader.signature[1], mHeader.signature[2], mHeader.signature[3], mHeader.version);
      }
      
      fclose(fp);
   }
      
   return retval;
}

void CRdl::Init()
{
   memset(&mHeader, 0, sizeof(mHeader));
}
