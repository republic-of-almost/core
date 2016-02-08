#include "ray.hpp"
#include <data/data.hpp>


namespace Core {


Ray::Ray(const math::vec3 from, const math::vec3 to, const Search search)
{
  auto phy_world = Data::get_physics_world();
  
  const btVector3 bt_from(math::vec3_get_x(from), math::vec3_get_y(from), math::vec3_get_z(from));
  const btVector3 bt_to(math::vec3_get_x(to), math::vec3_get_y(to), math::vec3_get_z(to));
  
  switch(search)
  {
    case(Search::first):
    {
      btCollisionWorld::ClosestRayResultCallback ray_test(bt_from, bt_to);
      phy_world->dynamics_world.rayTest(bt_from, bt_to, ray_test);
      
      if(ray_test.hasHit())
      {
        const auto hit_obj        = ray_test.m_collisionObject;
        const Core::Entity_id id  = Core::Entity_id_util::convert_ptr_to_entity(hit_obj->getUserPointer());
        const math::vec3 hit_pos  = math::vec3_init(ray_test.m_hitPointWorld.x(), ray_test.m_hitPointWorld.y(), ray_test.m_hitPointWorld.z());
        const math::vec3 normal   = math::vec3_init(ray_test.m_hitNormalWorld.x(), ray_test.m_hitNormalWorld.y(), ray_test.m_hitNormalWorld.z());
        
        m_results.emplace_back(Ray_result{id, hit_pos, normal});
      }
    }
  }
}


Entity
Ray::get_entity(const size_t i) const
{
  Entity return_ent;
  Data::world_find_entity(Data::get_world(), &return_ent, m_results.at(i).id);
  
  return return_ent;
}


} // ns