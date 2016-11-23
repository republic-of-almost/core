#include <transformations/entity/entity_light.hpp>
#include <transformations/lighting/light_data.hpp>
#include <common/data_types.hpp>
#include <math/transform/transform.hpp>
#include <core/color/color_utils.hpp>
#include <core/lighting/point_light.hpp>
#include <data/world/transform_data.hpp>
#include <data/world/entity_data.hpp>
#include <data/world/light_data.hpp>
#include <utilities/logging.hpp>


namespace Entity_detail {


void
set_light(const util::generic_id this_id,
          Data::Entity_data *entity_data,
          Data::Light_data *light_data,
          const Data::Transform_data *transform_data,
          const Core::Point_light *light)
{
  // Param Check
  assert(this_id);
  assert(entity_data);
  assert(light_data);
  assert(transform_data);
  assert(light);
  
  // Add Light Component to entity
  bool entity_exists = false;
  {
    Data::data_lock(entity_data);
    
    if(Data::entity_exists(entity_data, this_id))
    {
      entity_exists = true;
    }
    
    
    if(entity_exists)
    {
      uint32_t components = 0;
      Data::entity_get_components(entity_data, this_id, &components);
      
      components |= Common::Data_type::light;
      Data::entity_set_components(entity_data, this_id, &components);
    }
    
    Data::data_unlock(entity_data);
  }
  
  // Bail if entity doesn't exist.
  {
    if(!entity_exists)
    {
      LOG_ERROR("Failed to add light");
      return;
    }
  }

  // Get the transform for this entity
  math::transform transform;
  {
    Data::data_lock(transform_data);
    Data::transform_get_transform(transform_data, this_id, &transform);
    Data::data_unlock(transform_data);
  }
  
  // Add Light to data
  {
    Data::data_lock(light_data);
    
    // Add a new record if none exists.
    if(!Data::light_exists(light_data, this_id))
    {
      Data::light_push(light_data, this_id);
    }
    
    Lighting::Light l_data;
    l_data.position[0]    = math::get_x(transform.position);
    l_data.position[1]    = math::get_y(transform.position);
    l_data.position[2]    = math::get_z(transform.position);
    l_data.color[0]       = Core::Color_utils::get_red_f(light->get_color());
    l_data.color[1]       = Core::Color_utils::get_green_f(light->get_color());
    l_data.color[2]       = Core::Color_utils::get_blue_f(light->get_color());
    l_data.ambient        = light->get_ambient();
    l_data.diffuse        = light->get_diffuse();
    l_data.specular       = light->get_specular();
    l_data.atten_constant = light->get_constant_attenuation();
    l_data.atten_linear   = light->get_linear_attenuation();
    l_data.atten_exp      = light->get_exponential_attenuation();
    
    Data::light_set_light(light_data, this_id, &l_data);
    
    // TODO: Set AABB
    
    Data::data_unlock(light_data);
  }
}


void
set_light_transform(const util::generic_id this_id,
                    const Data::Entity_data *entity_data,
                    const Data::Transform_data *transform_data,
                    Data::Light_data *light_data)
{
}


} // ns