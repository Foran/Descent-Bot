#include "hog.h"

CHog::CHog()
{
}

CHog::CHog(const string &filename)
{
	mFilename = filename;
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

vector<string> CHog::get_Filenames() const
{
	vector<string> retval;
	string filename = "missions/" + mFilename;
	FILE *fp = fopen(filename.c_str(), "rb");
	char signature[3];
	char file_name[13];
	int file_size;

	if(fp) {
		if(3 == fread(signature, sizeof(char), 3, fp)) {
			if(signature[0] == 'D' && signature[1] == 'H' && signature[2]) {
				while(!feof(fp)) {
					if(13 != fread(file_name, sizeof(char), 13, fp)) break; //Exit if feof() fails to return end of file
					string name = file_name;
					retval.push_back(name);
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
