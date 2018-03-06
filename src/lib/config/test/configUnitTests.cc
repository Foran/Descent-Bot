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
#include "gtest/gtest.h"
#include "src/lib/config/config.h"

class ConfigTest : public ::testing::Test {
 protected:
  ConfigTest() {
  }

  virtual ~ConfigTest() {
  }

  virtual void SetUp() {
  }

  virtual void TearDown() {
  }

 private:
};

TEST_F(ConfigTest, DefaultConstructor) {
//  EXPECT_EQ(0, a.GetHeaders().size());
}
