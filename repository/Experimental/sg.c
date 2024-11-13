#include "sg.h"

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

// strdup
#include <string.h>

#include "os-commons.h"

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

static void sg_node_destruct(struct sg_node_t* self);

static const struct sg_node_type_t SG_NODE_TY = {
  .name = "SceneGraph.Node",
  .destruct = & sg_node_destruct,
  .parent = NULL,
};

struct sg_node_t {
  reference_count_t reference_count;
  struct sg_node_type_t const* type;
  struct sg_node_t* parent;
  struct {
    int x, y, w, h;
  } visual_bounds;
  bool show_bounds;
};

static void sg_node_destruct(struct sg_node_t* self)
{/*Intentionally empty.*/}

int sg_node_the_type(struct sg_node_type_t const** result) {
  *result = &SG_NODE_TY;
  return EXIT_SUCCESS;
}

int sg_node_construct(struct sg_node_t* self) {
  self->reference_count = 1;
  self->parent = NULL;
  self->type = &SG_NODE_TY;
  return EXIT_SUCCESS;
}

int sg_node_ref(struct sg_node_t* self) {
  if (self->reference_count < REFERENCE_COUNT_MAXIMUM) {
    self->reference_count++;
    return EXIT_SUCCESS;
  } else {
    return EXIT_FAILURE;
  }
}

int sg_node_unref(struct sg_node_t* self) {
  if (self->reference_count <= 0) {
    return EXIT_FAILURE;
  }
  if (0 == --self->reference_count) {
    while (self->type) {
      self->type->destruct(self);
      self->type = self->type->parent;
    }
    free(self);
  }
  return EXIT_SUCCESS;
}

int sg_node_get_type(struct sg_node_type_t const** result, struct sg_node_t* self) {
  *result = self->type;
  return EXIT_SUCCESS;
}

int sg_node_get_visual_bounds(struct sg_node_t* self, int* x, int* y, int* w, int* h) {
  *x = self->visual_bounds.x;
  *y = self->visual_bounds.y;
  *w = self->visual_bounds.w;
  *h = self->visual_bounds.h;
  return EXIT_SUCCESS;
}

int sg_node_set_visual_bounds(struct sg_node_t* self, int x, int y, int w, int h) {
  self->visual_bounds.x = x;
  self->visual_bounds.y = y;
  self->visual_bounds.w = w;
  self->visual_bounds.h = h;
  return EXIT_SUCCESS;
}

int sg_node_set_show_bounds(struct sg_node_t* self, bool show_bounds) {
  self->show_bounds = show_bounds;
  return EXIT_SUCCESS;
}

int sg_node_get_show_bounds(bool* result, struct sg_node_t* self) {
  *result = self->show_bounds;
  return EXIT_SUCCESS;
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

static void sg_list_destruct(struct sg_list_t* self);

static const struct sg_node_type_t SG_LIST_TY = {
  .name = "SceneGraph.List",
  .destruct = (void (*)(struct sg_node_t*)) &sg_list_destruct,
  .parent = &SG_NODE_TY,
};

struct sg_list_t {
  struct sg_node_t _parent;
  struct {
    struct sg_node_t** elements;
    size_t size;
    size_t capacity;
  } children;
};

static void sg_list_destruct(struct sg_list_t* self) {
  while (self->children.size > 0) {
    sg_node_unref(self->children.elements[--self->children.size]);
  }
  free(self->children.elements);
  self->children.elements = NULL;
  self->children.capacity = 0;
}

int sg_list_the_type(struct sg_node_type_t const** result) {
  *result = &SG_LIST_TY;
  return EXIT_SUCCESS;
}

int sg_list_create(struct sg_list_t** result) {
  struct sg_list_t* self = malloc(sizeof(struct sg_list_t));
  if (!self) {
    fprintf(stderr, "%s:%d: unable to allocate %zu Bytes\n", __FILE__, __LINE__, sizeof(struct sg_list_t));
    return EXIT_FAILURE;
  }
  if (sg_node_construct((struct sg_node_t*)self)) {
    free(self);
    return EXIT_FAILURE;
  }
  self->children.capacity = 8;
  self->children.elements = malloc(sizeof(struct sg_node_t*) * self->children.capacity);
  if (!self->children.elements) {
    free(self);
    self = NULL;
    return EXIT_FAILURE;
  }
  self->children.size = 0;
  ((struct sg_node_t*)self)->type = &SG_LIST_TY;
  *result = self;
  return EXIT_SUCCESS;
}

int sg_list_append(struct sg_list_t* self, struct sg_node_t* node) {
  if (os_ensure_free_capacity((void**)&self->children.elements, self->children.size, &self->children.capacity, sizeof(struct sg_node_t*), 1)) {
    return EXIT_FAILURE;
  }
  self->children.elements[self->children.size++] = node;
  sg_node_ref(node);
  return EXIT_SUCCESS;
}

int sg_list_get_size(size_t* result, struct sg_list_t* self) {
  *result = self->children.size;
  return EXIT_SUCCESS;
}

int sg_list_get_at(struct sg_node_t** result, struct sg_list_t* self, size_t i) {
  *result = self->children.elements[i];
  return EXIT_SUCCESS;
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

static void sg_text_destruct(struct sg_text_t* self);

static const struct sg_node_type_t SG_TEXT_TY = {
  .name = "SceneGraph.Text",
  .destruct = (void (*)(struct sg_node_t*)) &sg_text_destruct,
  .parent = &SG_NODE_TY,
};

struct sg_text_t {
  struct sg_node_t _parent;
  char* t;
  struct sg_color_t* c;
  int x, y;
};

static void sg_text_destruct(struct sg_text_t* self) {
  free(self->t);
  self->t = NULL;
  sg_node_unref((struct sg_node_t*)self->c);
  self->c = NULL;
}

int sg_text_the_type(struct sg_node_type_t const** result) {
  *result = &SG_TEXT_TY;
  return EXIT_SUCCESS;
}

int sg_text_create(struct sg_text_t** result, int x, int y, char const* t, struct sg_color_t* c) {
  struct sg_text_t* self = malloc(sizeof(struct sg_text_t));
  if (!self) {
    fprintf(stderr, "%s:%d: unable to allocate %zu Bytes\n", __FILE__, __LINE__, sizeof(struct sg_text_t));
    return EXIT_FAILURE;
  }
  if (sg_node_construct((struct sg_node_t*)self)) {
    free(self);
    self = NULL;
    return EXIT_FAILURE;
  }
  self->x = x;
  self->y = y;
  self->t = _strdup(t);
  if (!self->t) {
    free(self);
    self = NULL;
    return EXIT_FAILURE;
  }
  self->c = c;
  if (sg_node_ref((struct sg_node_t*)self->c)) {
    free(self->t);
    self->t = NULL;
    free(self);
    self = NULL;
    return EXIT_FAILURE;
  }
  ((struct sg_node_t*)self)->type = &SG_TEXT_TY;
  *result = self;
  return EXIT_SUCCESS;
}

int sg_text_get_color(struct sg_color_t** result, struct sg_text_t* self) {
  *result = self->c;
  return EXIT_SUCCESS;
}

int sg_text_get_position(struct sg_text_t* self, int* x, int* y) {
  *x = self->x;
  *y = self->y;
  return EXIT_SUCCESS;
}

int sg_text_get_text(struct sg_text_t* self, char const** text) {
  *text = self->t;
  return EXIT_SUCCESS;
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

static void sg_rectangle_destruct(struct sg_rectangle_t* self);

static const struct sg_node_type_t SG_RECTANGLE_TY = {
  .name = "SceneGraph.Rectangle",
  .destruct = (void (*)(struct sg_node_t*)) &sg_rectangle_destruct,
  .parent = &SG_NODE_TY,
};

struct sg_rectangle_t {
  struct sg_node_t _parent;
  int x, y, w, h;
  struct sg_color_t* c;
};

static void sg_rectangle_destruct(struct sg_rectangle_t* self) {
  sg_node_unref((struct sg_node_t*)self->c);
  self->c = NULL;
}

int sg_rectangle_the_type(struct sg_node_type_t const** result) {
  *result = &SG_RECTANGLE_TY;
  return EXIT_SUCCESS;
}

int sg_rectangle_create(struct sg_rectangle_t** result, int x, int y, int w, int h, struct sg_color_t* c) {
  struct sg_rectangle_t* self = malloc(sizeof(struct sg_rectangle_t));
  if (!self) {
    fprintf(stderr, "%s:%d: unable to allocate %zu Bytes\n", __FILE__, __LINE__, sizeof(struct sg_rectangle_t));
    return EXIT_FAILURE;
  }
  if (sg_node_construct((struct sg_node_t*)self)) {
    free(self);
    self = NULL;
    return EXIT_FAILURE;
  }
  self->x = x;
  self->y = y;
  self->w = w;
  self->h = h;
  self->c = c;
  if (sg_node_ref((struct sg_node_t*)self->c)) {
    free(self);
    self = NULL;
    return EXIT_FAILURE;
  }
  ((struct sg_node_t*)self)->type = &SG_RECTANGLE_TY;
  *result = self;
  return EXIT_SUCCESS;
}

int sg_rectangle_get_color(struct sg_color_t** result, struct sg_rectangle_t* self) {
  *result = self->c;
  return EXIT_SUCCESS;
}

int sg_rectangle_get_position(struct sg_rectangle_t* self, int* x, int* y) {
  *x = self->x;
  *y = self->y;
  return EXIT_SUCCESS;
}

int sg_rectangle_set_position(struct sg_rectangle_t* self, int x, int y) {
  self->x = x;
  self->y = y;
  return EXIT_SUCCESS;
}

int sg_rectangle_get_size(struct sg_rectangle_t* self, int* w, int* h) {
  *w = self->w;
  *h = self->h;
  return EXIT_SUCCESS;
}

int sg_rectangle_set_size(struct sg_rectangle_t* self, int w, int h) {
  self->w = w;
  self->h = h;
  return EXIT_SUCCESS;
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

static void sg_color_destruct(struct sg_color_t* self);

static const struct sg_node_type_t SG_COLOR_TY = {
  .name = "SceneGraph.Color",
  .destruct = (void (*)(struct sg_node_t*)) &sg_color_destruct,
  .parent = &SG_NODE_TY,
};

struct sg_color_t {
  struct sg_node_t _parent;
  uint8_t r;
  uint8_t g;
  uint8_t b;
};

void sg_color_destruct(struct sg_color_t* self)
{/*Intentionally empty.*/}

int sg_color_the_type(struct sg_node_type_t const** result) {
  *result = &SG_COLOR_TY;
  return EXIT_SUCCESS;
}

int sg_color_pack_rgbx(uint32_t* result, struct sg_color_t* self, uint8_t x) {
  *result = self->r << 24 | self->g << 16 | self->b << 8 | x << 0;
  return EXIT_SUCCESS;
}
int sg_color_pack_xrgb(uint32_t* result, struct sg_color_t* self, uint8_t x) {
  *result = x << 24 | self->r << 16 | self->g << 8 | self->b << 0;
  return EXIT_SUCCESS;
}
int sg_color_pack_bgrx(uint32_t* result, struct sg_color_t* self, uint8_t x) {
  *result = self->b << 24 | self->g << 16 | self->r << 8 | x << 0;
  return EXIT_SUCCESS;
}
int sg_color_pack_xbgr(uint32_t* result, struct sg_color_t* self, uint8_t x) {
  *result = x << 24 | self->b << 16 | self->g << 8 | self->r << 0;
  return EXIT_SUCCESS;
}

int sg_color_create(struct sg_color_t** result, uint8_t r, uint8_t g, uint8_t b) {
  struct sg_color_t* self = malloc(sizeof(struct sg_color_t));
  if (!self) {
    fprintf(stderr, "%s:%d: unable to allocate %zu Bytes\n", __FILE__, __LINE__, sizeof(struct sg_color_t));
    return EXIT_FAILURE;
  }
  if (sg_node_construct((struct sg_node_t*)self)) {
    free(self);
    self = NULL;
    return EXIT_FAILURE;
  }
  self->r = r;
  self->g = g;
  self->b = b;
  ((struct sg_node_t*)self)->type = &SG_COLOR_TY;
  *result = self;
  return EXIT_SUCCESS;
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

static void sg_top_down_viewer_destruct(struct sg_top_down_viewer_t* self)
{/*Intentionally empty.*/}

static const struct sg_node_type_t SG_TOP_DOWN_VIEWER_TY = {
  .name = "SceneGraph.TopDownViewer",
  .destruct = (void (*)(struct sg_node_t*)) & sg_top_down_viewer_destruct,
  .parent = &SG_NODE_TY,
};

struct sg_top_down_viewer_t {
  struct sg_node_t _parent;
  int origin_x;
  int origin_y;
};

int sg_top_down_viewer_the_type(struct sg_node_type_t const** result) {
  *result = &SG_TOP_DOWN_VIEWER_TY;
  return EXIT_SUCCESS;
}

int sg_top_down_viewer_create(struct sg_top_down_viewer_t** result, int origin_x, int origin_y) {
  struct sg_top_down_viewer_t* self = malloc(sizeof(struct sg_top_down_viewer_t));
  if (!self) {
    fprintf(stderr, "%s:%d: unable to allocate %zu Bytes\n", __FILE__, __LINE__, sizeof(struct sg_top_down_viewer_t));
    return EXIT_FAILURE;
  }
  if (sg_node_construct((struct sg_node_t*)self)) {
    free(self);
    self = NULL;
    return EXIT_FAILURE;
  }
  self->origin_x = origin_x;
  self->origin_y = origin_y;
  ((struct sg_node_t*)self)->type = &SG_TOP_DOWN_VIEWER_TY;
  *result = self;
  return EXIT_SUCCESS;
}

int sg_top_down_viewer_set_origin(struct sg_top_down_viewer_t* self, int origin_x, int origin_y) {
  self->origin_x = origin_x;
  self->origin_y = origin_y;
  return EXIT_SUCCESS;
}

int sg_top_down_viewer_get_origin(struct sg_top_down_viewer_t* self, int* origin_x, int* origin_y) {
  *origin_x = self->origin_x;
  *origin_y = self->origin_y;
  return EXIT_SUCCESS;
}
