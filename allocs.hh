#pragma once
typedef unsigned long size_t;

extern "C" void *malloc(size_t size) __THROW __attribute_malloc__;
extern "C" void free (void *__ptr) __THROW;
extern "C" void *realloc (void *__ptr, size_t __size)
     __THROW __attribute_warn_unused_result__ __attribute_alloc_size__ ((2));
