#ifndef __CONNECTIONMANAGER_H__
#define __CONNECTIONMANAGER_H__

#include <map>

using namespace std;

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <unistd.h>
#include <string.h>
#include <arpa/inet.h>
#include <time.h>
#include <sys/time.h>

#include "packets.h"

#include "connection.h"

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
   static int mSocket;
   static map<int, CConnection *> mConnections;
   static map<struct sockaddr_in, string> mGames;
   static map<string, time_t> mGameAges;
};

#endif
