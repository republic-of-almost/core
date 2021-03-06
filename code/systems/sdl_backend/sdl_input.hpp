#ifndef SDL_INPUT_INCLUDED_46AF05A3_F13C_4CDB_B560_75EFEC2B20B8
#define SDL_INPUT_INCLUDED_46AF05A3_F13C_4CDB_B560_75EFEC2B20B8


#include <data/context_data/input_pool.hpp>
#include <SDL2/SDL.h>


namespace Sdl {


void
update_gamepad_controller(Context_data::Game_controller *controller, const uint32_t controller_id);


void
update_keyboard_controller(Context_data::Game_controller *controller);


void
capture_mouse(const bool set);


bool
is_mouse_captured();


void
process_input_messages(const SDL_Event *evt,
                       Context_data::Input_pool *input_data);
  


using Text_input_stream_fn = void(*)(const uint8_t *utf8_stream, const size_t size_of_stream);

void
get_text_input_stream(const Text_input_stream_fn &text_input_stream);


} // ns


#endif // inc guard