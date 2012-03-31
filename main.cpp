/****************************************************
 * This work is licensed under the Creative
 * Commons Attribution-NonCommercial-ShareAlike
 * 3.0 Unported License. To view a copy of this
 * license, visit
 * http://creativecommons.org/licenses/by-nc-sa/3.0/
 * or send a letter to Creative Commons, 444
 * Castro Street, Suite 900, Mountain View,
 * California, 94041, USA.
 ***************************************************/
#include "main.h"

#ifndef _WIN32
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
#endif

int main(int argc, char **argv)
{
	int retval = 0;
	CConnectionManager ConnectionManager;
	CHogManager HogManager;

#ifndef _WIN32
	struct sigaction sigIntHandler;
	sigIntHandler.sa_sigaction = NULL;
	sigIntHandler.sa_handler = dbot_signal_handler;
	sigemptyset(&sigIntHandler.sa_mask);
	sigIntHandler.sa_flags = 0;
	sigIntHandler.sa_restorer = NULL;
	sigaction(SIGINT, &sigIntHandler, NULL);
#endif
	

	CConfig::getInstance().Load("config/Main.xml");

	//   vector<string> names = HogManager["chaos.hog"].get_Filenames();
	//   for(vector<string>::iterator i = names.begin(); i != names.end(); i++) {
	//      cout << *i << endl;
	//   }

	//   CRdl rdl1("chaos.hog", "chaos1.rdl");
	//   CRdl rdl2("chaos.hog", "chaos2.rdl");
#ifdef _WIN32
	while(1) CConnectionManager::get_Instance().Pulse();
#else
	while(dbot_signal_stillwantstoplay) CConnectionManager::get_Instance().Pulse();
#endif
	//   CConnection connection;
	//   connection.find_Game();

	cout << "Exiting gracefully" << endl;

	return retval;
}
