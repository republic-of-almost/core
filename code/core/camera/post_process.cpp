#include <core/camera/post_process.hpp>
#include <core/resources/shader.hpp>
#include <core/resources/texture.hpp>
#include <core/resources/render_target.hpp>
#include <data/context/post_process_data.hpp>
#include <data/context/shader_data.hpp>
#include <data/context/texture_data.hpp>
#include <data/context_data.hpp>
#include <common/error_strings.hpp>
#include <common/fixed_string_search.hpp>
#include <utilities/logging.hpp>


namespace Core {


struct Post_process::Impl
{
  uint32_t id;
};


Post_process::Post_process(const char *name)
: m_impl(new Impl{})
{
  // Search to see if it exists, else add a new one.
  auto post_data = Data::get_context_data()->post_process_data;
  
  uint32_t search_id = 0;
  Data::data_lock(post_data);
  
  if(Common::fixed_string_search(name,
                                 Data::post_process_get_name_data(post_data),
                                 Data::post_process_get_name_stride(),
                                 Data::post_process_get_size(post_data)),
                                 &search_id)
  {
    m_impl->id = search_id;
  }
  else
  {
    // Add a new record.
    m_impl->id = Data::post_process_push(post_data);
  
    if(m_impl->id)
    {
      Data::post_process_set_name(post_data, m_impl->id, name, strlen(name));
    }
    else
    {
      assert(false);
      LOG_ERROR(Error_string::no_free_space());
    }
  }
  
  Data::data_unlock(post_data);
}


Post_process::Post_process(Post_process &&other)
: m_impl(new Impl(*other.m_impl.get()))
{
}


Post_process::~Post_process()
{
}


void
Post_process::set_shader(const Core::Shader &core_shader)
{

  auto post_data = Data::get_context_data()->post_process_data;
  auto shd_data = Data::get_context_data()->shader_data;
  
  // Update
  { 
    Data::data_lock(shd_data);
    Data::data_lock(post_data);
    
    Ogl::Shader shader;
    Data::shader_get_shader(shd_data, core_shader.get_id(), &shader);
    
    Post_renderer::Post_shader post_shd;
    Data::post_process_get_post_shader(post_data, m_impl->id, &post_shd);
    
    Post_renderer::create_post_shader(&post_shd, &shader);
    
    Data::data_unlock(shd_data);
    Data::data_unlock(post_data);
  }
}


void
Post_process::set_input_01(const Texture &core_texture)
{
  auto post_data = Data::get_context_data()->post_process_data;
  auto tex_data = Data::get_context_data()->texture_data;
  
  {
    Data::data_lock(post_data);
    Data::data_lock(tex_data);
    
    Post_renderer::Post_shader post_shd;
    Data::post_process_get_post_shader(post_data, m_impl->id, &post_shd);
    
    Ogl::Texture texture;
    Data::texture_get_texture(tex_data, core_texture.get_id(), &texture);
    post_shd.map_01_id = texture;
    
    Data::data_unlock(tex_data);
    Data::data_unlock(post_data);
  }
}


void
Post_process::set_input_02(const Texture &core_texture)
{
  auto post_data = Data::get_context_data()->post_process_data;
  auto tex_data = Data::get_context_data()->texture_data;
  
  {
    Data::data_lock(post_data);
    Data::data_lock(tex_data);
    
    Post_renderer::Post_shader post_shd;
    Data::post_process_get_post_shader(post_data, m_impl->id, &post_shd);
    
    Ogl::Texture texture;
    Data::texture_get_texture(tex_data, core_texture.get_id(), &texture);
    post_shd.map_02_id = texture;
    
    Data::data_unlock(tex_data);
    Data::data_unlock(post_data);
  }
}


void
Post_process::set_input_03(const Texture &core_texture)
{
  auto post_data = Data::get_context_data()->post_process_data;
  auto tex_data = Data::get_context_data()->texture_data;
  
  {
    Data::data_lock(post_data);
    Data::data_lock(tex_data);
    
    Post_renderer::Post_shader post_shd;
    Data::post_process_get_post_shader(post_data, m_impl->id, &post_shd);
    
    Ogl::Texture texture;
    Data::texture_get_texture(tex_data, core_texture.get_id(), &texture);
    post_shd.map_03_id = texture;
    
    Data::data_unlock(tex_data);
    Data::data_unlock(post_data);
  }
}


uint32_t
Post_process::get_id() const
{
  return m_impl->id;
}


} // ns
