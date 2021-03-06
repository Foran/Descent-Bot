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
#include "lib/network/connectionmanager.h"

#include "lib/context/context.h"
#include "protos/lib/network/udp_packet_type.pb.h"

using ::DESCENT_BOT::LIB::CONTEXT::CContext;
using ::DESCENT_BOT::LIB::LOG::CLog;
using ::DESCENT_BOT::LIB::LOG::LogType;
using ::std::map;
using ::std::string;

namespace DESCENT_BOT {
namespace LIB {
namespace NETWORK {

/**
 * Default constructor
 **************************************************/
CConnectionManager::CConnectionManager(CContext *context) {
  mContext = context;
  mSocket = -1;
  mSocket = CNetwork::get_Instance().socket(PF_INET, SOCK_DGRAM,
              CNetwork::get_Instance().getprotobyname("udp")->p_proto);
  if (mSocket != -1) {
    int on = 1;
    CNetwork::get_Instance().setsockopt(mSocket, SOL_SOCKET, SO_BROADCAST,
                                        reinterpret_cast<char *>(&on),
                                        sizeof(on));
    struct sockaddr_in addr;
    memset(&addr, 0, sizeof(addr));
    addr.sin_family = AF_INET;
    addr.sin_port = htons(42424);
    addr.sin_addr.s_addr = INADDR_ANY;
    CNetwork::get_Instance().bind(mSocket, (struct sockaddr *)&addr,
                                  sizeof(addr));
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
  for (auto& pair : mConnections) {
    delete pair.second;
  }
  mConnections.clear();
  mGames.clear();
  mGameAges.clear();
  if (mSocket >= 0) {
    CNetwork::get_Instance().close(mSocket);
    mSocket = -1;
  }
}

/**
 * Copy Assignment operator
 * @param source object instance to copy
 * @returns a reference to this object
 **************************************************/
CConnectionManager &CConnectionManager::operator=(
                                        const CConnectionManager &source) {
  return *this;
}

::std::string CConnectionManager::getName() const {
  return "ConnectionManager";
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
  for (auto& pair : mConnections) {
    if (pair.second != NULL) {
      FD_SET(pair.first, &read);
      if (max > static_cast<int>(pair.first)) max = pair.first;
    }
  }

  tv.tv_sec = 0;
  tv.tv_usec = 10;

  result = CNetwork::get_Instance().select(max + 1, &read, NULL, NULL, &tv);

  if (result > 0) {
    if (FD_ISSET(mSocket, &read)) {
      len = sizeof(addr);
      if (CNetwork::get_Instance().recvfrom(mSocket, &packetId, 1, MSG_PEEK,
                                      (struct sockaddr *)&addr, &len) > 0) {
        LOG(LogType::LogType_Debug, 100) << "Recieved a packet ("
          << PROTO::UDP_PacketType_Name((PROTO::UDP_PacketType)packetId)
          << ")";
        switch (packetId) {
          case UPID_GAME_INFO_LITE_REQ:
            {
              CPacket_Request_Game_Info_Lite request_packet;
              PACKET_Request_Game_Info_Lite packet =
                request_packet.Recv(mSocket);
              LOG(LogType::LogType_Debug, 100) << packet;
            }
            break;
          case UPID_GAME_INFO_LITE:
            {
              CPacket_Game_Info_Lite gameinfo_packet;
              PACKET_Game_Info_Lite packet = gameinfo_packet.Recv(mSocket);
              LOG(LogType::LogType_Debug, 100) << packet;
            }
            break;
          case UPID_GAME_INFO:
          default:
            LOG(LogType::LogType_Debug, 100) << "Throwing packet away";
            // throw the packet away
            CNetwork::get_Instance().recvfrom(mSocket, &packetId, 1, 0,
              (struct sockaddr *)&addr, &len);
            break;
        }
      }
    }
    for (auto& pair : mConnections) {
      if (pair.second != NULL && FD_ISSET(mSocket, &read)) {
        len = sizeof(addr);
        if (CNetwork::get_Instance().recvfrom(mSocket, &packetId, 1,
          MSG_PEEK, (struct sockaddr *)&addr, &len) > 0) {
          switch (packetId) {
            case UPID_GAME_INFO_LITE:
            case UPID_GAME_INFO:
            default:
              // throw the packet away
              CNetwork::get_Instance().recvfrom(mSocket, &packetId, 1, 0,
                (struct sockaddr *)&addr, &len);
              break;
          }
        }
      }
    }
  }
}

}  // namespace NETWORK
}  // namespace LIB
}  // namespace DESCENT_BOT
