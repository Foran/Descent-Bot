#include "main.h"

int main(int argc, char **argv)
{
   int retval = 0;
   
   for(vector<string>::const_iterator i = TestManager.get_TestClasses().begin(); i != TestManager.get_TestClasses().end(); i++) {
      cout << "Loading Test Class: " + *i << endl;
   }   
   
   return retval;
}
