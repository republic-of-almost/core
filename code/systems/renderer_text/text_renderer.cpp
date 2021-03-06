#include "text_renderer.hpp"
#include <op/op.hpp>
#include <math/mat/mat4.hpp>
#include <utilities/file.hpp>
#include <utilities/string.hpp>
#include <utilities/directory.hpp>
#include <utilities/platform.hpp>
#include <data/common/directories.hpp>


namespace
{
  opID text_shader;
  opID text_shader_wvp;
  opID text_shader_metrics;
  opID text_shader_details;
  opID text_shader_map;
  opID text_rasterizer;
  opID text_blendmode;
} // anon ns


namespace Text_renderer {


void
initialize(opContext *ctx,
           opBuffer *buf)
{
  char core_text_shd_path[LIB_MAX_FILE_PATH_SIZE];
  {
    memset(core_text_shd_path, 0, sizeof(core_text_shd_path));
    strcat(core_text_shd_path, Common::Dir::assets());
    strcat(core_text_shd_path, "shaders/core_text.ogl");
  }
  
  char shader_code[1 << 12];
  {
    memset(shader_code, 0, sizeof(shader_code));
    lib::file::get_contents(core_text_shd_path, shader_code, sizeof(shader_code));
    assert(strlen(shader_code));
  }
  
  char vs_code[1024];
  {
    memset(vs_code, 0, sizeof(vs_code));
    lib::string::get_text_between_tags("/* VERT_SHD */", "/* VERT_SHD */", shader_code, vs_code, sizeof(vs_code));
  }

  char gs_code[1 << 12];
  {
    memset(gs_code, 0, sizeof(gs_code));
    lib::string::get_text_between_tags("/* GEO_SHD */", "/* GEO_SHD */", shader_code, gs_code, sizeof(gs_code));
  }
  
  char fs_code[1024];
  {
    memset(fs_code, 0, sizeof(fs_code));
    lib::string::get_text_between_tags("/* FRAG_SHD */", "/* FRAG_SHD */", shader_code, fs_code, sizeof(fs_code));
  }
  
  opShaderDesc shader_desc;
  {
    memset(&shader_desc, 0, sizeof(shader_desc));
    
    text_shader = opBufferShaderCreate(
      ctx,
      buf,
      "Text Shader",
      vs_code,
      gs_code,
      fs_code,
      &shader_desc
    );
  }
  
  opShaderDataDesc shader_data_wvp_desc;
  {
    memset(&shader_data_wvp_desc, 0, sizeof(shader_data_wvp_desc));
    
    text_shader_wvp = opBufferShaderDataCreate
    (
      ctx,
      buf,
      text_shader,
      "uni_wvp_mat",
      &shader_data_wvp_desc
    );
  }
  
  opShaderDataDesc shader_data_metrics_desc;
  {
    memset(&shader_data_metrics_desc, 0, sizeof(shader_data_metrics_desc));
    
    text_shader_metrics = opBufferShaderDataCreate
    (
      ctx,
      buf,
      text_shader,
      "uni_metrics",
      &shader_data_metrics_desc
    );
  }
  
  opShaderDataDesc shader_data_details_desc;
  {
    memset(&shader_data_details_desc, 0, sizeof(shader_data_details_desc));
    
    text_shader_details = opBufferShaderDataCreate
    (
      ctx,
      buf,
      text_shader,
      "uni_string",
      &shader_data_details_desc
    );
  }
  
  opShaderDataDesc shader_data_map_desc;
  {
    memset(&shader_data_map_desc, 0, sizeof(shader_data_map_desc));
    
    text_shader_map = opBufferShaderDataCreate
    (
      ctx,
      buf,
      text_shader,
      "uni_map_01",
      &shader_data_map_desc
    );
  }
  
  opRasterizerDesc rasterizer_desc;
  {
    memset(&rasterizer_desc, 0, sizeof(rasterizer_desc));
    
    rasterizer_desc.cull_face     = opCullFace_BACK;
    rasterizer_desc.primitive     = opPrimitive_POINT;
    rasterizer_desc.winding_order = opWindingOrder_CCW;
    
    text_rasterizer = opBufferRasterizerCreate(
      ctx,
      buf,
      &rasterizer_desc
    );
  }
  
  opBlendDesc blend_desc;
  {
    memset(&blend_desc, 0, sizeof(blend_desc));
    
    blend_desc.enabled = opBool_TRUE;
    
    text_blendmode = opBufferBlendCreate(ctx, buf, &blend_desc);
  }

  // Load up the resources.
  opBufferExec(ctx, buf);
  
  // Did we load everything?
  {
    assert(shader_desc.status == opStatus_VALID);
    assert(shader_data_wvp_desc.status == opStatus_VALID);
    assert(shader_data_metrics_desc.status == opStatus_VALID);
    assert(shader_data_details_desc.status == opStatus_VALID);
    assert(shader_data_map_desc.status == opStatus_VALID);
    assert(rasterizer_desc.status == opStatus_VALID);
    assert(blend_desc.status == opStatus_VALID);
  }
}


uint32_t
render(const math::mat4 &view_proj_mat,
       const uint32_t cull_mask,
       /*const*/ Draw_call calls[],
       const uint32_t number_of_calls,
       opContext *ctx,
       opBuffer *buf)
{
  // opBuffer is delayed so we need to store the wvp mats here until opExec is called.
  for(uint32_t i = 0; i < number_of_calls; ++i)
  {
    const math::mat4 world_mat = math::mat4_init_with_array(calls[i].world_matrix);
    const math::mat4 wvp_mat = math::mat4_multiply(world_mat, view_proj_mat);
    math::mat4_to_array(wvp_mat, calls[i].wvp_matrix);
  }

  opContextResetStats(ctx);

  opBufferDebugMarkerPush(buf, "// -- [TEXT RENDERER] -- //");
  opBufferDeviceReset(buf);
  opBufferBlendBind(buf, text_blendmode);
  opBufferRasterizerBind(buf, text_rasterizer);
  opBufferShaderBind(buf, text_shader);
  
  for(uint32_t i = 0; i < number_of_calls; ++i)
  {
    opBufferDebugMarkerPush(buf, "// -- [RENDER STRING] -- //");
    opBufferShaderDataBind(buf, text_shader_map, calls[i].texture);
    opBufferShaderDataBind(buf, text_shader_metrics, calls[i].glyph_metrics);
    opBufferShaderDataBind(buf, text_shader_details, calls[i].string_info);
    opBufferShaderDataBind(buf, text_shader_wvp, (void*)&calls[i].wvp_matrix);
    opBufferRenderSubset(buf, 0, calls[i].string_size);
    opBufferDebugMarkerPop(buf);
  }
  
  opBufferDebugMarkerPop(buf);
  opBufferExec(ctx, buf);

  return opContextDrawCallStats(ctx);
}


} // ns
