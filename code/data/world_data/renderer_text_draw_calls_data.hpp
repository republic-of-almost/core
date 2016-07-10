

/*
  Warning:
  This file is auto_generated any changes here may be overwritten.
*/


#ifndef RENDERER_TEXT_DRAW_CALLS_DATA_INCLUDED_290F1BA9_F29E_4304_B074_F61EE57307D4
#define RENDERER_TEXT_DRAW_CALLS_DATA_INCLUDED_290F1BA9_F29E_4304_B074_F61EE57307D4


#include <utilities/generic_id.hpp>
#include <utilities/memory_pool.hpp>
#include <stddef.h>


namespace World_data {



/*!
  \brief Auto-generated structure for Renderer_text_draw_calls_data
*/
struct Renderer_text_draw_calls_data
{
  // Data Key
  util::generic_id *renderer_text_draw_calls_id = nullptr;

  // Properties
  char *property_text = nullptr;
  util::generic_id *property_model_id = nullptr;

  // Size information
  size_t size = 0;
  const size_t capacity = 0;


  // Memory chunk
  const util::memory_chunk memory = util::memory_chunk();

}; // struct


/*!
  \brief initialise the Renderer_text_draw_calls_data structure, this is will allocate the memory for the keys and properties. Function will take a lock.
  \param data This structure to initialise.
  \param size_hint This helps the init function allocate the correct memory.
*/
void
renderer_text_draw_calls_data_init(Renderer_text_draw_calls_data *data, const size_t size_hint);


/*!
  \brief Not currently implemented, but will return the memory. Function will take a lock.
  \param data The data to free.
*/
void
renderer_text_draw_calls_data_free(Renderer_text_draw_calls_data *data);


/*!
  \brief Gets the number of items in the container.
  \param data The structure which to find the size.
*/
size_t
renderer_text_draw_calls_data_get_size(const Renderer_text_draw_calls_data *data);


/*!
  \brief Gets the capacity before new memory is needed.
  \param data The structure which to find the capacity.
*/
size_t
renderer_text_draw_calls_data_get_capacity(const Renderer_text_draw_calls_data *data);


/*!
  \brief Locks the data, any thing else requiring a lock will have to wait (not implemented).
  \param data The container to lock.
*/
void
data_lock(const Renderer_text_draw_calls_data *data);


/*!
  \brief Unlocks the data, any pending locks can now proceed (not implemented).
  \param The container to unlock
*/
void
data_unlock(const Renderer_text_draw_calls_data *data);

/*!
  \brief Push back a new element, increases the size by 1. (Does not take a lock).
  \param data The container which to push back.
  \param key The id to use as a key.
  \param out_index Optional - this will return the inserted location in the container.
  \return Returns true if it was successful.
*/
bool
renderer_text_draw_calls_data_push_back(Renderer_text_draw_calls_data *data, const util::generic_id key, size_t *out_index = nullptr);


/*!
  \brief Erase an item from the container, decreases size by 1. (Does not take a lock).
  \param data The container to erase from.
  \param key The key which is used to remove the data.
  \return Returns true if it was successful.
*/
bool
renderer_text_draw_calls_data_erase(Renderer_text_draw_calls_data *data, const util::generic_id key);


/*!
  \brief Inserts a new element shuffling down any data that exists in the array. (Does not take a lock).
  \param data The container to insert into.
  \param key The key which is used to remove the data.
  \param insert_point Where to insert. If bigger then the size it will push back.
  \return Returns true if it was successful.
*/
bool
renderer_text_draw_calls_data_insert(Renderer_text_draw_calls_data *data, const util::generic_id key, const size_t insert_index);


/*!
  \brief Checks to see if a key exists in the container.
  \param data The container to search.
  \param key The key to search for.
  \param out_index Optional - this will return the location of the key.
  \return Returns true if a key was found.
*/
bool
renderer_text_draw_calls_data_exists(const Renderer_text_draw_calls_data *data, const util::generic_id key, size_t *out_index = nullptr);


/*!
  \brief Getter for property_text.
  \param data The container to get information from.
  \param key The key to search for.
  \param value The output value, which will be set if the key is found.
  \return Returns true if the data was found.
*/
bool
renderer_text_draw_calls_data_get_property_text(const Renderer_text_draw_calls_data *data, const util::generic_id key, const char **value);


/*!
  \brief Setter for property_text.
  \param data The container to update.
  \param key The key to search for.
  \param value The new value of the data.
  \return Returns true if the data was set.
*/
bool
renderer_text_draw_calls_data_set_property_text(Renderer_text_draw_calls_data *data,  const util::generic_id key, const char *value);


/*!
  \brief Getter for property_model_id.
  \param data The container to get information from.
  \param key The key to search for.
  \param value The output value, which will be set if the key is found.
  \return Returns true if the data was found.
*/
bool
renderer_text_draw_calls_data_get_property_model_id(const Renderer_text_draw_calls_data *data, const util::generic_id key, util::generic_id *value);


/*!
  \brief Setter for property_model_id.
  \param data The container to update.
  \param key The key to search for.
  \param value The new value of the data.
  \return Returns true if the data was set.
*/
bool
renderer_text_draw_calls_data_set_property_model_id(Renderer_text_draw_calls_data *data,  const util::generic_id key, const util::generic_id value);


} // ns


#endif // inc guard