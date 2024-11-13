#if !defined(SG_H_INCLUDED)
#define SG_H_INCLUDED

// bool, true, false
#include <stdbool.h>

// uint8_t 
#include <stdint.h>

#include "os-commons.h"

#define SG_NODE_TYPE_LIST (0)
#define SG_NODE_TYPE_TEXT (1)
#define SG_NODE_TYPE_RECTANGLE (2)
#define SG_NODE_TYPE_COLOR (3)

typedef uint8_t sg_node_type_t;

struct sg_node_type_t {
  struct sg_node_type_t const* parent;
  char const* name;
  void (*destruct)(struct sg_node_t* self);
};

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

int sg_node_the_type(struct sg_node_type_t const** result);

int sg_node_construct(struct sg_node_t* self);

int sg_node_ref(struct sg_node_t* self);

int sg_node_unref(struct sg_node_t* self);

int sg_node_get_type(struct sg_node_type_t const** result, struct sg_node_t* self);

/* The initial value is x = 0, y = 0, w = 0, and h = 0. */
int sg_node_get_visual_bounds(struct sg_node_t* self, int* x, int* y, int* w, int* h);

int sg_node_set_visual_bounds(struct sg_node_t* self, int x, int y, int w, int h);

/* The initial value is false */
int sg_node_get_show_bounds(bool* result, struct sg_node_t* self);

int sg_node_set_show_bounds(struct sg_node_t* self, bool show_bounds);

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

int sg_list_the_type(struct sg_node_type_t const** result);

int sg_list_create(struct sg_list_t** result);

int sg_list_append(struct sg_list_t* self, struct sg_node_t* node);

int sg_list_get_size(size_t* result, struct sg_list_t* self);

int sg_list_get_at(struct sg_node_t** result, struct sg_list_t* self, size_t i);

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

int sg_text_the_type(struct sg_node_type_t const** result);

// Note: '\n' and '\r' are skipped.
int sg_text_create(struct sg_text_t** result, int x, int y, char const* text, struct sg_color_t* c);

int sg_text_get_color(struct sg_color_t** result, struct sg_text_t* self);

int sg_text_get_position(struct sg_text_t* self, int *x, int *y);

int sg_text_get_text(struct sg_text_t* self, char const** text);

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

int sg_rectangle_the_type(struct sg_node_type_t const** result);

int sg_rectangle_create(struct sg_rectangle_t** result, int x, int y, int w, int h, struct sg_color_t* c);

int sg_rectangle_get_color(struct sg_color_t** result, struct sg_rectangle_t* self);

int sg_rectangle_get_position(struct sg_rectangle_t* self, int* x, int* y);

int sg_rectangle_set_position(struct sg_rectangle_t* self, int x, int y);

int sg_rectangle_get_size(struct sg_rectangle_t* self, int* w, int* h);

int sg_rectangle_set_size(struct sg_rectangle_t* self, int x, int y);

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

int sg_color_the_type(struct sg_node_type_t const** result);

int sg_color_pack_rgbx(uint32_t* result, struct sg_color_t* self, uint8_t x);

int sg_color_pack_xrgb(uint32_t* result, struct sg_color_t* self, uint8_t x);

int sg_color_pack_bgrx(uint32_t* result, struct sg_color_t* self, uint8_t x);

int sg_color_pack_xbgr(uint32_t* result, struct sg_color_t* self, uint8_t x);

int sg_color_create(struct sg_color_t** result, uint8_t r, uint8_t g, uint8_t b);

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

int sg_top_down_viewer_the_type(struct sg_node_type_t const** result);

int sg_top_down_viewer_create(struct sg_top_down_viewer_t** result, int origin_x, int origin_y);

int sg_top_down_viewer_set_origin(struct sg_top_down_viewer_t* self, int origin_x, int origin_y);

/* Default is x = 0 and y = 0. */
int sg_top_down_viewer_get_origin(struct sg_top_down_viewer_t* self, int *origin_x, int *origin_y);

#endif // SG_H_INCLUDED
