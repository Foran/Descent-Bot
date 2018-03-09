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
#ifndef SRC_LIB_NETWORK_CONNECTION_H_
#define SRC_LIB_NETWORK_CONNECTION_H_

#include <string.h>

#include <iostream>

#include "src/lib/network/network.h"
#include "src/lib/network/packets.h"

namespace DESCENT_BOT {
namespace SRC {
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
}  // namespace SRC
}  // namespace DESCENT_BOT

#endif  // SRC_LIB_NETWORK_CONNECTION_H_
