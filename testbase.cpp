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
