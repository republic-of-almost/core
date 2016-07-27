
/*
  Warning:
  This file is auto_generated any changes here may be overwritten.
*/

#include <data/global_data/rasterized_glyphs_data.hpp>
#include <data/global_data/memory_data.hpp>
#include <common/error_strings.hpp>
#include <utilities/logging.hpp>
#include <utilities/memory.hpp>
#include <assert.h>
#include <cstring>


namespace Resource_data {


void
rasterized_glyphs_data_init(Rasterized_glyphs_data *data, const size_t size_hint)
{
  // Argument validation.
  assert(data && size_hint);

  // 16 byte alignment buffer, apply to all for safety.
  constexpr size_t simd_buffer = 16;

  // Calculate the various sizes of things.
  const size_t bytes_rasterized_glyphs_id = sizeof(*data->rasterized_glyphs_id) * size_hint + simd_buffer;
  const size_t bytes_property_character = sizeof(*data->property_character) * size_hint + simd_buffer;

  const size_t bytes_to_alloc = bytes_rasterized_glyphs_id + bytes_property_character;

  // Allocate some memory.
  util::memory_chunk *data_memory = const_cast<util::memory_chunk*>(&data->memory);
  *data_memory = Memory::request_memory_chunk(bytes_to_alloc, "rasterized_glyphs_data");

  assert(data_memory->bytes_in_chunk == bytes_to_alloc);

  data_lock(data);

  // Init memory
  {
    size_t byte_counter = 0;
    const void *alloc_start = data->memory.chunk_start;

    // Assign rasterized_glyphs_id memory
    {
      void *offset = util::mem_offset(alloc_start, byte_counter);
      void *aligned = util::mem_next_16byte_boundry(offset);

      data->rasterized_glyphs_id = reinterpret_cast<util::generic_id*>(aligned);
      #ifndef NDEBUG
      memset(offset, 0, bytes_rasterized_glyphs_id);
      #endif

      byte_counter += bytes_rasterized_glyphs_id;
      assert(byte_counter <= bytes_to_alloc);
    }
    // Assign property_character memory
    {
      void *offset = util::mem_offset(alloc_start, byte_counter);
      void *aligned = util::mem_next_16byte_boundry(offset);

      data->property_character = reinterpret_cast<Text::Character*>(aligned);
      #ifndef NDEBUG
      memset(offset, 0, bytes_property_character);
      #endif

      byte_counter += bytes_property_character;
      assert(byte_counter <= bytes_to_alloc);
    }
  }

  // Set the size and capacity
  {
    data->size = 0;

    size_t *capacity = const_cast<size_t*>(&data->capacity);
    *capacity = size_hint;
  }

  data_unlock(data);
}


void
rasterized_glyphs_data_free(Rasterized_glyphs_data *data)
{
  assert(data);
}


size_t
rasterized_glyphs_data_get_size(const Rasterized_glyphs_data *data)
{
  assert(data);
  return data->size;
}


size_t
rasterized_glyphs_data_get_capacity(const Rasterized_glyphs_data *data)
{
  assert(data);
  return data->capacity;
}


void
data_lock(const Rasterized_glyphs_data *data)
{
  assert(data);
}


void
data_unlock(const Rasterized_glyphs_data *data)
{
  assert(data);
}


bool
rasterized_glyphs_data_push_back(Rasterized_glyphs_data *data, const util::generic_id key, size_t *out_index)
{
  assert(data && key);
  assert(data->size < data->capacity);

  // TODO: Duplicate key check

  if(data->size >= data->capacity)
  {
    LOG_ERROR(Error_string::no_free_space());

    return false;
  }

  const uint32_t index = data->size;

  if(out_index)
  {
    *out_index = index;
  }

  ++(data->size);

  data->rasterized_glyphs_id[index] = key;

  // Memset the properties
  {
    memset(&data->property_character[index], 0, sizeof(*data->property_character));
  }

  return true;
}


bool
rasterized_glyphs_data_erase(Rasterized_glyphs_data *data, const util::generic_id key)
{
  // Param check
  assert(data && key);

  size_t index_to_erase;

  if(rasterized_glyphs_data_exists(data, key, &index_to_erase))
  {
    assert(index_to_erase < data->size);

    const size_t start_index = index_to_erase + 1;
    const size_t size_to_end = data->size - index_to_erase - 1;

    --(data->size);

    // Shuffle the memory down.
    memmove(&data->rasterized_glyphs_id[index_to_erase], &data->rasterized_glyphs_id[start_index], size_to_end * sizeof(*data->rasterized_glyphs_id));
    memmove(&data->property_character[index_to_erase], &data->property_character[start_index], size_to_end * sizeof(*data->property_character));
  }
  else
  {
    LOG_ERROR(Error_string::entity_not_found());
    assert(false);

    return false;
  }

  return true;
}


bool
rasterized_glyphs_data_exists(const Rasterized_glyphs_data *data, const util::generic_id key, size_t *out_index)
{
  assert(data && key);

  if(data->size == 0)
  {
    return false;
  }

  bool found = false;

  size_t no_index;
  if(!out_index) { out_index = &no_index; }

  found = util::generic_id_search_binary(out_index, key, data->rasterized_glyphs_id, data->size);

  return found;
}


bool
rasterized_glyphs_data_get_property_character(const Rasterized_glyphs_data *data, const util::generic_id key, Text::Character *out_value)
{
  size_t index;

  if(rasterized_glyphs_data_exists(data, key, &index))
  {
    *out_value = data->property_character[index];
  }
  else
  {
    LOG_ERROR(Error_string::entity_not_found());
    assert(false);

    return false;
  }

  return true;
}


bool
rasterized_glyphs_data_set_property_character(Rasterized_glyphs_data *data,  const util::generic_id key, const Text::Character value)
{
  assert(data && key);

  size_t index;

  if(rasterized_glyphs_data_exists(data, key, &index))
  {
    data->property_character[index] = value;
  }
  else
  {
    LOG_ERROR(Error_string::entity_not_found());
    assert(false);

    return false;
  }

  return true;
}




} // ns