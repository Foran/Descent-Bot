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
	mHog = &CHogManager::get_Instance()[hog];
}

CFile::CFile(const CHog &hog, const string &filename, streampos offset, int length)
{
  mHog = const_cast<CHog *>(&hog);
  mFilename = filename;
  mPos = offset;
  mLength = length;
   cout << "Loading file " << hog.mFilename << "." << mFilename << " at offset " << mPos << " for " << mLength << " bytes" << endl;
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
  mPos = source.mPos;
  
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
	mHog = &CHogManager::get_Instance()[hog];
  mFilename = filename;
  mLength = (*mHog)[filename].mLength;
  mPos = (*mHog)[filename].mPos;
}

fstreamptr CFile::get_Stream()
{
  fstreamptr file;
  
  if(mFilename.length() > 0) {
    if(mHog == NULL) {
      global_Log.Write(LogType_Debug, 200, "Opening " + mFilename + " in direct mode");
      (*file).open(("missions/" + mFilename).c_str(), ios::in | ios::binary);
      mPos = (*file).tellg();
    }
    else {
      global_Log.Write(LogType_Debug, 200, "Opening " + mFilename + " from " + mHog->mFilename);
      file = mHog->get_Stream(mFilename);
       cout << ((*file).is_open() ? "True" : "False") << endl;
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
