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
#ifndef LIB_NETWORK_CONNECTION_H_
#define LIB_NETWORK_CONNECTION_H_

#include <string.h>

#include <iostream>

#include "lib/network/network.h"
#include "lib/network/packets.h"

namespace DESCENT_BOT {
namespace LIB {
namespace NETWORK {

class CConnection {
 public:
  void find_Game();
  void ProcessInboundPackets();

 private:
  Descent_Socket mSocket;

  CConnection();
  CConnection(const CConnection &source);
  ~CConnection();
  CConnection &operator=(const CConnection &source);

  friend class CConnectionManager;
};

}  // namespace NETWORK
}  // namespace LIB
}  // namespace DESCENT_BOT

#endif  // LIB_NETWORK_CONNECTION_H_
