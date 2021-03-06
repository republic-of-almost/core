#ifndef CONTEXT_DETAIL_INCLUDED_FDB7F20D_9B77_4AF1_892F_7B2C7361F763
#define CONTEXT_DETAIL_INCLUDED_FDB7F20D_9B77_4AF1_892F_7B2C7361F763


#include <data/context_data/context_data_fwd.hpp>

struct nk_context;

namespace Core {
namespace Context_detail {


struct Data
{
  Context_data::Input_pool   *input_pool = nullptr;
  nk_context *ctx = nullptr;
};


} // ns
} // ns


#endif // inc guard