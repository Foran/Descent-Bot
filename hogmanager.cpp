#include "hogmanager.h"

vector<CHog *> CHogManager::mHogs;
unsigned int CHogManager::mReferences = 0;

CHogManager HogManager;

CHogManager::CHogManager()
{
  mReferences++;
}

CHogManager::~CHogManager()
{
  if(--mReferences == 0) {
    for(vector<CHog *>::iterator i = mHogs.begin(); i != mHogs.end(); i++) {
      delete *i;
    }
  }
}

CHog &CHogManager::operator[](const string &filename)
{
  CHog *hog = NULL;
  
  for(vector<CHog *>::iterator i = mHogs.begin(); i != mHogs.end(); i++) {
    if((**i).mFilename == filename) {
      hog = *i;
      break;
    }
  }
  
  if(hog == NULL) {
    hog = new CHog(filename);
    mHogs.push_back(hog);
  }
  
  return *hog;
}
