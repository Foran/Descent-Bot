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
   
   if(fp != NULL) {
      fclose(fp);
   }
      
   return retval;
}

void CRdl::Init()
{
   memset(&mHeader, 0, sizeof(mHeader));
}
