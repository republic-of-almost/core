#ifndef WORLD_INCLUDED_F6D825F0_D062_4B85_A636_7EDE94635488
#define WORLD_INCLUDED_F6D825F0_D062_4B85_A636_7EDE94635488


#include "world_setup.hpp"
#include "entity.hpp"
#include "entity_ref.hpp"
#include <stdint.h>
#include <data/core_data/core_data.hpp>
#include <data/world_data/world_data.hpp>


namespace Core {


class World
{
public:

  explicit              World(const World_setup &setup);

  Entity                create_entity();
  Entity_ref            find_entity(const char *name);
  
private:

  Core_data::Core       m_core_data;
  World_data::World     m_world_data;

};


} // ns


#endif // inc guard