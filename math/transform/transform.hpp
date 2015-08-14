#ifndef TRANSFORM_INCLUDED_E79342EA_D69A_4FEB_BEAD_BA21D7B8B8E6
#define TRANSFORM_INCLUDED_E79342EA_D69A_4FEB_BEAD_BA21D7B8B8E6


/*
  Transform
  --
  Transform is a position and rotation in 3D space.
*/


#include "../transform/transform_types.hpp"
#include "../quat/quat.hpp"
#include "../vec/vec3.hpp"
#include "../mat/mat4.hpp"


namespace math {


// ** Interface ** //

inline transform  transform_init(const vec3 position, const vec3 scale, const quat &rotation);
inline mat4       transform_get_world_matrix(const transform &transform);
inline void       transform_set_with_world_matrix(transform &transform, const mat4 &matrix);
inline transform  transform_inherited(const transform &parent, const transform &child);


// ** Impl ** //


transform
transform_init(const vec3 position, const vec3 scale, const quat &rotation)
{
  transform return_transform;
  return_transform.position = position;
  return_transform.scale    = scale;
  return_transform.rotation = rotation;

  return return_transform;
}


transform
transform_inherited(const transform &parent, const transform &child)
{
  transform inherited;

  inherited.scale    = math::vec3_multiply(parent.scale, child.scale);
  inherited.position = math::vec3_subtract(parent.position, child.position);

  // TODO: Rotation.

  return inherited;
}


mat4
transform_get_world_matrix(const transform &to_world)
{
  // Get scale
  const mat4 scale = mat4_scale(to_world.scale);
  
  // Get rotation
  mat4 rotation = mat4_init_with_mat3(quat_get_rotation_matrix(to_world.rotation));
  mat4_set(rotation, 3, 3, 1.f);
  
  // Get translation
  const mat4 translation = mat4_translate(to_world.position);
  
  return mat4_multiply(scale, rotation, translation);
}


} // namespace


#endif // include guard