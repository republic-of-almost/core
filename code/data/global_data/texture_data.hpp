

/*
  Warning:
  This file is auto_generated any changes here may be overwritten.
*/


#ifndef TEXTURE_DATA_INCLUDED_EC1713C8_5995_4131_BB1C_BECC86EF2333
#define TEXTURE_DATA_INCLUDED_EC1713C8_5995_4131_BB1C_BECC86EF2333


#include <utilities/generic_id.hpp>
#include <utilities/memory_pool.hpp>
#include <stddef.h>
#include <graphics_api/ogl/ogl_texture.hpp>


namespace Resource_data {



/*!
  \brief Auto-generated structure for Texture_data
*/
struct Texture_data
{
  // Data Key
  util::generic_id *texture_id = nullptr;

  // Properties
  char *property_name = nullptr;
  Ogl::Texture *property_texture = nullptr;

  // Size information
  size_t size = 0;
  const size_t capacity = 0;

  // Memory chunk
  const util::memory_chunk memory = util::memory_chunk();

}; // struct


/*!
  \brief Initialize the Texture_data structure, this is will allocate the memory for the keys and properties. Function will take a lock.
  \param data This structure to initialize.
  \param size_hint This helps the init function allocate the correct memory.
*/
void
texture_data_init(Texture_data *data, const size_t size_hint);


/*!
  \brief Not currently implimented, but will return the memory. Function will take a lock.
  \param data The data to free.
*/
void
texture_data_free(Texture_data *data);


/*!
  \brief Gets the number of items in the container.
  \param data The structure which to find the size.
*/
size_t
texture_data_get_size(const Texture_data *data);


/*!
  \brief Gets the capacity before new memory is needed.
  \param data The structure which to find the capacity.
*/
size_t
texture_data_get_capacity(const Texture_data *data);


/*!
  \brief Locks the data, any thing else requiring a lock will have to wait (not implimented).
  \param data The container to lock.
*/
void
data_lock(Texture_data *data);


/*!
  \brief Unlocks the data, any pending locks can now proceed (not implimented).
  \param The container to unlock
*/
void
data_unlock(Texture_data *data);


/*!
  \brief Push back a new element, increases the size by 1. (Does not take a lock).
  \param data The container which to push back.
  \param key The id to use as a key.
  \param out_index Optional - this will return the inserted location in the container.
  \return Returns true if it was successful.
*/
bool
texture_data_push_back(Texture_data *data, const util::generic_id key, size_t *out_index = nullptr);


/*!
  \brief Erase an item from the container, decreases size by 1. (Does not take a lock).
  \param data The container to erase from.
  \param key The key which is used to remove the data.
  \return Returns true if it was successful.
*/
bool
texture_data_erase(Texture_data *data, const util::generic_id key);


/*!
  \brief Checks to see if a key exists in the container.
  \param data The container to search.
  \param key The key to search for.
  \param out_index Optional - this will return the location of the key.
  \return Returns true if a key was found.
*/
bool
texture_data_exists(const Texture_data *data, const util::generic_id key, size_t *out_index = nullptr);


/*!
  \brief Getter for property_name.
  \param data The container to get information from.
  \param key The key to search for.
  \param value The output value, which will be set if the key is found.
  \return Returns true if the data was found.
*/
bool
texture_data_get_property_name(const Texture_data *data, const util::generic_id key, const char **value);


/*!
  \brief Setter for property_name.
  \param data The container to update.
  \param key The key to search for.
  \param value The new value of the data.
  \return Returns true if the data was set.
*/
bool
texture_data_set_property_name(Texture_data *data,  const util::generic_id key, const char *value);


/*!
  \brief Searches for a given value.
  \param data The container to search.
  \param value The value which to search for.
  \param out_key Optional the key for that value.
  \return Returns true if the data was found.
*/
bool
texture_data_search_property_name(const Texture_data *data, const char *value, util::generic_id *out_key = nullptr);


/*!
  \brief Getter for property_texture.
  \param data The container to get information from.
  \param key The key to search for.
  \param value The output value, which will be set if the key is found.
  \return Returns true if the data was found.
*/
bool
texture_data_get_property_texture(const Texture_data *data, const util::generic_id key, Ogl::Texture *value);


/*!
  \brief Setter for property_texture.
  \param data The container to update.
  \param key The key to search for.
  \param value The new value of the data.
  \return Returns true if the data was set.
*/
bool
texture_data_set_property_texture(Texture_data *data,  const util::generic_id key, const Ogl::Texture value);


} // ns


#endif // inc guard