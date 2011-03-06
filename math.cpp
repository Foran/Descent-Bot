#include "math.h"

float DESCENT_FIXED::get_Value()
{
   return ((float)value.raw) / 65536.0;
}

void DESCENT_FIXED::set_Value(float f)
{
   value.raw = f * 65536;
}

void DESCENT_FIXED::set_Value(int i)
{
   value.parts.hi = i;
   value.parts.lo = 0;
}

/********************************
 * This method compartmentalizes
 * the loading of fixed data types
 *******************************/
istream &operator>>(istream &input, DESCENT_FIXED &fixed)
{
   input.read((char *)&fixed.value.raw, sizeof(fixed.value.raw));
   return input;
}

/********************************
 * This method compartmentalizes
 * the displaying of fixed data types
 *******************************/
ostream &operator<<(ostream &output, DESCENT_FIXED &fixed)
{
   output << fixed.get_Value();
   return output;
}

/********************************
 * This method compartmentalizes
 * the loading of fixed data types
 *******************************/
istream &operator>>(istream &input, DESCENT_SHORTFIXED &fixed)
{
   input.read((char *)&fixed.value.raw, sizeof(fixed.value.raw));
   return input;
}
