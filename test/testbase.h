#ifndef __TESTBASE_H__
#define __TESTBASE_H__



#include "test.h"
#include "testManager.h"

class CTestBase : public iTestClass
{
 public:
   virtual void TestInitialize() = 0;
   vector<string> get_Tests() const;
   TestPtr operator[](const string &test);
   virtual void TestCleanup() = 0;
 protected:
   map<string, TestPtr> mTests;
 private:
};

#endif
