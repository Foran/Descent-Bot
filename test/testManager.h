#ifndef __TESTMANAGER_H__
#define __TESTMANAGER_H__

#include "test.h"

#include <map>
#include <string>
#include <vector>

using namespace std;

class CTestManager 
{
 public:
   CTestManager();
   ~CTestManager();
   
   static CTestManager &get_Instance();
   
   iTestClass &operator[](const string &testClass);
   vector<string> get_TestClasses() const;
 protected:
   static map<string, iTestClass *> mTestClasses;
 private:
   CTestManager(const CTestManager &source);
   void operator=(const CTestManager &source);
};

extern CTestManager TestManager;

#endif
