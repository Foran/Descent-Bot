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
#include <string>

#include "gtest/gtest.h"
#include "lib/network/packets.h"

using ::DESCENT_BOT::LIB::NETWORK::PACKET_Game_Info_Lite;
using ::DESCENT_BOT::LIB::NETWORK::UDP_PacketType;
using ::std::string;

class PacketTest : public ::testing::Test {
 protected:
  PacketTest() {
  }

  virtual ~PacketTest() {
  }

  virtual void SetUp() {
  }

  virtual void TearDown() {
  }

 private:
};

TEST_F(PacketTest, DefaultConstructor) {
  unsigned char buffer[] = {0x05, 0x00, 0x00, 0x38, 0x00, 0x00, 0x00, 0x66,
                            0x6f, 0x72, 0x61, 0x6e, 0x27, 0x73, 0x20, 0x67,
                            0x61, 0x6d, 0x65, 0x00, 0x00, 0x00, 0x00, 0x54,
                            0x6f, 0x74, 0x61, 0x6c, 0x20, 0x43, 0x68, 0x61,
                            0x6f, 0x73, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                            0x00, 0x00, 0x00, 0x00, 0x00, 0x43, 0x48, 0x41,
                            0x4f, 0x53, 0x00, 0x00, 0x00, 0x00};

  PACKET_Game_Info_Lite *packet =
                         reinterpret_cast<PACKET_Game_Info_Lite *>(buffer);
  EXPECT_EQ(UDP_PacketType::UPID_GAME_INFO_LITE, packet->Type);
  EXPECT_EQ(0, packet->Major);
  EXPECT_EQ(56, packet->Minor);
  EXPECT_EQ(0, packet->Micro);
  EXPECT_EQ(string("foran's game"), string(packet->Game_Name));
  EXPECT_EQ(string("Total Chaos"), string(packet->Mission_Title));
  EXPECT_EQ(string("CHAOS"), string(packet->Mission_Name));
}
