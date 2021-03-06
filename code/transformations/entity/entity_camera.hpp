#ifndef ENTITY_CAMERA_INCLUDED_CFCEEF1D_BEA3_4899_ABB6_6AA2F57945B5
#define ENTITY_CAMERA_INCLUDED_CFCEEF1D_BEA3_4899_ABB6_6AA2F57945B5


#include <core/common/core_fwd.hpp>
#include <data/fwd_dec_data.hpp>
#include <data/graph/fwd.hpp>


namespace Entity_detail {


void
set_camera(const uint32_t this_id,
           Data::Graph::Graph_data *entity_data,
           Data::Camera_data *camera_data,
           const Core::Camera *camera);


void
get_camera(const uint32_t this_id,
           const Data::Camera_data *camera_data,
           Core::Camera *out_camera);


void
remove_camera(const uint32_t this_id,
              Data::Graph::Graph_data *entity_data,
              Data::Camera_data *camera_data);
  

bool
has_camera(const uint32_t this_id,
           Data::Camera_data *camera_data);


} // ns


#endif // inc guard
