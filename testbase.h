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
