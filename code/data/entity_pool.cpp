#include "entity_pool.hpp"


namespace Data {


void
entity_pool_init(Entity_pool *pool)
{
  memset(pool->entity_id, 0, sizeof(pool->entity_id));
  memset(pool->model, 0, sizeof(pool->model));
  memset(pool->texture, 0, sizeof(pool->texture));
  memset(pool->transform, 0, sizeof(pool->transform));
  memset(pool->rigidbody, 0, sizeof(pool->rigidbody));
  memset(pool->rigidbody_property, 0, sizeof(pool->rigidbody_property));
}


} // ns