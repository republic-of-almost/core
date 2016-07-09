#include <core/renderer/text_renderer.hpp>
#include <core/renderer/renderer.hpp>
#include <core/font/font.hpp>
#include <data/global_data/text_mesh_data.hpp>
#include <data/global_data/resource_data.hpp>


namespace Core {


Text_renderer::Text_renderer()
{
}


void
Text_renderer::set_font(const Font &font)
{
}


Font
Text_renderer::get_font() const
{
  return Font("");
}


void
Text_renderer::set_text(const char *str)
{
  // Generate the underlying resource
  {
    auto resources = Resource_data::get_resources();
    assert(resources);
    
    auto text_mesh = resources->text_mesh_data;
    assert(text_mesh);
    
    Resource_data::data_lock(text_mesh);
    
    LOG_TODO_ONCE("Dont create a mesh every time, check to see if it exists first");
    
    const util::generic_id id = Resource_data::text_mesh_data_push_back(text_mesh);
    Resource_data::text_mesh_data_set_property_text(text_mesh, id, str);
    
    Resource_data::data_unlock(text_mesh);
  }
}


const char*
Text_renderer::get_text() const
{
  return "";
}


Text_renderer::operator Renderer() const
{
  return Renderer(Core::Renderer_type::text, m_font_id, m_text_id);
}


} // ns