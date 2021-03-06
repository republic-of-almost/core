#ifndef ENGINE_INCLUDED_028C7BEE_E9AA_408E_AEA1_55EF0DDB370F
#define ENGINE_INCLUDED_028C7BEE_E9AA_408E_AEA1_55EF0DDB370F


#include "tick_information.hpp"
#include <data/fwd_dec_collections.hpp>

#include <core/world/world.hpp> // Kill

namespace Engine {


void
initialize(std::shared_ptr<Data::World> world);


void
think(const std::shared_ptr<Data::World> world_data,
      const std::shared_ptr<Data::Context> resource_data,
      const float dt,
      const float running_time,
      const uint32_t width,
      const uint32_t height,
      Tick_information *out_tick_info = nullptr);


/*
  Temp hack till core can access the collision data specifically.
*/
void
set_collision_callback(Core::Collision_callback callback);


void
de_initialize();


} // ns


#endif // inc guard