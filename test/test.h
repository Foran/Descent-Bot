#ifndef __TEST_H__
#define __TEST_H__

#include <vector>
#include <string>
#include <exception>

using namespace std;

typedef struct iTestContainer 
{
} iTestContainer;

typedef void (iTestContainer::*TestPtr)();

typedef struct iTestClass : public iTestContainer
{
   virtual void TestInitialize() = 0;
   virtual vector<string> get_Tests() const = 0;
   virtual TestPtr operator[](const string &test) = 0;
   virtual void TestCleanup() = 0;
} iTestClass;

class Assert : public exception
{
 public:
   Assert(const string &message);
   ~Assert() throw();
   
   virtual const char *what() const throw();
   
   static void Pass();
   static void Pass(const string &message);
   static void Fail();
   static void Fail(const string &message);
   static void IsTrue(const bool value);
   static void IsTrue(const bool value, const string &message);
   static void IsFalse(const bool value);
   static void IsFalse(const bool value, const string &message);
   template<typename T> static void AreEqual(const T &expected, const T &actual);
   template<typename T> static void AreEqual(const T &expected, const T &actual, const string &message);
   template<typename T> static void AreNotEqual(const T &expected, const T &actual);
   template<typename T> static void AreNotEqual(const T &expected, const T &actual, const string &message);
 protected:
   string mMessage;
 private:
   Assert();
};

#endif
