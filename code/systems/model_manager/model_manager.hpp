#ifndef MESH_DATA_INCLUDED_A8754D41_F518_4378_A1D4_7B46EEE7387D
#define MESH_DATA_INCLUDED_A8754D41_F518_4378_A1D4_7B46EEE7387D


#include <cstddef>
#include <stdint.h>
#include <simple_renderer/vertex_buffer.hpp>


namespace Model {


struct Load_model
{
  const std::size_t id;         //!< Index into the output.
  const std::string file_name;  //!< File to load
}; // struct


/*!
  Loads models into output array, using the given index (id) provided in Load_model.
  \param model_to_load[] array of Load_model with details of things to load.
  \param number_of_models_to_load size of the model_to_load array.
  \param output_vbo[] array of vbo's that get created.
  \param size_of_output_pool size of output_vbo array.
*/
void
model_load(const Load_model models_to_load[],
           const std::size_t number_of_models_to_load,
           renderer::vertex_buffer output_vbo[],
           const std::size_t size_of_output_pool);

  
void
find_model_data(renderer::vertex_buffer output_vbo[],
                const std::size_t size_of_output,
                const uint32_t input_ids[],
                const renderer::vertex_buffer input_vbo[],
                const std::size_t size_of_input);



} // ns


#endif // inc guard