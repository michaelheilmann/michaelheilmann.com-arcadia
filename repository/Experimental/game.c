#include "game.h"

// malloc, free, realloc
#include <malloc.h>

// fprintf, stderr, stdout
#include <stdio.h>

// EXIT_SUCCESS, EXIT_FAILURE
#include <stdlib.h>

// uint32_t
#include <stdint.h>

// bool, true, false
#include <stdbool.h>

struct ids_t* g_ids = NULL;

static inline int _ensure_free_capacity(void** elements, size_t size, size_t* capacity, size_t element_size, size_t required_free_capacity) {
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

// "ids" allows for acquiring and relinquishing unique IDs within a process.

struct id_t {
  uint32_t value;
};

struct ids_t {
  uint64_t reference_count;
  struct id_t** elements;
  uint32_t hi; // the highest id generated so far
  size_t size;
  size_t capacity;
};

int ids_relinquish_id(struct ids_t* self, struct id_t* id) {
  if (_ensure_free_capacity((void**)&self->elements, self->size, &self->capacity, sizeof(struct id_t*), 1)) {
    return EXIT_FAILURE;
  }
  self->elements[self->size++] = id;
  return EXIT_SUCCESS;
}

int ids_acquire_id(struct id_t** result, struct ids_t* self) {
  if (self->size > 0) {
    struct id_t* element = self->elements[--self->size];
    *result = element;
    return EXIT_SUCCESS;
  } else {
    if (self->hi == UINT32_MAX) {
      return EXIT_FAILURE;
    }
    struct id_t* element =  malloc(sizeof(struct id_t));
    if (!element) {
      fprintf(stderr, "%s:%d: unable to allocate %zu Bytes\n", __FILE__, __LINE__, sizeof(struct id_t));
      return EXIT_FAILURE;
    }
    element->value = ++self->hi;
    *result = element;
    return EXIT_SUCCESS;
  }
}

int ids_ref(struct ids_t* self) {
  if (g_ids->reference_count < UINT64_MAX) {
    g_ids->reference_count++;
    return EXIT_SUCCESS;
  } else {
    return EXIT_FAILURE;
  }
}

int ids_acquire(struct ids_t** result) {
  if (!g_ids) {
    g_ids = malloc(sizeof(struct ids_t));
    if (!g_ids) {
      fprintf(stderr, "%s:%d: unable to allocate %zu Bytes\n", __FILE__, __LINE__, sizeof(struct ids_t));
      return EXIT_FAILURE;
    }
    g_ids->capacity = 8;
    g_ids->elements = malloc(sizeof(struct id_t*) * g_ids->capacity);
    if (!g_ids->elements) {
      fprintf(stderr, "%s:%d: unable to allocate %zu Bytes\n", __FILE__, __LINE__, sizeof(struct id_t*) * 8);
      return EXIT_FAILURE;
    }
    g_ids->capacity = 8;
    g_ids->size = 0;
    g_ids->hi = 0;
    g_ids->reference_count = 1;
  } else {
    if (g_ids->reference_count < UINT64_MAX) {
      g_ids->reference_count++;
    }
  }
  *result = g_ids;
  return EXIT_SUCCESS;
}

void ids_relinquish(struct ids_t* self) {
  if (0 == --g_ids->reference_count) {
    while (g_ids->size > 0) {
      struct id_t* element = g_ids->elements[--g_ids->size];
      free(element);
    }

    free(g_ids->elements);
    g_ids->elements = NULL;
    g_ids->capacity = 0;

    free(g_ids);
    g_ids = NULL;
  }
}
