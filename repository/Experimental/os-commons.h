#if !defined(OS_COMMONS_H_INCLUDED)
#define OS_COMMONS_H_INCLUDED

// size_t, SIZE_MAX
#include <stddef.h>

// bool, true, false
#include <stdbool.h>

// u?int(8|16|32|64)_t, U?INT(8|16|32|64)_(MIN|MAX)
#include <stdint.h>

typedef int64_t reference_count_t;
#define REFERENCE_COUNT_MINIMUM (INT64_MIN)
#define REFERENCE_COUNT_MAXIMUM (INT64_MAX)

int os_deallocate(void* p);

int os_reallocate(void** p, size_t n);

int os_allocate(void** p, size_t n);

int os_ensure_free_capacity(void** elements, size_t size, size_t* capacity, size_t element_size, size_t required_free_capacity);

#endif // OS_COMMONS_H_INCLUDED
