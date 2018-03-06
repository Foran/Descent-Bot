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
