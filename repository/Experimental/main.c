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
#include "os-windows.h"

#include "game.h"

struct map_t {
  /// The SG scene the map adds its node(s) to.
  struct sg_list_t* sg_scene;
  // The scenegraph node representing the map.
  struct sg_node_t* sg_node;
};

int map_create(struct map_t** result, struct sg_list_t* sg_scene) {
  struct map_t* self = NULL;
  if (os_allocate(&self, sizeof(struct map_t))) {
    return EXIT_FAILURE;
  }
  self->sg_scene = sg_scene;
  sg_node_ref((struct sg_node_t*)self->sg_scene);
  self->sg_node = NULL;
  *result = self;
  return EXIT_SUCCESS;
}

void map_destroy(struct map_t* self) {
  if (self->sg_node) {
    sg_node_unref((struct sg_node_t*)self->sg_node);
    self->sg_node = NULL;
  }
  sg_node_unref((struct sg_node_t*)self->sg_scene);
  self->sg_scene = NULL;
  os_deallocate(self);
  self = NULL;
}

int map_render(struct map_t* self, int canvas_width, int canvas_height) {
  if (!self->sg_node) {
    struct sg_list_t* list = NULL;
    if (sg_list_create(&list)) {
      return EXIT_FAILURE;
    }
    struct sg_color_t* floor_color;
    struct sg_rectangle_t* floor_rectangle;
    if (sg_color_create(&floor_color, 160, 160, 160)) {
      sg_node_unref((struct sg_node_t*)list);
      list = NULL;
      return EXIT_FAILURE;
    }
    if (sg_rectangle_create(&floor_rectangle, 0 - 256, 0 - 256, 512, 512, floor_color)) {
      sg_node_unref((struct sg_node_t*)floor_color);
      floor_color = NULL;
      sg_node_unref((struct sg_node_t*)list);
      list = NULL;
      return EXIT_FAILURE;
    }
    sg_node_unref((struct sg_node_t*)floor_color);
    floor_color = NULL;
    if (sg_list_append(list, (struct sg_node_t*)floor_rectangle)) {
      sg_node_unref((struct sg_node_t*)floor_rectangle);
      floor_rectangle = NULL;
      sg_node_unref((struct sg_node_t*)list);
      list = NULL;
      return EXIT_FAILURE;
    }
    sg_node_unref((struct sg_node_t*)floor_rectangle);
    floor_rectangle = NULL;

    if (sg_list_append(self->sg_scene, (struct sg_node_t*)list)) {
      sg_node_unref((struct sg_node_t*)list);
      list = NULL;
      return EXIT_FAILURE;
    }
    self->sg_node = (struct sg_node_t*)list;
    sg_node_unref((struct sg_node_t*)list);
    list = NULL;
  }
  return EXIT_SUCCESS;
}

// a puppet has a name (for display), an ID that is unique wrt all other existing puppets and attributes.
// The attributes are inspired by GURPS (https://gurps.fandom.com/wiki/Attributes) and are
// - strength: measures the physical power and bulk of an individual
// - dexterity: measures agility, coordination, and fine motor ability
// - intelligence: measures creativity, intuition, memory, perception, reason, sanity, and willpower
// - health: measures energy and vitality
// in future versions of this software, a single attribute may be split into multiple other attributes

struct puppets_t {
  struct ids_t* ids;
  struct sg_top_down_viewer_t* sg_viewer;
  struct sg_list_t* sg_scene;
  struct puppet_t** elements;
  size_t size;
  size_t capacity;
};

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

struct puppet_t {
  struct id_t* id;
  // reference to puppets module
  struct puppets_t* puppets;
  // the display name of the puppet
  char* name;
  // the strength attribute
  // 10 is an average human
  int32_t strength;
  // the dexterity attribute
  // 10 is an average human
  int32_t dexterity;
  // the intelligence attribute
  // 10 is an average human
  int32_t intelligence;
  // the health attribute
  // 10 is an average human
  int32_t health;
  // The position.
  int32_t x, y;
  /// The scenegraph node for the audio-visual representation of the puppet.
  struct sg_node_t* sg_node;
};

// Create a puppet with default values.
// The puppet is added to the list of puppets.
// Its default values are:
// - id is a an unique ID
// - name is "<default puppet>"
// - strength is 10
// - dexterity is 10
// - intelligence is 10
// - health is 10
// - position.x = 0
// - position.y = 0
int puppet_create(struct puppet_t** result, struct puppets_t* puppets) {
  struct puppet_t* self = malloc(sizeof(struct puppet_t));
  if (!self) {
    fprintf(stderr, "%s:%d: unable to allocate %zu Bytes\n", __FILE__, __LINE__, sizeof(struct puppets_t));
    return EXIT_FAILURE;
  }
  if (ids_acquire_id(&self->id, puppets->ids)) {
    free(self);
    self = NULL;
    return EXIT_FAILURE;
  }
  self->name = _strdup("<default puppet>");
  if (!self->name) {
    ids_relinquish_id(puppets->ids, self->id);
    puppets->ids = NULL;
    free(self);
    self = NULL;
    return EXIT_FAILURE;
  }
  self->strength = 10;
  self->dexterity = 10;
  self->intelligence = 10;
  self->health = 10;
  self->x = 0;
  self->y = 0;
  self->sg_node = NULL;
  if (os_ensure_free_capacity((void**) & puppets->elements, puppets->size, &puppets->capacity, sizeof(struct puppet_t*), 1)) {
    free(self->name);
    self->name = NULL;
    ids_relinquish_id(puppets->ids, self->id);
    puppets->ids = NULL;
    free(self);
    self = NULL;
    return EXIT_FAILURE;
  }
  puppets->elements[puppets->size++] = self;
  return EXIT_SUCCESS;
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

int puppets_create(struct puppets_t** result, struct sg_list_t* sg_scene, struct ids_t* ids) {
  struct puppets_t* self = malloc(sizeof(struct puppets_t));
  if (!self) {
    fprintf(stderr, "%s:%d: unable to allocate %zu Bytes\n", __FILE__, __LINE__, sizeof(struct puppets_t));
    return EXIT_FAILURE;
  }
  self->ids = ids;
  if (ids_ref(ids)) {
    free(self);
    self = NULL;
    return EXIT_FAILURE;
  }
  self->capacity = 8;
  self->elements = malloc(sizeof(struct puppet_t*) * self->capacity);
  if (!self->elements) {
    ids_relinquish(self->ids);
    self->ids = NULL;
    free(self);
    self = NULL;
    fprintf(stderr, "%s:%d: unable to allocate %zu Bytes\n", __FILE__, __LINE__, sizeof(struct puppet_t*) * 8);
    return EXIT_FAILURE;
  }
  self->size = 0;
  self->sg_scene = sg_scene;
  self->sg_viewer = NULL;
  sg_node_ref((struct sg_node_t*)self->sg_scene);
  *result = self;
  return EXIT_SUCCESS;
}

void puppets_destroy(struct puppets_t* self) {
  while (self->size > 0) {
    struct puppet_t* element = self->elements[--self->size];
    if (element->name) {
      free(element->name);
      element->name = NULL;
    }
    if (element->sg_node) {
      sg_node_unref(element->sg_node);
      element->sg_node = NULL;
    }
    free(element);
  }

  free(self->elements);
  self->elements = NULL;
  self->capacity = 0;

  if (self->sg_viewer) {
    sg_node_unref((struct sg_node_t*)self->sg_viewer);
    self->sg_viewer = NULL;
  }

  sg_node_unref((struct sg_node_t*)self->sg_scene);
  self->sg_scene = NULL;

  ids_relinquish(self->ids);
  self->ids = NULL;

  free(self);
}

int puppets_append(struct puppets_t* self, struct puppet_t* puppet) {
  return EXIT_SUCCESS;
}

int puppets_update(struct puppets_t* self) {
  for (size_t i = 0, n = self->size; i < n; ++i) {
    struct puppet_t* element = self->elements[i];
  }
  return EXIT_SUCCESS;
}

int puppets_render(struct puppets_t* self, int canvas_width, int canvas_height) {
  if (!self->sg_viewer) {
    if (sg_top_down_viewer_create(&self->sg_viewer, canvas_width / 2, canvas_height / 2)) {
      return EXIT_FAILURE;
    }
    if (sg_list_append(self->sg_scene, (struct sg_node_t*)self->sg_viewer)) {
      sg_node_unref((struct sg_node_t*)self->sg_viewer);
      self->sg_viewer = NULL;
      return EXIT_FAILURE;
    }
  } else {
    if (sg_top_down_viewer_set_origin(self->sg_viewer, canvas_width / 2, canvas_height / 2)) {
      return EXIT_FAILURE;
    }
  }
  for (size_t i = 0, n = self->size; i < n; ++i) {
    struct puppet_t* element = self->elements[i];
    if (!element->sg_node) {
      struct sg_color_t* color = NULL;
      if (sg_color_create(&color, 255, 0, 0)) {
        return EXIT_FAILURE;
      }
      if (sg_rectangle_create((struct sg_rectangle_t**) & element->sg_node, element->x - 8, element->y - 8, 16, 16, color)) {
        sg_node_unref((struct sg_node_t*)color);
        color = NULL;
        return EXIT_FAILURE;
      }
      sg_node_unref((struct sg_node_t*)color);
      color = NULL;
      if (sg_list_append(self->sg_scene, element->sg_node)) {
        sg_node_unref((struct sg_node_t*)element->sg_node);
        element->sg_node = NULL;
        return EXIT_FAILURE;
      }
    }
  }
  return EXIT_SUCCESS;
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

struct puppets_t* g_puppets = NULL;
static struct map_t* g_map = NULL;
static struct sg_list_t* g_scene = NULL;

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

static create_scene(struct sg_list_t** result) {
  struct sg_list_t* list_node = NULL;
  if (sg_list_create(&list_node)) {
    return EXIT_FAILURE;
  }
  int x = 64, y = 64;
  {
    struct sg_color_t* color_node;
    if (sg_color_create(&color_node, 0, 0, 0)) {
      sg_node_unref((struct sg_node_t*)list_node);
      list_node = NULL;
      return EXIT_FAILURE;
    }
    struct sg_rectangle_t* rectangle_node;
    if (sg_rectangle_create(&rectangle_node, 0 + x, 0 + y, 164, 164, color_node)) {
      sg_node_unref((struct sg_node_t*)color_node);
      color_node = NULL;
      sg_node_unref((struct sg_node_t*)list_node);
      list_node = NULL;
      return EXIT_FAILURE;
    }
    sg_node_unref((struct sg_node_t*)color_node);
    color_node = NULL;
    if (sg_list_append(list_node, (struct sg_node_t*)rectangle_node)) {
      sg_node_unref((struct sg_node_t*)rectangle_node);
      rectangle_node = NULL;
      sg_node_unref((struct sg_node_t*)list_node);
      list_node = NULL;
      return EXIT_FAILURE;
    }
    sg_node_unref((struct sg_node_t*)rectangle_node);
    rectangle_node = NULL;
  }
  {
    struct sg_color_t* color_node;
    if (sg_color_create(&color_node, 255, 255, 255)) {
      sg_node_unref((struct sg_node_t*)list_node);
      list_node = NULL;
      return EXIT_FAILURE;
    }
  #define PRINT(X, Y, T) \
      { \
        struct sg_text_t* text_node; \
        if (sg_text_create(&text_node, X, Y, T, color_node)) { \
          sg_node_unref((struct sg_node_t*)color_node); \
          color_node = NULL; \
          sg_node_unref((struct sg_node_t*)list_node); \
          list_node = NULL; \
          return EXIT_FAILURE; \
        } \
        if (sg_list_append(list_node, (struct sg_node_t*)text_node)) { \
          sg_node_unref((struct sg_node_t*)text_node); \
          text_node = NULL; \
          sg_node_unref((struct sg_node_t*)list_node); \
          list_node = NULL; \
          return EXIT_FAILURE; \
        } \
        sg_node_unref((struct sg_node_t*)text_node); \
        text_node = NULL; \
      }

    PRINT(0 + x, 20 * 0 + y, "Skeleton");

    PRINT(0 + x, 20 * 1 + y, "Strength:");
    PRINT(120 + x, 20 * 1 + y, "10");

    PRINT(0 + x, 20 * 2 + y, "Dexterity:");
    PRINT(120 + x, 20 * 2 + y, "10");

    PRINT(0 + x, 20 * 3 + y, "Intelligence:");
    PRINT(120 + x, 20 * 3 + y, "10");

    PRINT(0 + x, 20 * 4 + y, "Health:");
    PRINT(120 + x, 20 * 4 + y, "10");

  #undef PRINT

    sg_node_unref((struct sg_node_t*)color_node);
    color_node = NULL;
  }
  *result = list_node;
  return EXIT_SUCCESS;
}

static int _populate_puppets() {
  struct puppet_t* puppet = NULL;
  if (puppet_create(&puppet, g_puppets)) {
    return EXIT_FAILURE;
  }
  return EXIT_SUCCESS;
}

static int _shutdown_window() {
  window_destroy();
  return EXIT_SUCCESS;
}

static int _startup_window() {
  // window
  if (window_create()) {
    return EXIT_FAILURE;
  }

  int width, height;
  struct window_icon_t* icon;

  // big window icon
  if (window_get_big_icon_size(&width, &height)) {
    window_destroy();
    return EXIT_FAILURE;
  }
  if (window_icon_create(&icon, width, height)) {
    window_destroy();
    return EXIT_FAILURE;
  }
  if (window_set_big_icon(icon)) {
    window_icon_unref(icon);
    icon = NULL;
    window_destroy();
    return EXIT_FAILURE;
  }
  window_icon_unref(icon);
  icon = NULL;

  // small window icon
  if (window_get_small_icon_size(&width, &height)) {
    window_destroy();
    return EXIT_FAILURE;
  }
  if (window_icon_create(&icon, width, height)) {
    window_destroy();
    return EXIT_FAILURE;
  }
  if (window_set_small_icon(icon)) {
    window_icon_unref(icon);
    icon = NULL;
    window_destroy();
    return EXIT_FAILURE;
  }
  window_icon_unref(icon);
  icon = NULL;

  return EXIT_SUCCESS;
}

int main(int argc, char **argv) {
  bool error = false;
  if (_startup_window()) {
    return EXIT_FAILURE;
  }
  if (create_scene(&g_scene)) {
    _shutdown_window();
    return EXIT_FAILURE;
  }
  struct ids_t* ids = NULL;
  if (ids_acquire(&ids)) {
    _shutdown_window();
    return EXIT_FAILURE;
  }
  if (puppets_create(&g_puppets, g_scene, ids)) {
    ids_relinquish(ids);
    ids = NULL;
    _shutdown_window();
    return EXIT_FAILURE;
  }
  ids_relinquish(ids);
  ids = NULL;

  if (map_create(&g_map, g_scene)) {
    puppets_destroy(g_puppets);
    g_puppets = NULL;
    _shutdown_window();
    return EXIT_FAILURE;
  }

  // populate the world
  if (_populate_puppets()) {
    map_destroy(g_map);
    g_map = NULL;
    puppets_destroy(g_puppets);
    g_puppets = NULL;
    _shutdown_window();
    return EXIT_FAILURE;
  }

  while (true) {
    bool quit_requested;
    if (app_get_quit_requested(&quit_requested)) {
      error = true;
      break;
    }
    if (quit_requested) {
      break;
    }
    if (window_update()) {
      error = true;
      break;
    }
    int canvas_width, canvas_height;
    if (window_get_canvas_size(&canvas_width, &canvas_height)) {
      error = true;
      break;
    }
    if (puppets_update(g_puppets)) {
      error = true;
      break;
    }
    if (map_render(g_map, canvas_width, canvas_height)) {
      error = true;
      break;
    }
    if (puppets_render(g_puppets, canvas_width, canvas_height)) {
      error = true;
      break;
    }

    if (window_render(g_scene)) {
      error = true;
      break;
    }
  }
  map_destroy(g_map);
  g_map = NULL;
  puppets_destroy(g_puppets);
  g_puppets = NULL;
  sg_node_unref((struct sg_node_t*)g_scene);
  g_scene = NULL;
  _shutdown_window();
  return error ? EXIT_FAILURE : EXIT_SUCCESS;
}
