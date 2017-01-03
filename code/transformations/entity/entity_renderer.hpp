#ifndef ENTITY_RENDERER_INCLUDED_B672FA56_D1B2_444E_BD28_F0ED3138E2F0
#define ENTITY_RENDERER_INCLUDED_B672FA56_D1B2_444E_BD28_F0ED3138E2F0


#include <transformations/entity/entity_common.hpp>


namespace Entity_detail {


uint32_t
has_renderer(const util::generic_id this_id,
             Data::Entity_data *entity_data);


void
set_renderer(const util::generic_id this_id,
             Data::Entity_data *entity_data,
             Data::Transform_data *transform_data,
             Data::Mesh_draw_call_data *mesh_data,
             Data::Text_draw_call_data *text_data,
             const Core::Renderer &renderer);
  
  
Core::Renderer
get_renderer(const util::generic_id this_id,
             Data::Entity_data *entity_data,
             Data::Mesh_draw_call_data *renderer_material,
             Data::Text_draw_call_data *text_draw_call_data);


void
set_renderer_material(const util::generic_id this_id,
                      Data::Entity_data *entity_data,
                      Data::Transform_data *transform_data,
                      Data::Mesh_draw_call_data *mesh_data,
                      const util::generic_id material_id,
                      const util::generic_id model_id);
  

void
get_renderer_material(const util::generic_id this_id,
                      Data::Mesh_draw_call_data *mesh_data,
                      util::generic_id *out_material_id,
                      util::generic_id *out_model_id);

  
void
set_renderer_text(const util::generic_id this_id,
                  const char *string,
                  Data::Entity_data *entity_data,
                  Data::Transform_data *transform_data,
                  Data::Text_draw_call_data *text_data,
                  const util::generic_id font_id,
                  const util::generic_id model_id);


} // ns


#endif // inc guard