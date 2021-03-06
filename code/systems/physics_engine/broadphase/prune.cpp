#include "prune.hpp"
#include "sweep.hpp"
#include <math/general/general.hpp>
#include <assert.h>

#define CORE_USE_SCRATCH_ALLOC

#ifdef CORE_USE_SCRATCH_ALLOC
#include <data/memory/memory_data.hpp>
#include <new>
#endif


namespace Physics {
namespace Broadphase {


void
prune_init(Prune *prune, const Sweep *sweep)
{
  assert(prune);

  const uint32_t capacity = sweep->size * 3;
  prune->capacity = capacity;
  prune->size = 0;

  #ifdef CORE_USE_SCRATCH_ALLOC
  const size_t bytes = sizeof(uint32_t) * capacity;
   
  prune->ids = new(Memory::scratch_alloc(bytes)) uint32_t[capacity];
  #else
  prune->ids = new uint32_t[capacity];
  #endif
}


void
prune_calculate(Prune *prune, const Sweep *sweep)
{
  // Loop through each item and check if it collides with something on that axis.
  uint32_t obj_id = 0;
  bool potential_collision = false;

  while(obj_id < sweep->size)
  {
    const Sweep_axis *test_obj_x = &sweep->x_axis[obj_id];
    const Sweep_axis *test_obj_y = &sweep->y_axis[obj_id];
    const Sweep_axis *test_obj_z = &sweep->z_axis[obj_id];

    uint32_t sweep_id = 0;
    potential_collision = false;

    while(sweep_id < sweep->size)
    {
      // Don't self test
      if(sweep_id == obj_id)
      {
        ++sweep_id;
        continue;
      }
      
      // Stagger the tests to reduce CPU cost

      // Test if this object is overlapping
      const Sweep_axis *sweep_obj_x = &sweep->x_axis[sweep_id];
      const float c1_x = math::min(test_obj_x->center, sweep_obj_x->center);
      const float c2_x = math::max(test_obj_x->center, sweep_obj_x->center);
      const float distance_x = math::abs(c2_x - c1_x);
      const float combined_extent_x = test_obj_x->half_extent + sweep_obj_x->half_extent;
      
      if(distance_x < combined_extent_x)
      {
        const Sweep_axis *sweep_obj_y = &sweep->y_axis[sweep_id];
        const float c1_y = math::min(test_obj_y->center, sweep_obj_y->center);
        const float c2_y = math::max(test_obj_y->center, sweep_obj_y->center);
        const float distance_y = math::abs(c2_y - c1_y);
        const float combined_extent_y = test_obj_y->half_extent + sweep_obj_y->half_extent;
        
        if(distance_y < combined_extent_y)
        {
          const Sweep_axis *sweep_obj_z = &sweep->z_axis[sweep_id];
          const float c1_z = math::min(test_obj_z->center, sweep_obj_z->center);
          const float c2_z = math::max(test_obj_z->center, sweep_obj_z->center);
          const float distance_z = math::abs(c2_z - c1_z);
          const float combined_extent_z = test_obj_z->half_extent + sweep_obj_z->half_extent;
          
          if(distance_z < combined_extent_z)
          {
            // No point testing this object
            // anymore we know its potentially
            // colliding.
            
            potential_collision = true;
            break;
          }
        }
      }

      ++sweep_id;
    }

    // This can be pruned out.
    if(!potential_collision)
    {
      assert(prune->size < prune->capacity);
      prune->ids[prune->size] = obj_id;
      ++(prune->size);
    }
    
    ++obj_id;
  }

  // Now we have a list of objects that are not colliding
  // we might possibly have duplicates so lets remove those.
  {
    uint32_t prune_index = 0;

    while(prune_index < prune->size)
    {
      const uint32_t id_to_search = prune->ids[prune_index];

      uint32_t search_index = 0;
      while(search_index < prune->size)
      {
        // Don't self check
        if(prune_index == search_index)
        {
          ++search_index;
          continue;
        }

        const uint32_t curr_id = prune->ids[search_index];

        if(curr_id == id_to_search)
        {
          const uint32_t start_move = search_index + 1;
          const uint32_t end_move   = prune->size - 1 - search_index;
        
          memmove(&prune->ids[search_index],
                  &prune->ids[start_move],
                  end_move * sizeof(prune->ids[0]));
        
          // Remove duplicate id.
          --(prune->size);
          
          continue;
        }
        else
        {
          ++search_index;
        }
      }

      ++prune_index;
    } // remove duplicate ids
  }
}


void
prune_free(Prune *prune)
{
  assert(prune);
  
  #ifndef CORE_USE_SCRATCH_ALLOC
  delete[] prune->ids;
  #endif
}


} // ns
} // ns
