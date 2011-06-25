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
#include "test.h"

/************************************************//**
 * Generic Assertion
 * @param message Message to throw for assertion
 ***************************************************/
Assert::Assert(const string &message)
{
   mMessage = message;
}

Assert::~Assert() throw()
{
}

const char *Assert::what() const throw()
{
   return mMessage.c_str();
}

void Assert::Pass()
{
}

void Assert::Pass(const string &message)
{
}

void Assert::Fail()
{
   Assert::Fail("No Message provided");
}

void Assert::Fail(const string &message)
{
   string temp = "Assert.Fail on line ";
   temp += __LINE__;
   throw new Assert(temp + " in " + __FILE__ + ": " + message);
}

void Assert::IsTrue(const bool value)
{
   if(!value) {
      string temp = "Assert.IsTrue failed on line ";
      temp += __LINE__;
      throw new Assert(temp + " in " + __FILE__);
   }
}

void Assert::IsTrue(const bool value, const string &message)
{
   if(!value) {
      string temp = "Assert.IsTrue failed on line ";
      temp += __LINE__;
      throw new Assert(temp + " in " + __FILE__ + ": " + message);
   }
}

void Assert::IsFalse(const bool value)
{
   if(value) {
      string temp = "Assert.IsFalse failed on line ";
      temp += __LINE__;
      throw new Assert(temp + " in " + __FILE__);
   }
}

void Assert::IsFalse(const bool value, const string &message)
{
   if(value) {
      string temp = "Assert.IsFalse failed on line ";
      temp +=  __LINE__;
      throw new Assert(temp + " in " + __FILE__ + ": " + message);
   }
}

template<typename T> void Assert::AreEqual(const T &expected, const T &actual)
{
   if(expected != actual) {
      string temp = "Assert.AreEqual failed on line ";
      temp +=  __LINE__;
      temp += " in ";
      temp += __FILE__;
      temp += "; Expected <";
      temp += expected;
      temp += ">, Actual <";
      temp += actual;
      temp += ">";
      throw new Assert(temp);
   }
}

template<typename T> void Assert::AreEqual(const T &expected, const T &actual, const string &message)
{
   if(expected != actual) {
      string temp = "Assert.AreEqual failed on line ";
      temp +=  __LINE__;
      temp += " in ";
      temp += __FILE__;
      temp += "; Expected <";
      temp += expected;
      temp += ">, Actual <";
      temp += actual;
      temp += ">: ";
      throw new Assert(temp + message);
   }
}

template<typename T> void Assert::AreNotEqual(const T &expected, const T &actual)
{
   if(expected == actual) {
      string temp = "Assert.AreNotEqual failed on line ";
      temp +=  __LINE__;
      temp += " in ";
      temp += __FILE__;
      temp += "; Expected <";
      temp += expected;
      temp += ">, Actual <";
      temp += actual;
      temp += ">";
      throw new Assert(temp);
   }
}

template<typename T> void Assert::AreNotEqual(const T &expected, const T &actual, const string &message)
{
   if(expected == actual) {
      string temp = "Assert.AreNotEqual failed on line ";
      temp +=  __LINE__;
      temp += " in ";
      temp += __FILE__;
      temp += "; Expected <";
      temp += expected;
      temp += ">, Actual <";
      temp += actual;
      temp += ">: ";
      throw new Assert(temp + message);
   }
}
