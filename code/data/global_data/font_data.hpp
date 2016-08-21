

/*
  WARNING
  -------
  This file is auto generated any changes here may be overwritten.
  See code_gen.rake in scripts folder.

  This file was last generated on: Sun 21 Aug 2016
*/


#ifndef FONT_DATA_INCLUDED_3706D304_8741_4F76_A8F4_E0373A6F3CCE
#define FONT_DATA_INCLUDED_3706D304_8741_4F76_A8F4_E0373A6F3CCE


#include <utilities/generic_id.hpp>
#include <utilities/memory_pool.hpp>
#include <stddef.h>
#include <3rdparty/stb/stb_truetype.h>
#include <systems/text/font_bitmap.hpp>


namespace Resource_data {


/*!
  \brief Auto-generated structure for Font_data
*/
struct Font_data
{
  // Data Key
  util::generic_id *font_id = nullptr;

  // Properties
  char *property_font_name = nullptr;
  stbtt_fontinfo *property_font_face = nullptr;
  Text::Font_bitmap *property_font_bitmap = nullptr;
  util::generic_id *property_texture_id = nullptr;

  // Size information
  size_t size = 0;
  const size_t capacity = 0;


  // Memory chunk
  const util::memory_chunk memory = util::memory_chunk();
}; // struct


/*!
  \brief initialise the Font_data structure, this is will allocate the memory for the keys and properties. Function will take a lock.
  \param data This structure to initialise.
  \param size_hint This helps the init function allocate the correct memory.
*/
void
font_data_init(Font_data *data, const size_t size_hint);


/*!
  \brief Not currently implemented, but will return the memory. Function will take a lock.
  \param data The data to free.
*/
void
font_data_free(Font_data *data);


/*!
  \brief Gets the number of items in the container.
  \param data The structure which to find the size.
*/
size_t
font_data_get_size(const Font_data *data);


/*!
  \brief Gets the capacity before new memory is needed.
  \param data The structure which to find the capacity.
*/
size_t
font_data_get_capacity(const Font_data *data);


/*!
  \brief Locks the data, any thing else requiring a lock will have to wait (not implemented).
  \param data The container to lock.
*/
void
data_lock(const Font_data *data);


/*!
  \brief Unlocks the data, any pending locks can now proceed (not implemented).
  \param The container to unlock
*/
void
data_unlock(const Font_data *data);

/*!
  \brief Push back a new element, increases the size by 1. (Does not take a lock).
  \param data The container which to push back.
  \param key The id to use as a key.
  \param out_index Optional - this will return the inserted location in the container.
  \return Returns true if it was successful.
*/
bool
font_data_push_back(Font_data *data, const util::generic_id key, size_t *out_index = nullptr);


/*!
  \brief Erase an item from the container, decreases size by 1. (Does not take a lock).
  \param data The container to erase from.
  \param key The key which is used to remove the data.
  \return Returns true if it was successful.
*/
bool
font_data_erase(Font_data *data, const util::generic_id key);


/*!
  \brief Checks to see if a key exists in the container.
  \param data The container to search.
  \param key The key to search for.
  \param out_index Optional - this will return the location of the key.
  \return Returns true if a key was found.
*/
bool
font_data_exists(const Font_data *data, const util::generic_id key, size_t *out_index = nullptr);


/*!
  \brief Getter for property_font_name.
  \param data The container to get information from.
  \param key The key to search for.
  \param value The output value, which will be set if the key is found.
  \return Returns true if the data was found.
*/
bool
font_data_get_property_font_name(const Font_data *data, const util::generic_id key, const char **value);


/*!
  \brief Setter for property_font_name.
  \param data The container to update.
  \param key The key to search for.
  \param value The new value of the data.
  \return Returns true if the data was set.
*/
bool
font_data_set_property_font_name(Font_data *data,  const util::generic_id key, const char *value);


/*!
  \brief Searches for a given value.
  \param data The container to search.
  \param value The value which to search for.
  \param out_key Optional the key for that value.
  \return Returns true if the data was found.
*/
bool
font_data_search_property_font_name(const Font_data *data, const char *value, util::generic_id *out_key = nullptr);


/*!
  \brief Getter for property_font_face.
  \param data The container to get information from.
  \param key The key to search for.
  \param value The output value, which will be set if the key is found.
  \return Returns true if the data was found.
*/
bool
font_data_get_property_font_face(const Font_data *data, const util::generic_id key, stbtt_fontinfo *value);


/*!
  \brief Setter for property_font_face.
  \param data The container to update.
  \param key The key to search for.
  \param value The new value of the data.
  \return Returns true if the data was set.
*/
bool
font_data_set_property_font_face(Font_data *data,  const util::generic_id key, const stbtt_fontinfo value);


/*!
  \brief Getter for property_font_bitmap.
  \param data The container to get information from.
  \param key The key to search for.
  \param value The output value, which will be set if the key is found.
  \return Returns true if the data was found.
*/
bool
font_data_get_property_font_bitmap(const Font_data *data, const util::generic_id key, Text::Font_bitmap *value);


/*!
  \brief Setter for property_font_bitmap.
  \param data The container to update.
  \param key The key to search for.
  \param value The new value of the data.
  \return Returns true if the data was set.
*/
bool
font_data_set_property_font_bitmap(Font_data *data,  const util::generic_id key, const Text::Font_bitmap value);


/*!
  \brief Getter for property_texture_id.
  \param data The container to get information from.
  \param key The key to search for.
  \param value The output value, which will be set if the key is found.
  \return Returns true if the data was found.
*/
bool
font_data_get_property_texture_id(const Font_data *data, const util::generic_id key, util::generic_id *value);


/*!
  \brief Setter for property_texture_id.
  \param data The container to update.
  \param key The key to search for.
  \param value The new value of the data.
  \return Returns true if the data was set.
*/
bool
font_data_set_property_texture_id(Font_data *data,  const util::generic_id key, const util::generic_id value);


} // ns


#endif // inc guard
