#include "main.h"

/**************************
 * This is temporary implementation
 * This will go into a seperate class
 *************************/
#include <signal.h>

bool dbot_signal_stillwantstoplay = true;

void dbot_signal_handler(int s)
{
   dbot_signal_stillwantstoplay = false;
}

int main(int argc, char **argv)
{
  int retval = 0;
   CConnectionManager ConnectionManager;
   CHogManager HogManager;
   
   struct sigaction sigIntHandler;
   sigIntHandler.sa_sigaction = NULL;
   sigIntHandler.sa_handler = dbot_signal_handler;
   sigemptyset(&sigIntHandler.sa_mask);
   sigIntHandler.sa_flags = 0;
   sigIntHandler.sa_restorer = NULL;
   sigaction(SIGINT, &sigIntHandler, NULL);
   
//   global_Config.Load("config/Main.xml");
   
//   vector<string> names = HogManager["chaos.hog"].get_Filenames();
//   for(vector<string>::iterator i = names.begin(); i != names.end(); i++) {
//      cout << *i << endl;
//   }
   
//   CRdl rdl1("chaos.hog", "chaos1.rdl");
//   CRdl rdl2("chaos.hog", "chaos2.rdl");

   while(dbot_signal_stillwantstoplay) CConnectionManager::get_Instance().Pulse();
//   CConnection connection;
//   connection.find_Game();

   cout << "Exiting gracefully" << endl;
   
   return retval;
}
