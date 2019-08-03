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

#include <iostream>
#include <string>

#include "lib/context/application_context.h"
#include "lib/log/log.h"
#include "lib/log/log_type.h"
#include "protos/lib/network/udp_packet_type.pb.h"

using ::DESCENT_BOT::LIB::CONTEXT::CApplicationContext;
using ::DESCENT_BOT::LIB::LOG::CLog;
using ::DESCENT_BOT::LIB::LOG::LogType;
using ::std::endl;
using ::std::ostream;
using ::std::string;

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
  LOG_GLOBAL(LogType::LogType_Debug, 100) << strerror(err);
}

PACKET_Request_Game_Info_Lite CPacket_Request_Game_Info_Lite::Recv(
  int socket) {
  PACKET_Request_Game_Info_Lite packet;
  struct sockaddr_in addr;
  socklen_t fromLen = sizeof(addr);
  recvfrom(socket, reinterpret_cast<char *>(&packet), sizeof(packet), 0,
    (struct sockaddr *)&addr, reinterpret_cast<socklen_t *>(&fromLen));
  return packet;
}

ostream &operator<<(ostream &output,
  const PACKET_Request_Game_Info_Lite &packet) {
  output << "Type: "
         << PROTO::UDP_PacketType_Name((PROTO::UDP_PacketType)packet.Type)
         << "\n";
  output << "Major: " << packet.Major << "\n";
  output << "Minor: " << packet.Minor << "\n";
  output << "Micro: " << packet.Micro;
  return output;
}

void CPacket_Game_Info_Lite::Send(int socket,
                                  const struct sockaddr_in &addr) {
}

PACKET_Game_Info_Lite CPacket_Game_Info_Lite::Recv(int socket) {
  PACKET_Game_Info_Lite packet;
  struct sockaddr_in addr;
  socklen_t fromLen = sizeof(addr);
  int len = recvfrom(socket, reinterpret_cast<char *>(&packet),
    sizeof(packet), 0, (struct sockaddr *)&addr,
    reinterpret_cast<socklen_t *>(&fromLen));
  char addrstr[16];
  inet_ntop(AF_INET, &(addr.sin_addr), addrstr, 16);
  LOG_GLOBAL(LogType::LogType_Debug, 100) << "Received " << len
    << " bytes from "
    << addrstr << ":" << addr.sin_port;
  return packet;
}

ostream &operator<<(ostream &output, const PACKET_Game_Info_Lite &packet) {
  output << "Type: "
         << PROTO::UDP_PacketType_Name((PROTO::UDP_PacketType)packet.Type)
         << "\n";
  output << "Major: " << packet.Major << "\n";
  output << "Minor: " << packet.Minor << "\n";
  output << "Micro: " << packet.Micro << "\n";
  output << "Game ID: " << packet.Game_Id << "\n";
  output << "Level Num: " << packet.Level_Num << "\n";
  output << "Game Mode: " << static_cast<int>(packet.Game_Mode) << "\n";
  output << "Refuse Players: " << static_cast<int>(packet.RefusePlayers)
         << "\n";
  output << "Difficulty: " << static_cast<int>(packet.Difficulty) << "\n";
  output << "Game Status: " << static_cast<int>(packet.Game_Status) << "\n";
  output << "Num Connected: " << static_cast<int>(packet.Num_Connected) << "\n";
  output << "Max Players: " << static_cast<int>(packet.Max_Players) << "\n";
  output << "Game Flags: " << static_cast<int>(packet.Game_Flags) << "\n";
  output << "Game_Name: " << packet.Game_Name;
  return output;
}

}  // namespace NETWORK
}  // namespace LIB
}  // namespace DESCENT_BOT
