#include "hog.h"

CHog::CHog()
{
}

CHog::CHog(const string &filename)
{
   Load(filename);
}

CHog::CHog(const CHog &source)
{
  *this = source;
}

CHog::~CHog()
{
  for(vector<CFile *>::iterator i = mFiles.begin(); i != mFiles.end(); i++) {
    delete *i;
  }
}

CHog &CHog::operator=(const CHog &source)
{
  Load(source.mFilename);
  return *this;
}

bool CHog::operator==(const CHog &source)
{
  return mFilename == source.mFilename;
}

CFile CHog::operator[](const string &name) const
{
  CFile file;
  
  for(vector<CFile *>::const_iterator i = mFiles.begin(); i != mFiles.end(); i++) {
    if((**i).mFilename == name) {
      file = **i;
      break;
    }
  }
  
  return file;
}

vector<string> CHog::get_Filenames() const
{
  vector<string> retval;
   
  for(vector<CFile *>::const_iterator i = mFiles.begin(); i != mFiles.end(); i++) {
    retval.push_back((*i)->mFilename);
  }
  
  return retval;
}

bool CHog::Load(const string &filename)
{
  bool retval = true;
  fstreamptr file(("missions/" + filename).c_str(), ios::in | ios::binary);
  char signature[3];
  char file_name[13];
  int file_size;
  
  mFilename = "";
  mFiles.clear();
  
  if((*file).is_open()) {
    mFilename = filename;
    if(!(*file).eof() && (*file).read(signature, 3)) {
      if(signature[0] == 'D' && signature[1] == 'H' && signature[2] == 'F') {
	global_Log.Write(LogType_Debug, 100, "Found a valid signature");
	while(!(*file).eof() && (*file).read(file_name, 13)) {
	  string name = file_name;
	  if(!(*file).eof() && (*file).read((char *)&file_size, 4)) {
	    streampos pos = (*file).tellg();
	    mFiles.push_back(new CFile(*this, name, pos, file_size));
	    global_Log.Write(LogType_Debug, 60, "Found file: " + name + " in hog");
	    (*file).seekg(file_size, ios_base::cur);
	  }
	}
	if(mFiles.size() > 0) retval = true;
      }
    }
    (*file).close();
  }
  
  return retval;
}

fstreamptr CHog::get_Stream() const
{
  fstreamptr file(mFilename.c_str(), ios::in | ios::binary);
  
  return file;
}

fstreamptr CHog::get_Stream(const string &name) const
{
  fstreamptr file = get_Stream();
  
  if((*file).is_open()) (*file).seekg((*this)[name].mPos, ios_base::beg);
  
  return file;
}
