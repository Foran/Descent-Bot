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
#ifndef SRC_LIB_NETWORK_CONNECTIONMANAGER_H_
#define SRC_LIB_NETWORK_CONNECTIONMANAGER_H_

#include <string.h>
#include <time.h>

#include <map>
#include <string>

#include "src/lib/network/network.h"
#include "src/lib/network/packets.h"
#include "src/lib/network/connection.h"
#include "src/lib/log/log.h"

namespace DESCENT_BOT {
namespace SRC {
namespace LIB {
namespace NETWORK {

/// Singleton that manages all connection objects
/**
 * Manages all instances of CConnection
 * @see CConnection
 ***********************************************/
class CConnectionManager {
 public:
  CConnectionManager();
  CConnectionManager(const CConnectionManager &source);
  ~CConnectionManager();

  CConnectionManager &operator=(const CConnectionManager &source);

  static CConnectionManager get_Instance();
  void Pulse();

 private:
  static int mReferences;
  static Descent_Socket mSocket;
  static ::std::map<Descent_Socket, CConnection *> mConnections;
  static ::std::map<struct sockaddr_in, ::std::string> mGames;
  static ::std::map<::std::string, time_t> mGameAges;
};

}  // namespace NETWORK
}  // namespace LIB
}  // namespace SRC
}  // namespace DESCENT_BOT

#endif  // SRC_LIB_NETWORK_CONNECTIONMANAGER_H_
