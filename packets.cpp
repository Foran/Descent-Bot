#include "packets.h"

void CPacket_Request_Game_Info_Lite::Send(int socket, const struct sockaddr_in &addr)
{
   PACKET_Request_Game_Info_Lite packet;
   packet.Type = UPID_GAME_INFO_LITE_REQ;
   packet.Request_ID = 0x52583144;
   packet.Major = 0;
   packet.Minor = 56;
   packet.Micro = 0;
   sendto(socket, (void *)&packet, sizeof(packet), 0, (const struct sockaddr *)&addr, sizeof(addr));
   int err = errno;
   cout << strerror(err) << endl;
}
