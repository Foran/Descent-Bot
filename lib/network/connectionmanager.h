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
#ifndef LIB_NETWORK_CONNECTIONMANAGER_H_
#define LIB_NETWORK_CONNECTIONMANAGER_H_

#include <string.h>
#include <time.h>

#include <map>
#include <string>

#include "lib/context/component.h"
#include "lib/context/context.h"
#include "lib/log/log.h"
#include "lib/network/network.h"
#include "lib/network/packets.h"
#include "lib/network/connection.h"

namespace DESCENT_BOT {
namespace LIB {
namespace NETWORK {

/// Singleton that manages all connection objects
/**
 * Manages all instances of CConnection
 * @see CConnection
 ***********************************************/
class CConnectionManager : public ::DESCENT_BOT::LIB::CONTEXT::CComponent {
 public:
  explicit CConnectionManager(
    ::DESCENT_BOT::LIB::CONTEXT::CContext *context);
  CConnectionManager(const CConnectionManager &source);
  ~CConnectionManager();

  CConnectionManager &operator=(const CConnectionManager &source);

  ::std::string getName() const;
  void Pulse();

 private:
  Descent_Socket mSocket;
  ::std::map<Descent_Socket, CConnection *> mConnections;
  ::std::map<struct sockaddr_in, ::std::string> mGames;
  ::std::map<::std::string, time_t> mGameAges;
  ::DESCENT_BOT::LIB::CONTEXT::CContext *mContext;
};

}  // namespace NETWORK
}  // namespace LIB
}  // namespace DESCENT_BOT

#endif  // LIB_NETWORK_CONNECTIONMANAGER_H_
