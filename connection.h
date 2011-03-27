#ifndef __CONNECTION_H__
#define __CONNECTION_H__

#include <iostream>

using namespace std;

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <unistd.h>
#include <string.h>
#include <arpa/inet.h>

#include "packets.h"

class CConnection 
{
 public:
   void find_Game();
   void ProcessInboundPackets();
 protected:
 private:
     int mSocket;
   
   CConnection();
   CConnection(const CConnection &source);
   ~CConnection();
   CConnection &operator=(const CConnection &source);
   
   friend class CConnectionManager;
};

#endif
