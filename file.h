#ifndef __FILE_H__
#define __FILE_H__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <string>
#include <vector>

using namespace std;

#include "hog.h"

class CFile {
 public:
   CFile();
   CFile(const string &filename);
   CFile(const CHog &hog, const string &filename);
   CFile(const string &hog, const string &filename);
   CFile(const CFile &source);
   ~CFile();
   
   CFile &operator=(const CFile &source);
   
   bool Load(const string &filename);
   bool Load(const CHog &hog, const string &filename);
   bool Load(const string &hog, const string &filename);
 protected:
   virtual bool LoadByFP(FILE *fp) = 0;
   FILE *get_FilePointer(const string &filename) const;
 private:
};

#endif

