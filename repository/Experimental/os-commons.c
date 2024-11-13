#include "os-commons.h"

#include <malloc.h>
#include <stdlib.h>
#include <stdio.h>

int os_deallocate(void* p) {
  if (!p) {
    fprintf(stderr, "%s:%d: invalid argument `%s`\n", __FILE__, __LINE__, "NULL == p");
    return EXIT_FAILURE;
  }
  free(p);
  return EXIT_SUCCESS;
}

int os_reallocate(void** p, size_t n) {
  if (!p) {
    fprintf(stderr, "%s:%d: invalid argument `%s`\n", __FILE__, __LINE__, "NULL == p");
    return EXIT_FAILURE;
  }
  void* q = realloc(*p, n > 0 ? n : 1);
  if (!q) {
    fprintf(stderr, "%s:%d: unable to reallocate %p to %zu Bytes\n", __FILE__, __LINE__, *p, n);
    return EXIT_FAILURE;
  }
  *p = q;
  return EXIT_SUCCESS;
}

int os_allocate(void** p, size_t n) {
  if (!p) {
    fprintf(stderr, "%s:%d: invalid argument `%s`\n", __FILE__, __LINE__, "NULL == p");
    return EXIT_FAILURE;
  }
  void* q = malloc(n > 0 ? n : 1);
  if (!q) {
    fprintf(stderr, "%s:%d: unable to allocate %zu Bytes\n", __FILE__, __LINE__, n);
    return EXIT_FAILURE;
  }
  *p = q;
  return EXIT_SUCCESS;
}

int os_ensure_free_capacity(void** elements, size_t size, size_t* capacity, size_t element_size, size_t required_free_capacity) {
  size_t available_free_capacity = *capacity - size;
  if (available_free_capacity >= required_free_capacity) {
    return EXIT_SUCCESS;
  }
  const size_t maximal_capacity = SIZE_MAX / element_size;
  size_t additional_capacity = required_free_capacity - available_free_capacity;
  if (maximal_capacity - additional_capacity < *capacity) {
    return EXIT_FAILURE;
  }
  size_t new_capacity = *capacity + additional_capacity;
  void* new_elements = realloc(*elements, new_capacity * element_size);
  if (!new_elements) {
    return EXIT_FAILURE;
  }
  *elements = new_elements;
  *capacity = new_capacity;
  return EXIT_SUCCESS;
}