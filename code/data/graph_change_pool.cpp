#include "graph_change_pool.hpp"
#include <assert.h>
#include <cstring>


namespace Data {


void
entity_graph_change_pool_init(Entity_graph_changes_pool *pool)
{
  memset(pool->entity_event, 0, sizeof(pool->entity_event));
  pool->size = 0;
}


void
entity_graph_change_push(Entity_graph_changes_pool *pool, const Core::Entity_id entity_id, Entity_graph_change change_type)
{
  assert(pool && pool->size < pool->capacity);
  
  pool->entity_event[pool->size].entity_id = entity_id;
  pool->entity_event[pool->size].change_type = change_type;
  
  ++(pool->size);
}


} // ns