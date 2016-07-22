#include "world_pools.hpp"
#include "renderer_mesh_data.hpp"
#include "physics_data.hpp"
#include "pending_scene_graph_change_data.hpp"
#include "camera_data.hpp"
#include "renderer_mesh_data.hpp"
#include "renderer_text_draw_calls_data.hpp"
#include "entity_data.hpp"
#include "transform_data.hpp"
#include <core/entity/entity.hpp>
#include <core/entity/entity_ref.hpp>
#include <utilities/logging.hpp>
#include <atomic>


namespace World_data {


World::World(const uint32_t entity_hint)
{
  Pending_scene_graph_change_data *graph_changes = new Pending_scene_graph_change_data();
  pending_scene_graph_change_init(graph_changes, entity_hint);
  
  Camera_data *camera_data = new Camera_data;
  camera_data_init(camera_data, 32);
    
  Physics_data* physics_data = new Physics_data;
  physics_data_init(physics_data, entity_hint);
  
  Renderer_mesh_data *mesh_data = new Renderer_mesh_data;
  renderer_mesh_data_init(mesh_data, entity_hint);
  
  Transform_data *transform_data = new Transform_data;
  World_data::transform_data_init(transform_data, entity_hint);
  
  Entity_data *entity_data = new Entity_data;
  World_data::entity_data_init(entity_data, entity_hint);
  
  Renderer_text_draw_calls_data *text_draw_calls = new Renderer_text_draw_calls_data;
  renderer_text_draw_calls_data_init(text_draw_calls, entity_hint);
  
  this->entity_graph_changes = graph_changes;
  this->physics_data         = physics_data;
  this->mesh_data            = mesh_data;
  this->camera_data          = camera_data;
  this->transform            = transform_data;
  this->entity               = entity_data;
  this->text_data            = text_draw_calls;
}

World::~World()
{
  delete this->entity_graph_changes;
  delete this->physics_data;
  delete this->mesh_data;
  delete this->camera_data;
  delete this->transform;
  delete this->entity;
  delete this->text_data;
}


void
world_find_entities_with_tag(World *world_data,
                             const uint32_t tag,
                             uint32_t *out_entities_for_tag,
                             util::generic_id out_ids[],
                             const uint32_t size_of_out)
{
  assert(world_data);
  
  auto entity_data = world_data->entity;
  
  uint32_t number_found(0);
  
  for(uint32_t i = 0; i < entity_data->size; ++i)
  {
    auto tags = entity_data->property_tag[i];
    
    if(tags & tag)
    {
      if(size_of_out > number_found)
      {
        out_ids[number_found++] = entity_data->entity_id[i];
      }
      else
      {
        break;
      }
    }
  }
  
  (*out_entities_for_tag) = number_found;
}


void
world_update_scene_graph_changes(World_data::World *world_data,
                                 const Pending_scene_graph_change_data *graph_changes)
{
  for(uint32_t i = 0; i < graph_changes->delete_size; ++i)
  {
    const util::generic_id id = graph_changes->entities_to_delete[i];
    
    entity_data_erase(world_data->entity, id);
    transform_data_erase(world_data->transform, id);
    renderer_mesh_data_erase(world_data->mesh_data, id);
    physics_data_erase(world_data->physics_data, id);
  }
}


} // ns