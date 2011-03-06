#ifndef __MATH_H__
#define __MATH_H__

#include <iostream>

using namespace std;

typedef struct DESCENT_FIXED 
{
   union {
      int raw;
      struct {
	 short hi;
	 unsigned short lo;
      } parts;
   } value;
   float get_Value();
   void set_Value(float f);
   void set_Value(int i);
 private:
   friend class DESCENT_VERTEX;
   friend class CRdl;
   friend istream &operator>>(istream &input, DESCENT_FIXED &fixed);
   friend ostream &operator<<(ostream &output, DESCENT_FIXED &fixed);
} DESCENT_FIXED;

typedef struct DESCENT_SHORTFIXED
{
   union {
      short raw;
      struct {
	 signed hi: 4;
	 unsigned lo: 12;
      } parts;
   } value;
 private:
   friend class DESCENT_VERTEX;
   friend class CRdl;
   friend istream &operator>>(istream &input, DESCENT_SHORTFIXED &fixed);
} DESCENT_SHORTFIXED;

#endif
