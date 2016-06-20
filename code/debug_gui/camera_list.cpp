#include <debug_gui/camera_list.hpp>
#include <3rdparty/imgui/imgui.h>
#include <stdio.h>


namespace Debug_menu {


void
display_camera_data(World_data::Camera_data *data)
{
  ImGui::Begin("Camera List");
  {
    ImGui::Columns(10, "material_cols");
    ImGui::Separator();
    
    ImGui::Text("ID");            ImGui::NextColumn();
    ImGui::Text("Entity ID");     ImGui::NextColumn();
    ImGui::Text("Post Process");  ImGui::NextColumn();
    ImGui::Text("Texture_id");    ImGui::NextColumn();
    ImGui::Text("Priority");      ImGui::NextColumn();
    ImGui::Text("Clear Flags");   ImGui::NextColumn();
    ImGui::Text("FOV");           ImGui::NextColumn();
    ImGui::Text("Mask");          ImGui::NextColumn();
    ImGui::Text("Dimention");     ImGui::NextColumn();
    ImGui::Text("Planes");        ImGui::NextColumn();
    
    ImGui::Separator();
    
    static int selected = -1;
    
    for(uint32_t i = 0; i < data->size; ++i)
    {
      char id[4];
      sprintf(id, "%02d", data->camera_id[i]);
    
      ImGui::Selectable(id, selected == i, ImGuiSelectableFlags_SpanAllColumns);
      ImGui::NextColumn();
      
      ImGui::Text("%d", data->property_entity_id[i]);       ImGui::NextColumn();
      ImGui::Text("%d", data->property_post_process_id[i]); ImGui::NextColumn();
      ImGui::Text("%d", data->property_texture_id[i]);      ImGui::NextColumn();
      
      ImGui::Text("%d", *reinterpret_cast<uint32_t*>(&data->property_priority[i]));
      ImGui::NextColumn();
      
      ::Camera::Camera_properties props;
      World_data::camera_data_get_property_camera(data, data->camera_id[i], &props);

      ImGui::Text("%d",           props.clear_flags);                             ImGui::NextColumn();
      ImGui::Text("%.2f",         props.fov);                                     ImGui::NextColumn();
      ImGui::Text("%d",           props.cull_mask);                               ImGui::NextColumn();
      ImGui::Text("%d x %d",      props.viewport_width, props.viewport_height);   ImGui::NextColumn();
      ImGui::Text("%.2f - %.2f",  props.near_plane, props.far_plane);             ImGui::NextColumn();
  
      
    }
    
    ImGui::Columns(1);
    ImGui::Separator();
  }
  ImGui::End();

}


} // ns