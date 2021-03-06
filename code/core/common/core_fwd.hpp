#ifndef CORE_FWD_INCLUDED_1B8F0FF5_4504_4628_95CD_CC76FBE5AC11
#define CORE_FWD_INCLUDED_1B8F0FF5_4504_4628_95CD_CC76FBE5AC11


/*
  Single include for core fwd decs.
*/

/*
  Usage Guidlines
  --
  This file is for fwd declerations of public types.
  Don't include fwd decleration of types that should have
  no public interface, like types inside 'detail' directories or namespaces.
*/


#include <core/audio/audio_fwd.hpp>
#include <core/camera/camera_fwd.hpp>
#include <core/color/color_fwd.hpp>
#include <core/common/common_fwd.hpp>
#include <core/context/context_fwd.hpp>
#include <core/entity/entity_fwd.hpp>
#include <core/font/font_fwd.hpp>
#include <core/input/input_fwd.hpp>
#include <core/model/model_fwd.hpp>
#include <core/physics/physics_fwd.hpp>
#include <core/renderer/renderer_fwd.hpp>
#include <core/resources/resources_fwd.hpp>
#include <core/transform/transform_fwd.hpp>
#include <core/world/world_fwd.hpp>
#include <core/lighting/light_fwd.hpp>


#endif // inc guard