#ifndef GENERAL_INCLUDED_BA1581F2_35C3_4026_BCDA_6E9EC3CF253E
#define GENERAL_INCLUDED_BA1581F2_35C3_4026_BCDA_6E9EC3CF253E


/*
  These are general math functions and constants.
  Alot of them are simple stubs to stl functions.
*/


#include <cmath>
#include <algorithm>
#include "../detail/detail.hpp"


namespace math {


// ** INTERFACE ** //


// ** Constants ** //

MATH_GENR_INLINE float              pi()          { return 3.14159265359f;  }
MATH_GENR_INLINE float              two_pi()      { return 2.f * pi();      }
MATH_GENR_INLINE float              half_pi()     { return pi() * 0.5f;     }
MATH_GENR_INLINE float              tau()         { return two_pi();        }
MATH_GENR_INLINE float              half_tau()    { return pi();            }
MATH_GENR_INLINE float              quart_tau()   { return half_pi();       }
MATH_GENR_INLINE float              g_ratio()     { return 1.61803398875f;  }
MATH_GENR_INLINE float              root_two()    { return 1.41421356237f;  }
MATH_GENR_INLINE float              root_three()  { return 1.73205080757f;  }


// ** Trig ** //

MATH_GENR_INLINE float              tan(const float x);
MATH_GENR_INLINE float              a_tan2(const float x, const float y);
MATH_GENR_INLINE float              cos(const float radians);
MATH_GENR_INLINE float              a_cos(const float radians);
MATH_GENR_INLINE float              sin(const float radians);
MATH_GENR_INLINE float              a_sin(const float radians);


// ** Degs/Rads ** //

MATH_GENR_INLINE float              radians_to_degrees(const float radians); // TODO:
MATH_GENR_INLINE float              degrees_to_radians(const float degrees); // TODO:


// ** Other general ** //

MATH_GENR_INLINE float              sqrt(const float x);
MATH_GENR_INLINE float              abs(const float x);
MATH_GENR_INLINE float              max(const float a, const float b);
MATH_GENR_INLINE float              min(const float a, const float b);
MATH_GENR_INLINE float              clamp(const float x, const float between_a, const float between_b);
MATH_GENR_INLINE bool               is_between(const float to_check, const float a, const float b); // TODO:
MATH_GENR_INLINE bool               is_near(const float actual, const float target, const float error_margin); // TODO:
MATH_GENR_INLINE bool               is_pow_two(const uint32_t i); // TODO:
MATH_GENR_INLINE bool               fmod(const float x, const float max); // TODO;
MATH_GENR_INLINE float              sign(const float x); // Returns 1 or -1


// ** Search ** //
MATH_GENR_INLINE bool               index_linear_search(const uint32_t to_find, const uint32_t search[], const size_t size_of_search, size_t *out_result);


// ** IMPL ** //


float
sqrt(const float x)
{
  return std::sqrt(x);
}


float
max(const float x, const float y)
{
  return std::max(x, y);
}


float
min(const float x, const float y)
{
  return std::min(x, y);
}


float
clamp(const float x, const float between_a, const float between_b)
{
  const float highest = between_a >= between_b ? between_a : between_b;
  const float lowest  = between_a != highest ? between_a : between_b;

  if(x >= highest)
  {
    return highest;
  }
  else if(x <= lowest)
  {
    return lowest;
  }

  return x;
}


float
abs(const float x)
{
  return std::abs(x);
}


float
tan(const float x)
{
  return std::tan(x);
}


float
a_tan2(const float x, const float y)
{
  return std::atan2(x, y);
}


float
cos(const float radians)
{
  return std::cos(radians);
}


float
a_cos(const float radians)
{
  return std::acos(radians);
}


float
sin(const float radians)
{
  return std::sin(radians);
}


float
a_sin(const float radians)
{
  return std::asin(radians);
}


float
radians_to_degrees(const float radians)
{
  return radians * (180.f / pi());
}

float
degrees_to_radians(const float degrees)
{
  return degrees * (pi() / 180.f);
}


float
sign(const float x)
{
  return x >= 0.f ? 1.f : -1.f;
}


bool
index_linear_search(const uint32_t to_find, const uint32_t search[], const size_t size_of_search, size_t *out_result)
{
  for(std::size_t i = 0; i < size_of_search; ++i)
  {
    if(search[i] == to_find)
    {
      (*out_result) = i;
      return true;
    }
  }

  return false;
}


} // namespace


#endif // include guard
