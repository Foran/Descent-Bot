#ifndef __HOG_H__
#define __HOG_H__

#include <string>
#include <vector>

using namespace std;

class CFile;

#include "log.h"
#include "file.h"
#include "fstreamptr.h"

class CHogManager;

#include "hogmanager.h"

class CHog
{
 public:
   CHog();
   CHog(const string &filename);
   CHog(const CHog &source);
   
   ~CHog();
   
   CHog &operator=(const CHog &source);
   bool operator==(const CHog &source);
   
   CFile operator[](const string &name) const;
   
   bool Load(const string &filename);
   
   vector<string> get_Filenames() const;
 protected:
 private:
   string mFilename;
   vector<CFile *> mFiles;
   fstreamptr get_Stream() const;
   fstreamptr get_Stream(const string &name) const;
   
   friend class CFile;
   friend class CHogManager;
};

#endif
