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
#include "src/lib/network/connectionmanager.h"

using ::DESCENT_BOT::SRC::LIB::LOG::global_Log;
using ::DESCENT_BOT::SRC::LIB::LOG::LogType;
using ::std::map;
using ::std::string;

namespace DESCENT_BOT {
namespace SRC {
namespace LIB {
namespace NETWORK {

int CConnectionManager::mReferences = 0;
Descent_Socket CConnectionManager::mSocket = -1;
map<Descent_Socket, CConnection *> CConnectionManager::mConnections;
map<struct sockaddr_in, string> CConnectionManager::mGames;
map<string, time_t> CConnectionManager::mGameAges;

/**
 * Default constructor
 **************************************************/
CConnectionManager::CConnectionManager() {
   if(0 == mReferences++) {
      mSocket = CNetwork::get_Instance().socket(PF_INET, SOCK_DGRAM, CNetwork::get_Instance().getprotobyname("udp")->p_proto);
      if(mSocket != -1) {
	 int on = 1;
	 CNetwork::get_Instance().setsockopt(mSocket, SOL_SOCKET, SO_BROADCAST, (char *)&on, sizeof(on));
	 struct sockaddr_in addr;
	 memset(&addr, 0, sizeof(addr));
	 addr.sin_family = AF_INET;
	 addr.sin_port = htons(42424);
	 addr.sin_addr.s_addr = INADDR_ANY;
	 CNetwork::get_Instance().bind(mSocket, (struct sockaddr *)&addr, sizeof(addr));
      }
   }
}

/**
 * Copy constructor
 * @param source object instance to copy
 **************************************************/
CConnectionManager::CConnectionManager(const CConnectionManager &source) {
  *this = source;
}

/**
 * Destructor
 **************************************************/
CConnectionManager::~CConnectionManager() {
   if(--mReferences) {
      for(auto& pair : mConnections) {
	 delete pair.second;
      }
      mConnections.clear();
      mGames.clear();
      mGameAges.clear();
      if(mSocket >= 0) {
	 CNetwork::get_Instance().close(mSocket);
	 mSocket = -1;
      }
   }
}

/**
 * Copy Assignment operator
 * @param source object instance to copy
 * @returns a reference to this object
 **************************************************/
CConnectionManager &CConnectionManager::operator=(const CConnectionManager &source) {
  mReferences++;
  return *this;
}

/**
 * Singleton Accessor
 * @returns a reference to the singleton instance of this object
 **************************************************/
CConnectionManager CConnectionManager::get_Instance() {
  return CConnectionManager();
}

void CConnectionManager::Pulse() {
   fd_set read;
   struct timeval tv;
   int result;
   int max = mSocket;
   char packetId;
   struct sockaddr_in addr;
   socklen_t len;

   FD_ZERO(&read);
   
   FD_SET(mSocket, &read);
   for(auto& pair : mConnections) {
      if(pair.second != NULL) {
	 FD_SET(pair.first, &read);
	 if(max > (int)pair.first) max = pair.first;
      }
   }
   
   tv.tv_sec = 0;
   tv.tv_usec = 10;
   
   result = CNetwork::get_Instance().select(max + 1, &read, NULL, NULL, &tv);
   
   if(result > 0) {
      global_Log.Write(LogType::LogType_Debug, 100, "Received a packet");
      if(FD_ISSET(mSocket, &read)) {
	 len = sizeof(addr);
	 if(CNetwork::get_Instance().recvfrom(mSocket, &packetId, 1, MSG_PEEK, (struct sockaddr *)&addr, &len) > 0) {
	    switch(packetId) {
	     case UPID_GAME_INFO_LITE:
	     case UPID_GAME_INFO:
	     default:
		 //throw the packet away
		 CNetwork::get_Instance().recvfrom(mSocket, &packetId, 1, 0, (struct sockaddr *)&addr, &len);
	         break;
	    }
	 }
      }
      for(auto& pair : mConnections) {
	 if(pair.second != NULL && FD_ISSET(mSocket, &read)) {
	    len = sizeof(addr);
	    if(CNetwork::get_Instance().recvfrom(mSocket, &packetId, 1, MSG_PEEK, (struct sockaddr *)&addr, &len) > 0) {
	       switch(packetId) {
		case UPID_GAME_INFO_LITE:
		case UPID_GAME_INFO:
		default:
		    //throw the packet away
		    CNetwork::get_Instance().recvfrom(mSocket, &packetId, 1, 0, (struct sockaddr *)&addr, &len);
		    break;
	       }
	    }
	 }
      }
   }
}

}  // namespace NETWORK
}  // namespace LIB
}  // namespace SRC
}  // namespace DESCENT_BOT
