#include <transformations/entity/entity_transform.hpp>
#include <transformations/entity/entity_common.hpp>
#include <transformations/entity/entity_rigidbody.hpp>
#include <core/transform/transform.hpp>
#include <data/world_data/world_pools.hpp>
#include <data/world_data/renderer_mesh_data.hpp>
#include <data/world_data/renderer_text_draw_calls_data.hpp>
#include <data/world_data/transform_data.hpp>
#include <common/error_strings.hpp>
#include <utilities/logging.hpp>
#include <assert.h>


namespace Entity_detail {


namespace {

inline void
update_transform(const util::generic_id this_id,
                 World_data::World *world,
                 const math::transform *transform)
{
  auto transform_data = world->transform;
  
  World_data::data_lock(transform_data);

  size_t index;
  if(World_data::transform_data_exists(transform_data, this_id, &index))
  {
    transform_data->property_transform[index] = *transform;
  }
  
  World_data::data_unlock(transform_data);
}


inline void
update_mesh_renderer(const util::generic_id this_id,
                     World_data::World *world,
                     const math::transform *transform)
{

  auto mesh_data = world->mesh_data;

  // Update mesh renderer data
  {
    World_data::data_lock(mesh_data);
  
    size_t mesh_index;

    if(World_data::renderer_mesh_data_exists(mesh_data, this_id, &mesh_index))
    {
      const math::mat4 world_mat = math::transform_get_world_matrix(*transform);
      memcpy(mesh_data->property_draw_call[mesh_index].world_matrix, &world_mat, sizeof(world_mat));
    }
    
    World_data::data_unlock(mesh_data);
  }
}


inline void
udpate_text_renderer(const util::generic_id this_id,
                     World_data::World *world,
                     const math::transform *transform)
{

  auto text_data = world->text_data;

  // Update mesh renderer data
  {
    World_data::data_lock(text_data);
  
    size_t index;

    if(World_data::renderer_text_draw_calls_data_exists(text_data, this_id, &index))
    {
      const math::mat4 world_mat = math::transform_get_world_matrix(*transform);
      memcpy(text_data->property_draw_call[index].world_matrix, &world_mat, sizeof(world_mat));
    }
    
    World_data::data_unlock(text_data);
  }
}


} // anon ns


void
set_transform(const util::generic_id this_id,
              World_data::World *world,
              const Core::Transform &set_transform,
              bool inform_phys_engine)
{
  // Check valid
  if(!is_valid(this_id, world, true)) {
    assert(false); return;
  }
  
  // Get aabb
  math::aabb curr_aabb;
  {
    auto transform_data = world->transform;
    assert(transform_data);
  
    World_data::data_lock(transform_data);
    World_data::transform_data_get_property_aabb(world->transform, this_id, &curr_aabb);
    World_data::data_unlock(world->transform);
  }
  
  // Update all the things that want to know.
  {
    // Build new transform
    const math::transform new_transform = math::transform_init(set_transform.get_position(),
                                                               set_transform.get_scale(),
                                                               set_transform.get_rotation());
    
    update_transform(this_id, world, &new_transform);
    update_collider(this_id, world, &new_transform, &curr_aabb, inform_phys_engine);
    update_mesh_renderer(this_id, world, &new_transform);
    udpate_text_renderer(this_id, world, &new_transform);
  }
}


Core::Transform
get_core_transform(const util::generic_id this_id,
              World_data::World *world)
{
  // Check valid
  if(!is_valid(this_id, world, true)) {
    assert(false); return Core::Transform();
  }
  
  const math::transform transform_prop = get_transform(this_id, world);
  
  return Core::Transform(transform_prop.position, transform_prop.scale, transform_prop.rotation);
}


math::transform
get_transform(const util::generic_id this_id,
              World_data::World *world)
{
  // Check valid
  if(!is_valid(this_id, world, true)) {
    assert(false); return math::transform();
  }
  
  // Get Data
  math::transform return_transform;
  {
    auto transform_data = world->transform;
    assert(transform_data);
    
    World_data::data_lock(transform_data);

    if(!World_data::transform_data_get_property_transform(transform_data,
                                                          this_id,
                                                          &return_transform))
    {
      assert(false);
      LOG_WARNING(Error_string::data_not_found());
    }
    
    World_data::data_unlock(transform_data);
  }
  
  return return_transform;
}





} // ns