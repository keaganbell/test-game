#pragma once

#include "defines.h"

#define DARRAY_DEFAULT_CAPACITY 1
#define DARRAY_RESIZE_FACTOR 2

#define darray_create(type) \
    _darray_create(DARRAY_DEFAULT_CAPACITY, sizeof(type), 0)

#define darray_push(array, value)           \
    {                                       \
        typeof(value) temp = value;         \
        array = _darray_push(array, &temp); \
    }

#define darray_insert_at(array, index, value)           \
    {                                                   \
        typeof(value) temp = value;                     \
        array = _darray_insert_at(array, index, &temp); \
    }

KAPI void* darray_pop_at(void* array, u64 index, void* value_ptr);
KAPI void darray_pop(void* array, void* value_ptr);
KAPI void darray_clear(void* array);
KAPI void darray_destroy(void* array);
KAPI void darray_length_set(void* array, u64 value);

KAPI u64 darray_capacity(void* array);
KAPI u64 darray_length(void* array);
KAPI u64 darray_stride(void* array);

KAPI void* _darray_create(u64 length, u64 stride);
KAPI void* _darray_resize(void* array);
KAPI void* _darray_push(void* array, const void* value_ptr);
KAPI void* _darray_insert_at(void* array, u64 index, void* value_ptr);
