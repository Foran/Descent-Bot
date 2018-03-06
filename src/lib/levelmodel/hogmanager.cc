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
#include "hogmanager.h"

vector<CHog *> CHogManager::mHogs;
unsigned int CHogManager::mReferences = 0;

CHogManager::CHogManager()
{
  mReferences++;
}

CHogManager::~CHogManager()
{
   if(--mReferences == 0) {
      for(auto& hog : mHogs) {
      delete hog;
    }
  }
}

CHog &CHogManager::operator[](const string &filename)
{
   CHog *retval = NULL;
   
   for(auto& hog : mHogs) {
      if(hog->mFilename == filename) {
	 retval = hog;
	 break;
      }
   }
   
   if(retval == NULL) {
      retval = new CHog(filename);
      mHogs.push_back(retval);
   }
   
   return *retval;
}

CHogManager CHogManager::get_Instance()
{
   return CHogManager();
}
