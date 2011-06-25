/****************************************************
 * This work is licensed under the Creative
 * Commons Attribution-NonCommercial-ShareAlike
 * 3.0 Unported License. To view a copy of this
 * license, visit
 * http://creativecommons.org/licenses/by-nc-sa/3.0/
 * or send a letter to Creative Commons, 444
 * Castro Street, Suite 900, Mountain View,
 * California, 94041, USA.
 ***************************************************/
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

/// Generic file (plain or part of a HOG)
class CFile {
 public:
   /// Default constructor
   CFile();
   /// Standalone file or file in missions/descent.hog
   CFile(const string &filename);
   /// File in hog or missions/descent.hog
   CFile(const CHog &hog, const string &filename);
   CFile(const string &hog, const string &filename);
   CFile(const CFile &source);
   virtual ~CFile();
   
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

