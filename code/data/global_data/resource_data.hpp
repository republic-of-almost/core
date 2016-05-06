#ifndef RESOURCE_DATA_INCLUDED_B0311127_B368_4A55_B58E_37C7198A76EA
#define RESOURCE_DATA_INCLUDED_B0311127_B368_4A55_B58E_37C7198A76EA


#include "audio_pool.hpp"
#include "audio_raw_pool.hpp"
#include "mesh_pool.hpp"
#include "texture_pool.hpp"


namespace Resource_data {


struct Resources
{
  Texture_pool  *texture_pool = nullptr;
  Audio_pool    *audio_pool   = nullptr;
  Mesh_pool     *mesh_pool    = nullptr;
};


void
resources_init();


Resources*
get_resources();


} // ns


#endif // inc guard