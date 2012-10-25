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
#include "connectionmanager.h"

int CConnectionManager::mReferences = 0;
Descent_Socket CConnectionManager::mSocket = -1;
map<Descent_Socket, CConnection *> CConnectionManager::mConnections;
map<struct sockaddr_in, string> CConnectionManager::mGames;
map<string, time_t> CConnectionManager::mGameAges;

/***********************************************//**
 * Default constructor
 **************************************************/
CConnectionManager::CConnectionManager()
{
   if(0 == mReferences++) {
      mSocket = socket(PF_INET, SOCK_DGRAM, getprotobyname("udp")->p_proto);
      if(mSocket != -1) {
	 int on = 1;
	 setsockopt(mSocket, SOL_SOCKET, SO_BROADCAST, (char *)&on, sizeof(on));
	 struct sockaddr_in addr;
	 memset(&addr, 0, sizeof(addr));
	 addr.sin_family = AF_INET;
	 addr.sin_port = htons(42424);
	 addr.sin_addr.s_addr = INADDR_ANY;
	 bind(mSocket, (struct sockaddr *)&addr, sizeof(addr));
      }
   }
}

/***********************************************//**
 * Copy constructor
 * @param source object instance to copy
 **************************************************/
CConnectionManager::CConnectionManager(const CConnectionManager &source)
{
   *this = source;
}

/***********************************************//**
 * Destructor
 **************************************************/
CConnectionManager::~CConnectionManager()
{
   if(--mReferences) {
      for(map<Descent_Socket, CConnection *>::iterator i = mConnections.begin(); i != mConnections.end(); i++) {
	 delete i->second;
      }
      mConnections.clear();
      mGames.clear();
      mGameAges.clear();
      if(mSocket >= 0) {
	 Descent_CloseSocket(mSocket);
	 mSocket = -1;
      }
   }
}

/***********************************************//**
 * Copy Assignment operator
 * @param source object instance to copy
 * @returns a reference to this object
 **************************************************/
CConnectionManager &CConnectionManager::operator=(const CConnectionManager &source)
{
   mReferences++;
   return *this;
}

/***********************************************//**
 * Singleton Accessor
 * @returns a reference to the singleton instance of this object
 **************************************************/
CConnectionManager CConnectionManager::get_Instance()
{
   return CConnectionManager();
}

void CConnectionManager::Pulse()
{
   fd_set read;
   struct timeval tv;
   int result;
   int max = mSocket;
   char packetId;
   struct sockaddr_in addr;
   socklen_t len;

   FD_ZERO(&read);
   
   FD_SET(mSocket, &read);
   for(map<Descent_Socket, CConnection *>::iterator i = mConnections.begin(); i != mConnections.end(); i++) {
      if(i->second != NULL) {
	 FD_SET(i->first, &read);
	 if(max > (int)i->first) max = i->first;
      }
   }
   
   tv.tv_sec = 0;
   tv.tv_usec = 10;
   
   result = select(max + 1, &read, NULL, NULL, &tv);
   
   if (result > 0) {
      global_Log.Write(LogType_Debug, 100, "Received a packet");
      if(FD_ISSET(mSocket, &read)) {
	 len = sizeof(addr);
	 if(recvfrom(mSocket, &packetId, 1, MSG_PEEK, (struct sockaddr *)&addr, &len) > 0) {
	    switch(packetId) {
	     case UPID_GAME_INFO_LITE:
	     case UPID_GAME_INFO:
	     default:
		 //throw the packet away
		 recvfrom(mSocket, &packetId, 1, 0, (struct sockaddr *)&addr, &len);
	       break;
	    }
	 }
      }
      for(map<Descent_Socket, CConnection *>::iterator i = mConnections.begin(); i != mConnections.end(); i++) {
	 if(i->second != NULL && FD_ISSET(mSocket, &read)) {
	    len = sizeof(addr);
	    if(recvfrom(mSocket, &packetId, 1, MSG_PEEK, (struct sockaddr *)&addr, &len) > 0) {
	       switch(packetId) {
		case UPID_GAME_INFO_LITE:
		case UPID_GAME_INFO:
		default:
		    //throw the packet away
		    recvfrom(mSocket, &packetId, 1, 0, (struct sockaddr *)&addr, &len);
		  break;
	       }
	    }
	 }
      }
   }
}
