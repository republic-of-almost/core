#include "physics_tick.hpp"

#include <transformations/entity/entity_transform.hpp>

#include <renderer/debug_line_renderer/debug_line_renderer_node.hpp>
#include <renderer/debug_line_renderer/debug_line_renderer.hpp>
#include <transformations/physics/bullet/bullet_math_extensions.hpp>

#include <BulletCollision/CollisionDispatch/btGhostObject.h>

// Don't want core here!
#include <core/common/collision.hpp>
#include <core/transform/transform.hpp>
#include <core/entity/detail/entity_id.hpp>
#include <core/entity/entity_components.hpp>
#include <core/physics/collision.hpp>

#include <data/world_data.hpp>
#include <data/world/rigidbody_data.hpp>


namespace {

//struct Debug_renderer : public q3Render
//{
//  math::vec3 pen_pos = math::vec3_zero();
//  math::vec3 pen_color = math::vec3_zero();
//  math::vec3 scale = math::vec3_one();
//
//  void SetPenColor( f32 r, f32 g, f32 b, f32 a = 1.0f ) override
//  {
//    pen_color = math::vec3_init(r, g, b);
//  }
//  
//  
//	void SetPenPosition( f32 x, f32 y, f32 z ) override
//  {
//    pen_pos = math::vec3_from_q3vec(q3Vec3(x, y, z));
//  }
//  
//  
//	void SetScale( f32 sx, f32 sy, f32 sz ) override
//  {
//    scale = math::vec3_init(sx, sy, sz);
//  }
//
//	// Render a line from pen position to this point.
//	// Sets the pen position to the new point.
//	void Line( f32 x, f32 y, f32 z ) override
//  {
//    math::vec3 pos = math::vec3_from_q3vec(q3Vec3(x, y, z));
//  
//    Debug_line_renderer::Line_node node;
//    node.color[0] = math::get_x(pen_color);
//    node.color[1] = math::get_y(pen_color);
//    node.color[2] = math::get_z(pen_color);
//    
//    node.position_from[0] = math::get_x(pen_pos);
//    node.position_from[1] = math::get_y(pen_pos);
//    node.position_from[2] = math::get_z(pen_pos);
//    
//    node.position_to[0] = math::get_x(pos);
//    node.position_to[1] = math::get_y(pos);
//    node.position_to[2] = math::get_z(pos);
//    
//    Debug_line_renderer::add_lines(&node, 1);
//  }
//  
//
//	void SetTriNormal( f32 x, f32 y, f32 z ) override {}
//
//	// Render a triangle with the normal set by SetTriNormal.
//	void Triangle(
//		f32 x1, f32 y1, f32 z1,
//		f32 x2, f32 y2, f32 z2,
//		f32 x3, f32 y3, f32 z3
//		) override
//  {
//    const math::vec3 old_pos = pen_pos;
//  
//    pen_pos = math::vec3_init(x3, y3, z3);
//    Line(x1, y1, z1);
//    
//    pen_pos = math::vec3_init(x1, y1, z1);
//    Line(x2, y2, z2);
//    
//    pen_pos = math::vec3_init(x2, y2, z2);
//    Line(x3, y3, z3);
//    
//    pen_pos = old_pos;
//  }
//
//	// Draw a point with the scale from SetScale
//	void Point( ) override {}
//} debug_renderer;

  // This state needs to go because its accross worlds
  Core::Collision_callback callback_hack;
  
  btPairCachingGhostObject *ghostObject;
  btManifoldArray manifoldArray;
  
  void ghost_callback(btDynamicsWorld *world, btScalar timeStep)
  {
    manifoldArray.clear();
    
    auto pair_cache = ghostObject->getOverlappingPairCache();
    auto num_pairs  = pair_cache->getNumOverlappingPairs();
    
    for(decltype(num_pairs) i = 0; i < num_pairs; ++i)
    {
      
    }
    
  
  
    for(int i = 0; i < ghostObject->getNumOverlappingObjects(); i++)
    {
      btRigidBody *pRigidBody = static_cast<btRigidBody *>(ghostObject->getOverlappingObject(i));
      
      uintptr_t user_data = (uintptr_t)pRigidBody->getCollisionShape()->getUserPointer();
      
      Core::Entity_ref entity_ref(Core_detail::entity_id_from_uint(user_data));
      const char *name = entity_ref.get_name();
      
      printf("name: %s", name);
    }
  }

} // anon ns


namespace Engine {
namespace Physics_tick {


void
initialize(std::shared_ptr<Data::World> world)
{
  ghostObject = new btGhostObject();
  ghostObject->setCollisionShape(new btBoxShape(btVector3(btScalar(50.),btScalar(50.),btScalar(50.))));
  
  btTransform transform;
  transform.setIdentity();
  
  ghostObject->setWorldTransform(transform);
  
  world->dynamicsWorld->addCollisionObject(ghostObject);
  world->dynamicsWorld->getBroadphase()->getOverlappingPairCache()->setInternalGhostPairCallback(new btGhostPairCallback());
  
  world->dynamicsWorld->setInternalTickCallback(ghost_callback, 0, true);
}


void
collision_callback(Core::Collision_callback callback)
{
  callback_hack = callback;
};


void
think(std::shared_ptr<Data::World> world, const float dt, Tick_information *out_tick_info)
{
  /*
    Collisions
    --
    Don't like the use of Core:: here.
    Where possible we should dump the information into an array, and let core apply
    the transformation to the data to generate Core::Collisions.
    
    Also don't like the callback here. World think should check if any collisions then fire its own callback.
  */
  {
    Core::Collision_pair *collisions_arr = nullptr;
    uint32_t number_of_collisions = 0;
    {
      world->dynamicsWorld->stepSimulation(1 / 60.f, 10);
    }
    
    if(number_of_collisions && callback_hack)
    {
      for(uint32_t i = 0; i < number_of_collisions; ++i)
      {
        callback_hack(Core::Collision_type::enter, collisions_arr[i]);
      }
    }
    
    // Set transforms.
    Data::Rigidbody_data *rb_data = world->rigidbody_data;
    
    for(size_t i = 0; i < Data::rigidbody_get_size(rb_data); ++i)
    {
      const uintptr_t rb_ptr = Data::rigidbody_get_rigidbody_data(rb_data)[i];
      
      if(rb_ptr)
      {
//        const q3Transform trans(reinterpret_cast<q3Body*>(rb_ptr)->GetTransform());
        btTransform trans;
        reinterpret_cast<btRigidBody*>(rb_ptr)->getMotionState()->getWorldTransform(trans);
        
        Core::Transform core_trans = math::transform_from_bt(trans);

        const uint32_t entity_id(rb_data->keys[i]);
        const Core::Entity_ref ref(Core_detail::entity_id_from_uint(entity_id));
        
        const Core::Transform old_trans(Core::Entity_component::get_transform(ref));
        
//        Core::Transform new_trans(to_core_trans(trans));
        core_trans.set_scale(old_trans.get_scale());

        
        Entity_detail::set_transform(entity_id,
                                     world->entity,
                                     world->transform,
                                     world->rigidbody_data,
                                     world->mesh_data,
                                     world->text_data,
                                     core_trans,
                                     false);
      }
    }
  }
}


void
de_initialize()
{
}


} // ns
} // ns