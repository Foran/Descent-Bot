#include "testManager.h"

CTestManager TestManager;
map<string, iTestClass *> CTestManager::mTestClasses;

CTestManager::CTestManager()
{
}

CTestManager::~CTestManager()
{
}
   
CTestManager &CTestManager::get_Instance()
{
   return TestManager;
}

iTestClass &CTestManager::operator[](const string &testClass)
{
   return *CTestManager::mTestClasses[testClass];
}

vector<string> CTestManager::get_TestClasses() const
{
   vector<string> retval;
   
   for(map<string, iTestClass *>::const_iterator i = CTestManager::mTestClasses.begin(); i != CTestManager::mTestClasses.end(); i++) {
	retval.push_back(i->first);
   }
      
   return retval;
}
