/****************************************************
 * Copyright 2018 Ben M. Ward
 *
 * This work is licensed under the Creative
 * Commons Attribution-NonCommercial-ShareAlike
 * 3.0 Unported License. To view a copy of this
 * license, visit
 * http://creativecommons.org/licenses/by-nc-sa/3.0/
 * or send a letter to Creative Commons, 444
 * Castro Street, Suite 900, Mountain View,
 * California, 94041, USA.
 ***************************************************/
#include <iostream>

#include "src/lib/config/config.h"
#include "src/lib/context/application_context.h"
#include "src/lib/levelmodel/hogmanager.h"
#include "src/lib/levelmodel/rdl.h"
#include "src/lib/log/log.h"
#include "src/lib/network/connectionmanager.h"

using ::DESCENT_BOT::SRC::LIB::CONFIG::CConfig;
using ::DESCENT_BOT::SRC::LIB::CONTEXT::CApplicationContext;
using ::DESCENT_BOT::SRC::LIB::LEVELMODEL::CHogManager;
// using ::DESCENT_BOT::SRC::LIB::LEVELMODEL::CRdl;
using ::DESCENT_BOT::SRC::LIB::LOG::CLog;
using ::DESCENT_BOT::SRC::LIB::NETWORK::CConnectionManager;
using ::std::cout;
using ::std::endl;

#ifndef _WIN32
/**************************
* This is temporary implementation
* This will go into a seperate class
*************************/
#include <signal.h>

bool dbot_signal_stillwantstoplay = true;

void dbot_signal_handler(int s) {
  dbot_signal_stillwantstoplay = false;
}
#endif

int main(int argc, char **argv) {
  int retval = 0;
  CApplicationContext applicationContext;

  CLog log(&applicationContext.getContext());
  applicationContext.registerComponent(&log);

  CConfig config(&applicationContext.getContext());
  applicationContext.registerComponent(&config);

  CConnectionManager connectionManager(&applicationContext.getContext());
  CHogManager hogManager(&applicationContext.getContext());

  applicationContext.registerComponent(&connectionManager);
  applicationContext.registerComponent(&hogManager);

#ifndef _WIN32
  struct sigaction sigIntHandler;
  sigIntHandler.sa_sigaction = nullptr;
  sigIntHandler.sa_handler = dbot_signal_handler;
  sigemptyset(&sigIntHandler.sa_mask);
  sigIntHandler.sa_flags = 0;
  sigIntHandler.sa_restorer = nullptr;
  sigaction(SIGINT, &sigIntHandler, nullptr);
#endif

  dynamic_cast<CConfig*>(
    applicationContext.getComponent("Config"))->Load("config/Main.conf");

  CLog::fromContext(&applicationContext)->Write(
    ::DESCENT_BOT::SRC::LIB::LOG::LogType::LogType_Debug, 100, "Initialized");

  // vector<string> names = HogManager["chaos.hog"].get_Filenames();
  // for(vector<string>::iterator i = names.begin(); i != names.end(); i++) {
  //   cout << *i << endl;
  // }

  // CRdl rdl1(applicationContext, "chaos.hog", "chaos1.rdl");
  // CRdl rdl2("chaos.hog", "chaos2.rdl");
#ifdef _WIN32
  while (1) dynamic_cast<CConnectionManager*>(
    applicationContext.getComponent("ConnectionManager"))->Pulse();
#else
  while (dbot_signal_stillwantstoplay) {
    dynamic_cast<CConnectionManager*>(
      applicationContext.getComponent("ConnectionManager"))->Pulse();
  }
#endif
  // CConnection connection;
  // connection.find_Game();

  cout << "Exiting gracefully" << endl;

  return retval;
}
