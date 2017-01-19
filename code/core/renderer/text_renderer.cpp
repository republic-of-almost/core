#include <core/renderer/text_renderer.hpp>
#include <core/renderer/renderer.hpp>
#include <core/font/font.hpp>
#include <common/fixed_string_search.hpp>
#include <data/context/text_mesh_data.hpp>
#include <data/context_data.hpp>
#include <systems/text/character.hpp>

#include <graphics_api/utils/geometry.hpp>
#include <graphics_api/mesh.hpp>
#include <graphics_api/vertex_format.hpp>

#include <transformations/text/rasterized_glyph_id.hpp>


namespace Core {


struct Text_renderer::Impl
{
  std::string m_text;
};


Text_renderer::Text_renderer()
: Text_renderer(util::generic_id_invalid(),
                util::generic_id_invalid())
{
}


Text_renderer::Text_renderer(const util::generic_id font_id,
                             const util::generic_id text_id)
: m_impl(new Impl)
, m_font_id(font_id)
, m_text_id(text_id)
{
  LOG_TODO("Check these ids are valid.");
}


Text_renderer::~Text_renderer()
{
  delete m_impl;
}


void
Text_renderer::set_font(const Font &font)
{
  m_font_id = font.get_id();
  
  // Set the font id for this item,
  // but only if it exists.
  if(m_text_id)
  {
    auto resources = Data::get_context_data();
    assert(resources);
    
    auto text_mesh_data = resources->text_mesh_data;
    assert(text_mesh_data);
  
    Data::data_lock(text_mesh_data);
    Data::text_mesh_set_font_id(text_mesh_data, m_text_id, &m_font_id);
    Data::data_unlock(text_mesh_data);
  }
}


Font
Text_renderer::get_font() const
{
  assert(false);
  return Font("");
}


void
Text_renderer::set_text(const char *str)
{
  assert(m_impl);
  m_impl->m_text = std::string(str);
}


const char*
Text_renderer::get_text() const
{
  assert(m_impl);
  return m_impl->m_text.c_str();
}


void
Text_renderer::set_text_size(const uint32_t size)
{
  assert(false);
}


uint32_t
Text_renderer::get_text_size() const
{
  assert(false);
  return 0;
}


Text_renderer::operator Renderer() const
{
  return Renderer(Core::Renderer_type::text, m_font_id, m_text_id);
}


util::generic_id
Text_renderer::get_font_id() const
{
  return m_font_id;
}


util::generic_id
Text_renderer::get_text_id() const
{
  return m_text_id;
}


} // ns