#ifndef ENTITY_RENDERER_INCLUDED_B672FA56_D1B2_444E_BD28_F0ED3138E2F0
#define ENTITY_RENDERER_INCLUDED_B672FA56_D1B2_444E_BD28_F0ED3138E2F0


#include <transformations/entity/entity_common.hpp>


namespace Entity_detail {


void
set_renderer(const util::generic_id this_id,
             World_data::World *world,
             const Core::Renderer &renderer);
  
  
Core::Renderer
get_renderer(const util::generic_id this_id,
             World_data::World *world);


void
set_renderer_material(const util::generic_id this_id,
                      World_data::World *world,
                      const util::generic_id material_id,
                      const util::generic_id model_id);
  

void
get_renderer_material(const util::generic_id this_id,
                      World_data::World *world,
                      util::generic_id *out_material_id,
                      util::generic_id *out_model_id);

  
void
set_renderer_text(const util::generic_id this_id,
                  World_data::World *world,
                  const util::generic_id font_id,
                  const util::generic_id model_id);


} // ns


#endif // inc guard