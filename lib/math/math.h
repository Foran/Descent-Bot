/****************************************************
 * Copyright 2018 Ben M. Ward
 *
 * This work is licensed under the Creative
 * Commons Attribution-NonCommercial-ShareAlike
 * 3.0 Unported License. To view a copy of this
 * license, visit
 * http://creativecommons.org/licenses/by-nc-sa/3.0/
 * or send a letter to Creative Commons, 444
 * Castro Street, Suite 900, Mountain View,
 * California, 94041, USA.
 ***************************************************/
#ifndef LIB_MATH_MATH_H_
#define LIB_MATH_MATH_H_

#include <iostream>

namespace DESCENT_BOT {
namespace LIB {
namespace MATH {

/// This structure supports Long Fixed point math
typedef struct DESCENT_FIXED {
  union {
    int raw;
    struct {
      int16_t hi;
      uint16_t lo;
    } parts;
  } value;
  float get_Value();
  void set_Value(float f);
  void set_Value(int i);

 private:
  friend struct DESCENT_VERTEX;
  friend class CRdl;
  friend ::std::istream &operator>>(::std::istream &input,
                                    DESCENT_FIXED &fixed);
  friend ::std::ostream &operator<<(::std::ostream &output,
                                    DESCENT_FIXED &fixed);
} DESCENT_FIXED;

/// This structure supports Short Fixed point math
typedef struct DESCENT_SHORTFIXED {
  union {
    int16_t raw;
    struct {
      signed hi: 4;
      unsigned lo: 12;
    } parts;
  } value;

 private:
  friend struct DESCENT_VERTEX;
  friend class CRdl;
  friend ::std::istream &operator>>(::std::istream &input,
                                    DESCENT_SHORTFIXED &fixed);
} DESCENT_SHORTFIXED;

}  // namespace MATH
}  // namespace LIB
}  // namespace DESCENT_BOT

#endif  // LIB_MATH_MATH_H_
