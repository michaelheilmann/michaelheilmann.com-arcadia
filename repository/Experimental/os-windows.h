#if !defined(OS_WINDOWS_H_INCLUDED)
#define OS_WINDOWS_H_INCLUDED

// bool, true, false
#include <stdbool.h>

// uint8_t
#include <stdint.h>

#include "sg.h"
#include "os-windows-icon.h"

int window_create();

int window_update();

void window_destroy();

int window_get_canvas_size(int *width, int *height);

int window_render(struct sg_list_t* list);

/**
 * @brief Get the size (width and height), in pixels, required for a big window icon.
 * @param width A pointer to a <code>int</code> variable.
 * @param height A pointer to a <code>int</code> variable.
 * @return EXIT_SUCCESS on success. EXIT_FAILURE on failure.
 * @post On Success, <code>*width</code> was assigned the width, in pixels, required for a big window icon and <code>*height</code> was assigned the height, in pixels, required for a big window icon.
 */
int window_get_big_icon_size(int *width, int *height);

/**
 * @brief Get the size (width and height), in pixels, of a small window icon.
 * @param width A pointer to a <code>int</code> variable.
 * @param height A pointer to a <code>int</code> variable.
 * @return EXIT_SUCCESS on success. EXIT_FAILURE on failure.
 * @post On Success, <code>*width</code> was assigned the width, in pixels, required for a big window icon and <code>*height</code> was assigned the height, in pixels, required for a big window icon.
 */
int window_get_small_icon_size(int *width, int *height);

int window_set_big_icon(struct window_icon_t* icon);
int window_set_small_icon(struct window_icon_t* icon);

/* Get if the application was requested to quit. */
int app_get_quit_requested(bool* result);

/* Set if the application was requested to quit. */
int app_set_quit_requested(bool quit_requested);

#endif // OS_WINDOWS_H_INCLUDED
