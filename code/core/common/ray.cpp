#include <core/common/ray.hpp>
#include <math/vec/vec3.hpp>


namespace Core {


Ray::Ray()
: Ray(math::vec3_zero(), math::vec3_init(0,0,1))
{
}


Ray::Ray(const math::vec3 origin,
         const math::vec3 direction,
         const float distance)
: m_origin(origin)
, m_direction(math::vec3_normalize(direction))
, m_distance(distance)
{
}


math::vec3
Ray::get_direction() const
{
  return m_direction;
}


math::vec3
Ray::get_origin() const
{
  return m_origin;
}


float
Ray::get_distance() const
{
  return m_distance;
}


} // ns