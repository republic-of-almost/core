#include "entity.hpp"
#include "data.hpp"


namespace Data {


Entity::Entity()
{
}


::Entity::Entity_id
Entity::get_id() const
{
  return m_this_id;
}


bool
Entity::is_valid() const
{
  return !(m_this_id == ::Entity::invalid_id());
}


namespace
{
  inline bool
  get_index(size_t *index, const ::Entity::Entity_id id, const ::Entity::Entity_id ents[], const size_t size)
  {
    if(!ents)
    {
      return false;
    }
    
    if(::Entity::find_index_linearly(index, id, ents, size))
    {
      return true;
    }
    
    return false;
  }
}


void
Entity::set_parent(const ::Entity::Entity_id id)
{
  if(!is_valid()) { return; }

  auto ent_pool = m_world_data->entity_pool;

  size_t index;
  assert(get_index(&index, m_this_id, ent_pool->entity_id, ent_pool->size));
  ent_pool->parent_id[index] = id;
  
  // TODO: Need to check parent is valid?
  Data::entity_graph_change_push(m_world_data->entity_graph_changes, id, Data::Entity_graph_change::moved);
  Data::entity_graph_change_push(m_world_data->entity_graph_changes, m_this_id, Data::Entity_graph_change::updated);
}


Entity
Entity::get_parent() const
{
  if(!is_valid()) { return Entity(); }

  Entity parent;
  Detail::set_entity_members(&parent, m_world_data, m_this_id);
  
  return parent;
}


size_t
Entity::get_number_of_children() const
{
  if(!is_valid()) { return 0; }

  auto ent_pool = m_world_data->entity_pool;

  size_t children_count(0);
  
  for(size_t i = 0; i < ent_pool->size; ++i)
  {
    const ::Entity::Entity_id id = ent_pool->parent_id[i];
  
    if(id == m_this_id)
    {
      ++children_count;
    }
  }
  
  return children_count;
}


Entity
Entity::get_child(const size_t index) const
{
  if(!is_valid()) { return Entity(); }

  auto ent_pool = m_world_data->entity_pool;

  size_t children_count(0);
  
  for(size_t i = 0; i < ent_pool->size; ++i)
  {
    const ::Entity::Entity_id id = ent_pool->parent_id[i];
  
    if(id == m_this_id)
    {
      if(index == children_count)
      {
        Entity child;
        Detail::set_entity_members(&child, m_world_data, m_this_id);
        
        return child;
      }
    
      ++children_count;
    }
  }
  
  return Entity();
}


void
Entity::set_transform(const math::transform &transform)
{
  if(!is_valid()) { return; }

  auto ent_pool = m_world_data->entity_pool;

  size_t index;
  assert(get_index(&index, m_this_id, ent_pool->entity_id, ent_pool->size));
  ent_pool->transform[index] = transform;
  
  Data::entity_graph_change_push(m_world_data->entity_graph_changes, m_this_id, Data::Entity_graph_change::updated);
}


math::transform
Entity::get_transform() const
{
  if(!is_valid()) { return math::transform(); }
  
  auto ent_pool = m_world_data->entity_pool;

  size_t index;
  assert(get_index(&index, m_this_id, ent_pool->entity_id, ent_pool->size));
  return ent_pool->transform[index];
}


void
Entity::set_material_id(const size_t id)
{
  if(!is_valid()) { return; }
  
  auto ent_pool = m_world_data->entity_pool;

  size_t index;
  assert(get_index(&index, m_this_id, ent_pool->entity_id, ent_pool->size));
  ent_pool->texture[index] = (Resource::Texture::ENUM)id;
}


size_t
Entity::get_material_id() const
{
  if(!is_valid()) { return 0; }

  auto ent_pool = m_world_data->entity_pool;

  size_t index;
  assert(get_index(&index, m_this_id, ent_pool->entity_id, ent_pool->size));
  return (size_t)ent_pool->texture[index];
}


void
Entity::set_model_id(const size_t id)
{
  if(!is_valid()) { return; }
  
  auto ent_pool = m_world_data->entity_pool;

  size_t index;
  assert(get_index(&index, m_this_id, ent_pool->entity_id, ent_pool->size));
  ent_pool->model[index] = (Resource::Model::ENUM)id;
}


size_t
Entity::get_model_id() const
{
  if(!is_valid()) { return 0; }
  
  auto ent_pool = m_world_data->entity_pool;

  size_t index;
  assert(get_index(&index, m_this_id, ent_pool->entity_id, ent_pool->size));
  return (size_t)ent_pool->model[index];
}


void
Entity::set_rigidbody_properties(const Physics::Rigidbody_properties props)
{
  if(!is_valid()) { return; }
  
  auto ent_pool = m_world_data->entity_pool;

  size_t index;
  assert(get_index(&index, m_this_id, ent_pool->entity_id, ent_pool->size));
  
  auto rb_prop = &ent_pool->rigidbody_property[index];

  *rb_prop = props;
  rb_prop->id = m_this_id;
  
  Data::entity_graph_change_push(m_world_data->entity_graph_changes, m_this_id, Data::Entity_graph_change::moved);
}


Physics::Rigidbody_properties
Entity::get_rigidbody_properties() const
{
  if(!is_valid()) { return Physics::Rigidbody_properties(); }

  size_t index;
  assert(get_index(&index, m_this_id, m_world_data->entity_pool->entity_id, m_world_data->entity_pool->size));
  return m_world_data->entity_pool->rigidbody_property[index];
}


void
Entity::set_rigidbody_collider(const Physics::Rigidbody_collider collider)
{
  if(!is_valid()) { return; }

  auto ent_pool = m_world_data->entity_pool;

  size_t index;
  assert(get_index(&index, m_this_id, ent_pool->entity_id, ent_pool->size));
  
  auto rb_coll = &ent_pool->rigidbody_collider[index];
  
  *rb_coll = collider;
  
  Data::entity_graph_change_push(m_world_data->entity_graph_changes, m_this_id, Data::Entity_graph_change::moved);
}


Physics::Rigidbody_collider
Entity::get_rigidbody_collider() const
{
  if(!is_valid()) { return Physics::Rigidbody_collider(); }

  auto ent_pool = m_world_data->entity_pool;

  size_t index;
  assert(get_index(&index, m_this_id, ent_pool->entity_id, ent_pool->size));
  return m_world_data->entity_pool->rigidbody_collider[index];
}


} // ns