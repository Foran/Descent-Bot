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
