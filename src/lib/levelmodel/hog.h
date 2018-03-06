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
#ifndef __HOG_H__
#define __HOG_H__

#include <string>
#include <vector>

using namespace std;

class CFile;

#include "src/lib/log/log.h"
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
