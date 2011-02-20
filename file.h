#ifndef __FILE_H__
#define __FILE_H__

#include <string>
#include <vector>
#include <iostream>

using namespace std;

class CHog;

#include "hogmanager.h"
#include "hog.h"
#include "fstreamptr.h"

class CFile {
 public:
   CFile();
   CFile(const string &filename);
   CFile(const CHog &hog, const string &filename);
   CFile(const string &hog, const string &filename);
   CFile(const CFile &source);
   ~CFile();
   
   CFile &operator=(const CFile &source);
   
   void Load(const string &filename);
   void Load(const CHog &hog, const string &filename);
   void Load(const string &hog, const string &filename);
 protected:
   fstreamptr get_Stream();
   bool eof(fstream &file);
   string mFilename;
   streampos mPos;
   int mLength;  
 private:
   CHog *mHog;
   CFile(const CHog &hog, const string &filename, streampos offset, int length);
   
   friend class CHog;
};

#endif

