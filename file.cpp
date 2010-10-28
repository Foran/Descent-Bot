#include "rdl.h"

CFile::CFile()
{
}

CFile::CFile(const string &filename)
{
}

CFile::CFile(const CHog &hog, const string &filename)
{
}

CFile::CFile(const string &hog, const string &filename)
{
}

CFile::CFile(const CFile &source)
{
}

CFile::~CFile()
{
}

CFile &CFile::operator=(const CFile &source)
{
   return *this;
}

bool CFile::Load(const string &filename)
{
   bool retval = false;
   
   FILE *fp = get_FilePointer(filename);
   if(fp == NULL) {
      CHog descent("descent.hog");
      fp = descent.OpenFile(filename);
   }
   
   if(fp) {
      retval = LoadByFP(fp);
      fp = NULL;
   }
   
   return retval;
}

bool CFile::Load(const CHog &hog, const string &filename)
{
   bool retval = false;
   
   FILE *fp = get_FilePointer(filename);
   if(fp == NULL) {
      fp = const_cast<CHog &>(hog).OpenFile(filename);
      if(fp == NULL) {
	 CHog descent("descent.hog");
	 fp = descent.OpenFile(filename);
      }
   }
   
   if(fp) {
      retval = LoadByFP(fp);
      fp = NULL;
   }
   
   return retval;
}

bool CFile::Load(const string &hog, const string &filename)
{
   bool retval = false;
   
   FILE *fp = get_FilePointer(filename);
   if(fp == NULL) {
      CHog tempHog(hog);
      fp = tempHog.OpenFile(filename);
      if(fp == NULL) {
	 CHog descent("descent.hog");
	 fp = descent.OpenFile(filename);
      }
   }
   
   if(fp) {
      retval = LoadByFP(fp);
      fp = NULL;
   }
   
   return retval;
}

FILE *CFile::get_FilePointer(const string &filename) const
{
   string file = "missions/" + filename;
   FILE *retval = fopen(file.c_str(), "rb");
   if(retval == NULL) {
      retval = fopen(filename.c_str(), "rb");
   }
   
   return retval;
}
