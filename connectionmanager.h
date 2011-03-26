#ifndef __CONNECTIONMANAGER_H__
#define __CONNECTIONMANAGER_H__

#include <vector>

using namespace std;

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <unistd.h>
#include <string.h>
#include <arpa/inet.h>

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
 protected:
 private:
   static int mReferences;
   static int mSocket;
   static vector<CConnection *> mConnections;
};

#endif
