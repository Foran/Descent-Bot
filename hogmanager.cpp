#include "hogmanager.h"

vector<CHog *> HogManager::mHogs;

void HogManager::Init()
{
  atexit(Cleanup);
}

void HogManager::Cleanup()
{
  for(vector<CHog *>::iterator i = mHogs.begin(); i != mHogs.end(); i++) {
    delete *i;
  }
}

CHog &HogManager::get_Hog(const string &filename)
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
