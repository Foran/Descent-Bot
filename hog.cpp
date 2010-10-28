#include "hog.h"

CHog::CHog()
{
}

CHog::CHog(const string &filename)
{
   set_Filename(filename);
}

CHog::CHog(const CHog &source)
{
}

CHog::~CHog()
{
}

CHog &CHog::operator=(const CHog &source)
{
	return *this;
}

void CHog::set_Filename(const string &filename)
{
   mFilename = filename;
}

vector<string> CHog::get_Filenames() const
{
   vector<string> retval;
   FILE *fp = get_FilePointer();
   char signature[3];
   char file_name[13];
   int file_size;
   
   if(fp) {
      if(3 == fread(signature, sizeof(char), 3, fp)) {
	 if(signature[0] == 'D' && signature[1] == 'H' && signature[2] == 'F') {
	    global_Log.Write(Debug, 100, "Found a valid signature");
	    while(13 == fread(file_name, sizeof(char), 13, fp)) {
	       string name = file_name;
	       retval.push_back(name);
	       global_Log.Write(Debug, 60, "Found file: " + name + " in hog and added to list");
	       fread(&file_size, sizeof(int), 1, fp);
	       fseek(fp, file_size, SEEK_CUR);
	    }
	 }
      }
      fclose(fp);
      fp = NULL;
   }
   
   return retval;
}

FILE *CHog::OpenFile(const string &filename)
{
   FILE *retval = NULL;
   FILE *fp = get_FilePointer();
   char signature[3];
   char file_name[13];
   int file_size;
   
   if(fp) {
      if(3 == fread(signature, sizeof(char), 3, fp)) {
	 if(signature[0] == 'D' && signature[1] == 'H' && signature[2] == 'F') {
	    global_Log.Write(Debug, 100, "Found a valid signature");
	    while(13 == fread(file_name, sizeof(char), 13, fp)) {
	       string name = file_name;
	       fread(&file_size, sizeof(int), 1, fp);
	       global_Log.Write(Debug, 60, "Found file: " + name + " in hog");
	       if(filename == name) {
		  global_Log.Write(Debug, 60, "Found file in hog that we were looking for");
		  retval = fp;
		  break;
	       }
	       fseek(fp, file_size, SEEK_CUR);
	    }
	 }
      }
      if(retval == NULL) {
	 fclose(fp);
	 fp = NULL;
      }
   }
   
   return retval;
}

FILE *CHog::get_FilePointer() const
{
   string filename = "missions/" + mFilename;
   FILE *retval = fopen(filename.c_str(), "rb");
   if(retval == NULL) {
      retval = fopen(mFilename.c_str(), "rb");
      global_Log.Write(Debug, 50, "Opening " + mFilename);
   }
   else global_Log.Write(Debug, 50, "Opening " + filename);
   
   return retval;
}
