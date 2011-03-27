#include "main.h"

int main(int argc, char **argv)
{
  int retval = 0;
   
   global_Config.Load("config/Main.xml");
   
   vector<string> names = HogManager["chaos.hog"].get_Filenames();
   for(vector<string>::iterator i = names.begin(); i != names.end(); i++) {
      cout << *i << endl;
   }
   
   CRdl rdl1("chaos.hog", "chaos1.rdl");
   CRdl rdl2("chaos.hog", "chaos2.rdl");
   
//   CConnection connection;
//   connection.find_Game();
   
   return retval;
}
