#include "main.h"

int main(int argc, char **argv)
{
	int retval = 0;

	CHog hog("chaos.hog");
	vector<string> names = hog.get_Filenames();
	for(vector<string>::iterator i = names.begin(); i != names.end(); i++) {
		printf("%s\n", (*i).c_str());
	}
   
   CRdl rdl(hog, "chaos1.rdl");
   
	return retval;
}
