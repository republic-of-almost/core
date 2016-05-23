#include <debug_gui/entity_list.hpp>
#include <data/world_data/entity_data.hpp>
#include <3rdparty/imgui/imgui.h>
#include <string>


namespace Debug_menu {


void
display_entity_list(World_data::Entity_data *data)
{
  ImGui::Begin("Entities");
  {
    for(uint32_t i = 0; i < data->size; ++i)
    {
      ImGui::Text(World_data::entity_data_get_name(data, data->entity_id[i]));
      ImGui::Text(std::to_string(data->tags[i]).c_str());
      ImGui::Text(std::to_string(data->user_data[i]).c_str());
      
      ImGui::Separator();
    }
  }
  ImGui::End();
 
}


} // ns