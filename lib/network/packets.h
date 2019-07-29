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
#ifndef LIB_NETWORK_PACKETS_H_
#define LIB_NETWORK_PACKETS_H_

#include <errno.h>
#include <string.h>

#include <iostream>

#include "lib/network/network.h"

namespace DESCENT_BOT {
namespace LIB {
namespace NETWORK {

/*************************************
 * UDP Packet ID's taken directly from
 * D1X-Rebirth source
 *************************************/
enum UDP_PacketType {
  UPID_VERSION_DENY = 1,    // Netgame join or info has been denied due to
                            // version difference.
  UPID_GAME_INFO_REQ,       // Requesting all info about a netgame.
  UPID_GAME_INFO,           // Packet containing all info about a netgame.
  UPID_GAME_INFO_LITE_REQ,  // Requesting lite info about a netgame. Used for
                            // discovering games.
  UPID_GAME_INFO_LITE,      // Packet containing lite netgame info.
  UPID_DUMP,                // Packet containing why player cannot join this
                            // game.
  UPID_ADDPLAYER,           // Packet from Host containing info about a new
                            // player.
  UPID_REQUEST,             // New player says: "I want to be inside of you!"
                            // (haha, sorry I could not resist) / Packet
                            // containing request to join the game actually.
  UPID_QUIT_JOINING,        // Packet from a player who suddenly quits joining.
  UPID_SYNC,                // Packet from host containing full netgame info
                            // to sync players up.
  UPID_OBJECT_DATA,         // Packet from host containing object buffer.
  UPID_PING,                // Packet from host containing his GameTime and
                            // the Ping list. Client returns this time to host
                            // as UPID_PONG and adapts the ping list.
  UPID_PONG,                // Packet answer from client to UPID_PING.
                            // Contains the time the initial ping packet was
                            // sent.
  UPID_ENDLEVEL_H,          // Packet from Host to all Clients containing
                            // connect-states and kills information about
                            // everyone in the game.
  UPID_ENDLEVEL_C,          // Packet from Client to Host containing
                            // connect-state and kills information from this
                            // Client.
  UPID_PDATA_H,             // Packet from Host to all Clients containing all
                            // players movement data.
  UPID_PDATA_C,             // Packet from Client to Host containing his
                            // movement data.
  UPID_MDATA_P0,            // Packet containing multi buffer from a player.
                            // Priority 0 - no ACK needed.
  UPID_MDATA_P1,            // Packet containing multi buffer from a player.
                            // Priority 1 - ACK needed. Also contains pkt_num
  UPID_MDATA_ACK            // ACK packet for UPID_MDATA_P1.
};

struct PACKET_Header {
  char Type;
#ifdef _WIN32
};
#else
} __attribute__((__packed__, aligned(1)));
#endif

struct PACKET_Version_Deny {
  char Type;
  int16_t Major;
  int16_t Minor;
  int16_t Micro;
#ifdef _WIN32
};
#else
} __attribute__((__packed__, aligned(1)));
#endif

struct PACKET_Request_Game_Info {
  char Type;
  int Request_ID;
  int16_t Major;
  int16_t Minor;
  int16_t Micro;
#ifdef _WIN32
};
#else
} __attribute__((__packed__, aligned(1)));
#endif

struct PACKET_Request_Game_Info_Lite {
  char Type;
  int Request_ID;
  int16_t Major;
  int16_t Minor;
  int16_t Micro;
#ifdef _WIN32
};
#else
} __attribute__((__packed__, aligned(1)));
#endif

struct PACKET_Game_Info_Lite {
  char Type;
  int16_t Major;
  int16_t Minor;
  int16_t Micro;
  int Game_Id;
  int Level_Num;
  char Game_Mode;
  char RefusePlayers;
  char Difficulty;
  char Game_Status;
  char Num_Connected;
  char Max_Players;
  char Game_Flags;
  char Game_Name[26];
  char Mission_Title[26];
  char Mission_Name[9];
#ifdef _WIN32
};
#else
} __attribute__((__packed__, aligned(1)));
#endif

template<class T> struct CPacket {
  virtual void Send(int socket, const struct sockaddr_in &addr) = 0;
  virtual T Recv(int socket) = 0;
};

class CPacket_Request_Game_Info_Lite : public CPacket<PACKET_Request_Game_Info_Lite> {
 public:
  void Send(int socket, const struct sockaddr_in &addr) override;
  PACKET_Request_Game_Info_Lite Recv(int socket) override;
};

::std::ostream &operator<<(::std::ostream &output,
  const PACKET_Request_Game_Info_Lite &packet);

class CPacket_Game_Info_Lite : public CPacket<PACKET_Game_Info_Lite> {
 public:
  void Send(int socket, const struct sockaddr_in &addr) override;
  PACKET_Game_Info_Lite Recv(int socket) override;
};

::std::ostream &operator<<(::std::ostream &output,
  const PACKET_Game_Info_Lite &packet);

}  // namespace NETWORK
}  // namespace LIB
}  // namespace DESCENT_BOT

#endif  // LIB_NETWORK_PACKETS_H_
