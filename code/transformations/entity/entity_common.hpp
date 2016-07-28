#ifndef ENTITY_COMMON_INCLUDED_861E3180_911C_4588_AA68_98BD4F51CD3E
#define ENTITY_COMMON_INCLUDED_861E3180_911C_4588_AA68_98BD4F51CD3E


#include <utilities/generic_id.hpp>
#include <core/common/core_fwd.hpp>
#include <data/world_data/world_data_fwd.hpp>
#include <stdint.h>


namespace Entity_detail {


util::generic_id
get_id(const util::generic_id this_id,
       World_data::World *world);


bool
is_valid(const util::generic_id this_id,
         World_data::World *world,
         const bool emit_error = false);


void
destroy(const util::generic_id this_id,
        World_data::World *world);


void
update_component(const util::generic_id this_id,
                 World_data::World *data,
                 const uint32_t component_id);


} // ns


#endif // inc guard