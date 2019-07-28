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
#include "lib/network/packets.h"

using ::std::cout;
using ::std::endl;

namespace DESCENT_BOT {
namespace LIB {
namespace NETWORK {

void CPacket_Request_Game_Info_Lite::Send(int socket,
                                          const struct sockaddr_in &addr) {
  PACKET_Request_Game_Info_Lite packet;
  packet.Type = UPID_GAME_INFO_LITE_REQ;
  packet.Request_ID = 0x52583144;
  packet.Major = 0;
  packet.Minor = 56;
  packet.Micro = 0;
  sendto(socket, reinterpret_cast<char *>(&packet), sizeof(packet), 0,
         (const struct sockaddr *)&addr, sizeof(addr));
  int err = errno;
  cout << strerror(err) << endl;
}

}  // namespace NETWORK
}  // namespace LIB
}  // namespace DESCENT_BOT
