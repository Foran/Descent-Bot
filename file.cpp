#include "file.h"

CFile::CFile()
{
  mHog = NULL;
}

CFile::CFile(const string &filename)
{
  Load(filename);
}

CFile::CFile(const CHog &hog, const string &filename)
{
  Load(hog, filename);
}

CFile::CFile(const string &hog, const string &filename)
{
  mHog = &HogManager::get_Hog(hog);
}

CFile::CFile(const CHog &hog, const string &filename, streampos offset, int length)
{
  mHog = const_cast<CHog *>(&hog);
  mFilename = filename;
  mPos = offset;
  mLength = length;
}

CFile::CFile(const CFile &source)
{
  *this = source;
}

CFile::~CFile()
{
  mHog = NULL;
}

CFile &CFile::operator=(const CFile &source)
{
  mHog = source.mHog;
  mFilename = source.mFilename;
  mLength = source.mLength;
  mPos = mPos;
  
  return *this;
}

void CFile::Load(const string &filename)
{
  mHog = NULL;
  mFilename = filename;
  mLength = 0;
  mPos = 0;
}

void CFile::Load(const CHog &hog, const string &filename)
{
  mHog = const_cast<CHog *>(&hog);
  mFilename = filename;
  mLength = (*mHog)[filename].mLength;
  mPos = (*mHog)[filename].mPos;
}

void CFile::Load(const string &hog, const string &filename)
{
  mHog = &HogManager::get_Hog(hog);
  mFilename = filename;
  mLength = (*mHog)[filename].mLength;
  mPos = (*mHog)[filename].mPos;
}

fstreamptr CFile::get_Stream()
{
  fstreamptr file;
  
  if(mFilename.length() > 0) {
    if(mHog == NULL) {
      (*file).open(mFilename.c_str(), ios::in | ios::binary);
      mPos = (*file).tellg();
    }
    else {
      file = mHog->get_Stream(mFilename);
    }
  }
  
  return file;
}

bool CFile::eof(fstream &file)
{
  bool retval = true;
  
  if(mHog == NULL) {
    retval = file.eof();
  }
  else {
    retval = (file.tellg() - mPos) >= mLength;
  }
  
  return retval;
}
