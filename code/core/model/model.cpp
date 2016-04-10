#include <core/model/model.hpp>
#include <core/model/mesh.hpp>
#include <data/world_data/world.hpp>
#include <data/world_data/world_pools.hpp>
#include <data/resource_data/mesh_pool.hpp>
#include <data/resource_data/resource_data.hpp>
#include <stddef.h>
#include <assert.h>

#include <utilities/obj_model_loader.hpp>
#include <algorithm>
#include <graphics_api/mesh.hpp>
#include <stdint.h>
#include <utilities/logging.hpp>


namespace Core {


struct Model::Impl
{
  uint32_t mesh_id = 0; // currently a model only supports one mesh.
};


Model::Model()
{
}


Model::Model(const uint32_t id)
: m_impl(new Impl{id})
{
  // TODO: Check that the id is valid.
}


Model::Model(const char *filename)
: m_impl(new Impl)
{
  LOG_TODO("Check there is space in the pool first.");
  
  const std::string file(filename);
  const util::obj_model model(util::load_obj(file));
  
  // No data.
  if(model.meshes.empty())
  {
    assert(false);
    return;
  }
  
  const util::gl_mesh imported_mesh(util::convert_to_open_gl_mesh(model.meshes.front()));
  
  // Add mesh to mesh manager.
  if(!imported_mesh.mesh_data.empty())
  {
    Resource_data::Resources *resources = Resource_data::get_resources();
  
    m_impl->mesh_id = Resource_data::mesh_pool_push_new(resources->mesh_pool,
                                                        filename,
                                                        imported_mesh.mesh_data.data(),
                                                        imported_mesh.mesh_data.size(),
                                                        nullptr,
                                                        0);
  }
}


Model::~Model()
{
}


Model::Model(const Model &other)
: m_impl(new Impl(*other.m_impl))
{
}


Model::Model(Model &&other)
: m_impl(new Impl(*other.m_impl))
{
}


Model&
Model::operator=(const Model &other)
{
  m_impl.reset(new Impl);
  m_impl->mesh_id = other.m_impl->mesh_id;
  return *this;
}


Model&
Model::operator=(Model &&other)
{
  m_impl.reset(new Impl);
  m_impl->mesh_id = other.m_impl->mesh_id;
  return *this;
}


bool
Model::has_meshes() const
{
  if(m_impl && m_impl->mesh_id)
  {
    return true;
  }
  
  return false;
}


Mesh
Model::get_mesh(const uint32_t index) const
{
  if(m_impl && m_impl->mesh_id)
  {
    // Get mesh
  }
  
  return Mesh();
}


math::aabb
Model::get_model_aabb() const
{
  math::aabb return_aabb;
  
  Resource_data::Mesh_pool *mesh_pool = Resource_data::get_resources()->mesh_pool;
  assert(mesh_pool);
  
  size_t id_index;
  
  if(math::index_linear_search(m_impl->mesh_id,
                               mesh_pool->id,
                               mesh_pool->capacity,
                               &id_index))
  {
    return_aabb = mesh_pool->aabb[id_index];
  }
  
  return return_aabb;
}


uint32_t
Model::get_id() const
{
  if(m_impl)
  {
    return m_impl->mesh_id;
  }
  
  return 0;
}


} // ns