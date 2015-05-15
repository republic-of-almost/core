#ifndef GENERAL_INCLUDED_BA1581F2_35C3_4026_BCDA_6E9EC3CF253E
#define GENERAL_INCLUDED_BA1581F2_35C3_4026_BCDA_6E9EC3CF253E


#include <cmath>
#include <algorithm>


namespace caffeine {
namespace math {


// Interface

inline float              sqrt(const float x);
inline float              clamp(const float x, const float between_a, const float between_b);

inline float              cos(const float radians);
inline float              a_cos(const float radians);
inline float              sin(const float radians);
inline float              a_sin(const float radians);


// Impl


float
sqrt(const float x)
{
  return std::sqrt(x);
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


} // namespace
} // namespace


#endif // include guard