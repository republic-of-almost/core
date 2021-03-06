#ifndef CAM_UTILS_INCLUDED_24851027_2A53_4F2A_88FA_93B9B5FC7810
#define CAM_UTILS_INCLUDED_24851027_2A53_4F2A_88FA_93B9B5FC7810


#include <systems/camera/camera_properties.hpp>
#include <core/transform/transform_fwd.hpp>
#include <data/fwd_dec_data.hpp>
#include <data/graph/graph.hpp>
#include <graphics_api/ogl/ogl_frame_buffer.hpp>
#include <math/mat/mat4.hpp>
#include <stdint.h>
#include <stddef.h>


namespace Camera_utils {


uint32_t
find_highest_priority(const uint32_t priorities[],
                      const uint32_t count);


size_t
find_insert_point_based_on_priority(const uint32_t priority,
                                    const uint32_t priorities[],
                                    const uint32_t count);


struct Cam_run
{
  Ogl::Frame_buffer fbo;
  math::mat4 view;
  math::mat4 proj;
  math::vec3 eye_pos;
  uint32_t width;
  uint32_t height;
  uint32_t clear_color;
  uint32_t clear_flags;
  uint32_t cull_mask;
  uint32_t post_process_id;
};

/*
  Builds the data for each run for the camera.
  All arrays must be at least the size of count.
*/
void
calculate_camera_runs(const Data::Camera_data *cam_data,
                      const Data::Texture_data *texture_data,
                      const Core::Transform transforms[],
                      Cam_run out_runs[],
                      const uint32_t count);


void
get_camera_transforms(const Data::Graph::Graph_data *transform_data,
                      const uint32_t entity_ids[],
                      Core::Transform out_transforms[],
                      const uint32_t size);


} // ns


#endif // inc guard
