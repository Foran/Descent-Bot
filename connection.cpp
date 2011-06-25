/****************************************************
 * This work is licensed under the Creative
 * Commons Attribution-NonCommercial-ShareAlike
 * 3.0 Unported License. To view a copy of this
 * license, visit
 * http://creativecommons.org/licenses/by-nc-sa/3.0/
 * or send a letter to Creative Commons, 444
 * Castro Street, Suite 900, Mountain View,
 * California, 94041, USA.
 ***************************************************/
#include "connection.h"

CConnection::CConnection()
{
   mSocket = socket(PF_INET, SOCK_DGRAM, getprotobyname("udp")->p_proto);
   if(mSocket != -1) {
      int on = 1;
      setsockopt(mSocket, SOL_SOCKET, SO_BROADCAST, &on, sizeof(on));
   }
}

CConnection::~CConnection()
{
   if(mSocket != -1) close(mSocket);
}

void CConnection::find_Game()
{
   struct sockaddr_in addr;
   memset(&addr, 0, sizeof(addr));
   addr.sin_family = AF_INET;
   addr.sin_port = htons(42424);
   inet_aton("192.168.2.32", (struct in_addr *)&addr.sin_addr.s_addr);
   CPacket_Request_Game_Info_Lite request_packet;
   request_packet.Send(mSocket, addr);
   PACKET_Game_Info_Lite packet;
   socklen_t len;
   recvfrom(mSocket, &packet, 1, MSG_PEEK, (struct sockaddr *)&addr, &len);
   if(packet.Type == UPID_GAME_INFO_LITE) {
      recvfrom(mSocket, &packet, sizeof(packet), 0, (struct sockaddr *)&addr, &len);
      cout << packet.Game_Name << endl;
      cout << packet.Mission_Title << endl;
      cout << packet.Mission_Name << endl;
      cout << packet.Level_Num << endl;
   }
}

void CConnection::ProcessInboundPackets()
{
}

