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
#include <string>

#include "lib/config/config.h"
#include "lib/context/application_context.h"
#include "lib/levelmodel/hogmanager.h"
#include "lib/levelmodel/rdl.h"
#include "lib/log/log.h"
#include "lib/network/connectionmanager.h"

using ::DESCENT_BOT::LIB::CONFIG::CConfig;
using ::DESCENT_BOT::LIB::CONTEXT::CApplicationContext;
using ::DESCENT_BOT::LIB::LEVELMODEL::CHogManager;
using ::DESCENT_BOT::LIB::LEVELMODEL::CRdl;
using ::DESCENT_BOT::LIB::LOG::CLog;
using ::DESCENT_BOT::LIB::LOG::LogType;
using ::DESCENT_BOT::LIB::NETWORK::CConnectionManager;
using ::std::cout;
using ::std::endl;
using ::std::string;

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
  CLog log(&CApplicationContext::getInstance().getContext());
  CApplicationContext::getInstance().registerComponent(&log);

  CConfig config(&CApplicationContext::getInstance().getContext());
  CApplicationContext::getInstance().registerComponent(&config);

  CConnectionManager connectionManager(
    &CApplicationContext::getInstance().getContext());
  CHogManager hogManager(&CApplicationContext::getInstance().getContext());

  CApplicationContext::getInstance().registerComponent(&connectionManager);
  CApplicationContext::getInstance().registerComponent(&hogManager);

#ifndef _WIN32
  struct sigaction sigIntHandler;
  sigIntHandler.sa_sigaction = nullptr;
  sigIntHandler.sa_handler = dbot_signal_handler;
  sigemptyset(&sigIntHandler.sa_mask);
  sigIntHandler.sa_flags = 0;
  sigIntHandler.sa_restorer = nullptr;
  sigaction(SIGINT, &sigIntHandler, nullptr);
#endif

  CConfig::fromContext(
    &CApplicationContext::getInstance())->Load("config/Main.conf");

  LOG_GLOBAL(LogType::LogType_Debug, 100) << "Initialized";

  for (string name : (*CHogManager::fromContext(
    &CApplicationContext::getInstance()))["chaos.hog"].get_Filenames()) {
    LOG_GLOBAL(LogType::LogType_Debug, 100) << name;
  }

  CRdl rdl1(&CApplicationContext::getInstance(), "chaos.hog", "chaos1.rdl");
  CRdl rdl2(&CApplicationContext::getInstance(), "chaos.hog", "chaos2.rdl");
#ifdef _WIN32
  while (1) dynamic_cast<CConnectionManager*>(
    CApplicationContext::getInstance().getComponent("ConnectionManager"))
      ->Pulse();
#else
  while (dbot_signal_stillwantstoplay) {
    dynamic_cast<CConnectionManager*>(
      CApplicationContext::getInstance().getComponent("ConnectionManager"))
        ->Pulse();
  }
#endif

  LOG_GLOBAL(LogType::LogType_Debug, 100) << "Exiting gracefully";

  return retval;
}
