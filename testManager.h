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
