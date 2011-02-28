#include "main.h"

int main(int argc, char **argv)
{
  int retval = 0;
   
   global_Config.Load("config/Main.xml");
   
   vector<string> names = HogManager["chaos.hog"].get_Filenames();
   for(vector<string>::iterator i = names.begin(); i != names.end(); i++) {
      cout << *i << endl;
   }
   
   CRdl rdl("chaos.hog", "chaos1.rdl");
   
   return retval;
}
