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
#ifndef __CONNECTIONMANAGER_H__
#define __CONNECTIONMANAGER_H__

#include <map>

using namespace std;

#include <string.h>
#include <time.h>

#include "network.h"
#include "packets.h"
#include "connection.h"
#include "src/lib/log/log.h"

/// Singleton that manages all connection objects
/********************************************//**
 * Manages all instances of CConnection
 * @see CConnection
 ***********************************************/
class CConnectionManager
{
 public:
   CConnectionManager();
   CConnectionManager(const CConnectionManager &source);
   ~CConnectionManager();
   
   CConnectionManager &operator=(const CConnectionManager &source);
   
   static CConnectionManager get_Instance();
   void Pulse();
 protected:
 private:
   static int mReferences;
   static Descent_Socket mSocket;
   static map<Descent_Socket, CConnection *> mConnections;
   static map<struct sockaddr_in, string> mGames;
   static map<string, time_t> mGameAges;
};

#endif
