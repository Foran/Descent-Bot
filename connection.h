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
