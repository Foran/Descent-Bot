#ifndef __PACKETS_H__
#define __PACKETS_H__

/*************************************
 * UDP Packet ID's taken directly from
 * D1X-Rebirth source
 *************************************/
enum UDP_PacketType 
{
   UPID_VERSION_DENY = 1,		// Netgame join or info has been denied due to version difference.
     UPID_GAME_INFO_REQ,		// Requesting all info about a netgame.
     UPID_GAME_INFO,			// Packet containing all info about a netgame.
     UPID_GAME_INFO_LITE_REQ,		// Requesting lite info about a netgame. Used for discovering games.
     UPID_GAME_INFO_LITE,		// Packet containing lite netgame info.
     UPID_DUMP,				// Packet containing why player cannot join this game.
     UPID_ADDPLAYER,			// Packet from Host containing info about a new player.
     UPID_REQUEST,			// New player says: "I want to be inside of you!" (haha, sorry I could not resist) / Packet containing request to join the game actually.
     UPID_QUIT_JOINING,			// Packet from a player who suddenly quits joining.
     UPID_SYNC,				// Packet from host containing full netgame info to sync players up.
     UPID_OBJECT_DATA,			// Packet from host containing object buffer.
     UPID_PING,				// Packet from host containing his GameTime and the Ping list. Client returns this time to host as UPID_PONG and adapts the ping list.
     UPID_PONG,				// Packet answer from client to UPID_PING. Contains the time the initial ping packet was sent.
     UPID_ENDLEVEL_H,			// Packet from Host to all Clients containing connect-states and kills information about everyone in the game.
     UPID_ENDLEVEL_C,			// Packet from Client to Host containing connect-state and kills information from this Client.
     UPID_PDATA_H,			// Packet from Host to all Clients containing all players movement data.
     UPID_PDATA_C,			// Packet from Client to Host containing his movement data.
     UPID_MDATA_P0,			// Packet containing multi buffer from a player. Priority 0 - no ACK needed.
     UPID_MDATA_P1,			// Packet containing multi buffer from a player. Priority 1 - ACK needed. Also contains pkt_num
     UPID_MDATA_ACK			// ACK packet for UPID_MDATA_P1.
}

struct PACKET_Header 
{
   unsigned char Packet_Type;
};

struct PACKET_Version_Deny 
{
   PACKET_Header Header;
   short Major;
   short Minor;
   short Micro;
};

struct PACKET_Request_Game_Info
{
   PACKET_Header Header;
   int Request_ID;
   short Major;
   short Minor;
   short Micro;
};

struct PACKET_Request_Game_Info_Lite
{
   PACKET_Header Header;
   int Request_ID;
   short Major;
   short Minor;
   short Micro;
};

struct PACKET_Game_Info 
{
   PACKET_Header Header;
   short Major;
   short Minor;
   short Micro;
   char Game_Name[16];
   char Mission_Title[22];
   char Mission_Name[9];
   int Level_Num;
   char Game_Mode;
   char RefusePlayers;
   char Difficulty;
   char Game_Status;
   char Num_Connected;
   char Max_Players;
   char Game_Flags;
   char Team_Vector;
};

#endif

