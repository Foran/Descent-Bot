#include "testbase.h"

vector<string> CTestBase::get_Tests() const
{
   vector<string> retval;
   
   for(map<string, TestPtr>::const_iterator i = mTests.begin(); i != mTests.end(); i++) {
      retval.push_back(i->first);
   }
   
   return retval;
}

TestPtr CTestBase::operator[](const string &test)
{
   return mTests[test];
}
