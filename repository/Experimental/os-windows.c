#include "os-windows.h"

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

#define WIN32_LEAN_AND_MEAN
#include <Windows.h>

#include "os-windows-icon.h"
#include "os-commons.h"

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

struct drawing_context_t {
  HDC hDC;
  int origin_x;
  int origin_y;
};

int draw(struct drawing_context_t* context, struct sg_node_t* node);

int draw_list(struct drawing_context_t* context, struct sg_list_t* node);

int draw_text(struct drawing_context_t* context, struct sg_text_t* node);

int draw_rectangle(struct drawing_context_t* context, struct sg_rectangle_t* node);

int draw_top_down_viewer(struct drawing_context_t* context, struct sg_top_down_viewer_t* node);

int draw(struct drawing_context_t* context, struct sg_node_t* node) {
#define ON(TYPE) \
  { \
    struct sg_node_type_t* a; \
    struct sg_node_type_t* b; \
    if (sg_##TYPE##_the_type(&a)) { \
      return EXIT_FAILURE; \
    } \
    if (sg_node_get_type(&b, (struct sg_node_t*)node)) { \
      return EXIT_FAILURE; \
    } \
    if (a == b) { \
      return draw_##TYPE(context, (struct sg_##TYPE##_t*)node); \
    } \
  }

  ON(list);
  ON(text);
  ON(rectangle);
  ON(top_down_viewer);

  return EXIT_SUCCESS;
}

int draw_list(struct drawing_context_t* context, struct sg_list_t* node) {
  size_t n;
  if (sg_list_get_size(&n, node)) {
    return EXIT_FAILURE;
  }
  for (size_t i = 0; i < n; ++i) {
    struct sg_node_t* child_node = NULL;
    if (sg_list_get_at(&child_node, node, i)) {
      return EXIT_FAILURE;
    }
    if (draw(context, child_node)) {
      return EXIT_FAILURE;
    }
  }
  return EXIT_SUCCESS;
}

int draw_text(struct drawing_context_t* context, struct sg_text_t* node) {
  struct sg_color_t* color_node;
  if (sg_text_get_color(&color_node, node)) {
    return EXIT_FAILURE;
  }
  uint32_t hColor;
  sg_color_pack_xbgr(&hColor, color_node, 0);
  HBRUSH hBrush = CreateSolidBrush(hColor);
  if (!hBrush) {
    return EXIT_FAILURE;
  }
  SetTextAlign(context->hDC, TA_TOP|TA_LEFT);
  SetTextColor(context->hDC, hColor);
  SetBkMode(context->hDC, TRANSPARENT);
  int x, y;
  sg_text_get_position(node, &x, &y);
  char const* p;
  sg_text_get_text(node, &p);
  SIZE extend;
  GetTextExtentPoint32A(context->hDC, p, strlen(p), &extend);
  if (sg_node_set_visual_bounds((struct sg_node_t*)node, x, y, extend.cx, extend.cy)) {
    DeleteObject(hBrush);
    hBrush = NULL;
    return EXIT_FAILURE;
  }
  TextOutA(context->hDC, x, y, p, strlen(p));
  DeleteObject(hBrush);
  hBrush = NULL;
  return EXIT_SUCCESS;
}

int draw_rectangle(struct drawing_context_t* context, struct sg_rectangle_t* node) {
  struct sg_color_t* color_node;
  if (sg_rectangle_get_color(&color_node, node)) {
    return EXIT_FAILURE;
  }
  uint32_t hColor;
  sg_color_pack_xbgr(&hColor, color_node, 0);
  HBRUSH hBrush = CreateSolidBrush(hColor);
  if (!hBrush) {
    return EXIT_FAILURE;
  }
  int x, y, w, h;
  if (sg_rectangle_get_position(node, &x, &y) || sg_rectangle_get_size(node, &w, &h)) {
    DeleteObject(hBrush);
    hBrush = NULL;
    return EXIT_FAILURE;
  }
  RECT r_ = { .left = context->origin_x + x, .top = context->origin_y + y, .right = context->origin_x + x + w, .bottom = context->origin_y + y + h };
  SetBkMode(context->hDC, OPAQUE);
  FillRect(context->hDC, &r_, hBrush);
  DeleteObject(hBrush);
  hBrush = NULL;
  return EXIT_SUCCESS;
}

int draw_top_down_viewer(struct drawing_context_t* context, struct sg_top_down_viewer_t* node) {
  sg_top_down_viewer_get_origin(node, &context->origin_x, &context->origin_y);
  return EXIT_SUCCESS;
}

static const char CLASS_NAME[] = "liminality window class";
static HINSTANCE g_hInstance = NULL;
static bool g_quit_requested = false;

struct window_t {
  HWND hWindow;
  HDC hDeviceContext;
  struct window_icon_t* pBigIcon;
  struct window_icon_t* pSmallIcon;
};

struct back_buffer_t {
  HDC hDeviceContext;
  HBITMAP hBitmap;
  HBITMAP hOldBitmap;
  size_t width;
  size_t height;
};

static struct window_t g_window = { .hWindow = NULL, .hDeviceContext = NULL, .pBigIcon = NULL, .pSmallIcon = NULL };

static struct back_buffer_t g_backBuffer = { .hDeviceContext = NULL, .hBitmap = NULL, .hOldBitmap = NULL, .width = 0, .height = 0 };

static void destroy_backbuffer() {
  if (g_backBuffer.hDeviceContext) {
    SelectObject(g_backBuffer.hDeviceContext, g_backBuffer.hOldBitmap);
    DeleteObject(g_backBuffer.hBitmap);
    g_backBuffer.hBitmap = NULL;
    DeleteDC(g_backBuffer.hDeviceContext);
    g_backBuffer.hDeviceContext = NULL;
  }
}

static int create_backbuffer() {
  RECT clientRectangle;
  GetClientRect(g_window.hWindow, &clientRectangle);
  g_backBuffer.hDeviceContext = CreateCompatibleDC(g_window.hDeviceContext);
  if (!g_backBuffer.hDeviceContext) {
    return EXIT_FAILURE;
  }
  g_backBuffer.hBitmap = CreateCompatibleBitmap(g_window.hDeviceContext, clientRectangle.right - clientRectangle.left, clientRectangle.bottom - clientRectangle.top);
  if (!g_backBuffer.hBitmap) {
    DeleteDC(g_backBuffer.hDeviceContext);
    g_backBuffer.hDeviceContext = NULL;
    return EXIT_FAILURE;
  }
  g_backBuffer.hOldBitmap = SelectObject(g_backBuffer.hDeviceContext, g_backBuffer.hBitmap);
  if (HGDI_ERROR == g_backBuffer.hOldBitmap) {
    DeleteObject(g_backBuffer.hBitmap);
    g_backBuffer.hBitmap = NULL;
    DeleteDC(g_backBuffer.hDeviceContext);
    g_backBuffer.hDeviceContext = NULL;
    return EXIT_FAILURE;
  }
  g_backBuffer.width = clientRectangle.right - clientRectangle.left;
  g_backBuffer.height = clientRectangle.bottom - clientRectangle.top;

  HBRUSH hBrush = CreateSolidBrush(RGB(0, 255, 0));
  FillRect(g_backBuffer.hDeviceContext, &clientRectangle, hBrush);
  DeleteObject(hBrush);

  return EXIT_SUCCESS;
}

static int resize_backbuffer() {
  RECT clientRectangle;
  GetClientRect(g_window.hWindow, &clientRectangle);
  int width = clientRectangle.right - clientRectangle.left;
  int height = clientRectangle.bottom - clientRectangle.top;
  if (width != g_backBuffer.width || height != g_backBuffer.height) {
    destroy_backbuffer();
    return create_backbuffer();
  }
  return EXIT_SUCCESS;
}

static LRESULT CALLBACK WindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
  switch (uMsg) {
    case WM_CLOSE: {
      g_quit_requested = true;
      return 0;
    } break;
    case WM_KEYUP: {
      if (LOWORD(wParam) == VK_ESCAPE) {
        g_quit_requested = true;
      }
      return 0;
    } break;
    case WM_SIZE: {
      int width = LOWORD(lParam);  // Macro to get the low-order word.
      int height = HIWORD(lParam); // Macro to get the high-order word.
      resize_backbuffer();
      return 0;
    } break;
    case WM_PAINT: {
      resize_backbuffer();
      PAINTSTRUCT ps;
      HDC hDC = BeginPaint(hWnd, &ps);
      BitBlt(hDC, 0, 0, g_backBuffer.width, g_backBuffer.height, g_backBuffer.hDeviceContext, 0, 0, SRCCOPY);
      EndPaint(hWnd, &ps);
      return 0;
    } break;
    default: {
      return DefWindowProc(hWnd, uMsg, wParam, lParam);
    } break;
  };
}

int window_create() {
  g_hInstance = GetModuleHandle(NULL);

  // Register the window class.
  WNDCLASS wc = { 0 };

  wc.lpfnWndProc = WindowProc;
  wc.hInstance = g_hInstance;
  wc.lpszClassName = CLASS_NAME;
  wc.hCursor = LoadCursor(NULL, IDC_ARROW); // Prevent the busy cursor from showing up.

  if (!RegisterClass(&wc)) {
    g_hInstance = NULL;
    return EXIT_FAILURE;
  }

  g_window.hWindow =
    CreateWindowEx
      (
        0,                              // Optional window styles.
        CLASS_NAME,                     // Window class
        "Liminality",                   // Window text
        WS_OVERLAPPEDWINDOW,            // Window style
        CW_USEDEFAULT, CW_USEDEFAULT,   // Default position
        CW_USEDEFAULT, CW_USEDEFAULT,   // Default size
        NULL,                           // Parent window
        NULL,                           // Menu
        g_hInstance,                    // Instance handle
        NULL                            // Additional application data
    );

  if (g_window.hWindow == NULL) {
    UnregisterClass(CLASS_NAME, g_hInstance);
    g_hInstance = NULL;
    return EXIT_FAILURE;
  }

  if (!SetProcessDpiAwarenessContext(DPI_AWARENESS_CONTEXT_PER_MONITOR_AWARE_V2)) {
    DestroyWindow(g_window.hWindow);
    g_window.hWindow = NULL;
    UnregisterClass(CLASS_NAME, g_hInstance);
    g_hInstance = NULL;
    return EXIT_FAILURE;
  }

  g_window.hDeviceContext = GetDC(g_window.hWindow);
  if (!g_window.hDeviceContext) {
    DestroyWindow(g_window.hWindow);
    g_window.hWindow = NULL;
    UnregisterClass(CLASS_NAME, g_hInstance);
    g_hInstance = NULL;
    return EXIT_FAILURE;
  }

  if (create_backbuffer()) {
    ReleaseDC(g_window.hWindow, g_window.hDeviceContext);
    g_window.hDeviceContext = NULL;
    DestroyWindow(g_window.hWindow);
    g_window.hWindow = NULL;
    UnregisterClass(CLASS_NAME, g_hInstance);
    g_hInstance = NULL;
    return EXIT_FAILURE;
  }

  ShowWindow(g_window.hWindow, SW_SHOW);

  return EXIT_SUCCESS;
}

int window_update() {
  MSG msg = { 0 };
  while (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)) {
    TranslateMessage(&msg);
    DispatchMessage(&msg);
    if (msg.message == WM_QUIT) {
      g_quit_requested = false;
    }
  }
  return EXIT_SUCCESS;
}

void window_destroy() {
  destroy_backbuffer();
  if (g_window.hDeviceContext) {
    ReleaseDC(g_window.hWindow, g_window.hDeviceContext);
    g_window.hDeviceContext = NULL;
  }
  if (g_window.hWindow) {
    DestroyWindow(g_window.hWindow);
    g_window.hWindow = NULL;
  }
  UnregisterClass(CLASS_NAME, g_hInstance);
  g_hInstance = NULL;
  if (g_window.pSmallIcon) {
    window_icon_unref(g_window.pSmallIcon);
    g_window.pSmallIcon = NULL;
  }
  if (g_window.pBigIcon) {
    window_icon_unref(g_window.pBigIcon);
    g_window.pBigIcon = NULL;
  }
}

int window_get_canvas_size(int* width, int* height) {
  RECT r;
  GetClientRect(g_window.hWindow, &r);
  *width = r.right - r.left;
  *height = r.bottom - r.top;
  return EXIT_SUCCESS;
}

int window_render(struct sg_list_t* list) {
  RECT rect = { .left = 0, .top = 0, .right = g_backBuffer.width, .bottom = g_backBuffer.height };

  HBRUSH hBrush = CreateSolidBrush(RGB(0, 0, 0));
  FillRect(g_backBuffer.hDeviceContext, &rect, hBrush);
  DeleteObject(hBrush);
  hBrush = NULL;

  struct drawing_context_t context = { .hDC = g_backBuffer.hDeviceContext, .origin_x = g_backBuffer.width / 2, .origin_y = g_backBuffer.height / 2 };
  draw(&context, (struct sg_node_t*)list);

  BitBlt(g_window.hDeviceContext, 0, 0, g_backBuffer.width, g_backBuffer.height, g_backBuffer.hDeviceContext, 0, 0, SRCCOPY);

  return EXIT_SUCCESS;
}

int window_get_big_icon_size(int* width, int* height) {
  *width = GetSystemMetrics(SM_CXICON);
  *height = GetSystemMetrics(SM_CYICON);
  return EXIT_SUCCESS;
}

int window_get_small_icon_size(int* width, int* height) {
  *width = GetSystemMetrics(SM_CXSMICON);
  *height = GetSystemMetrics(SM_CYSMICON);
  return EXIT_SUCCESS;
}

int window_set_big_icon(struct window_icon_t* icon) {
  if (window_icon_ref(icon)) {
    return EXIT_FAILURE;
  }
  if (g_window.pBigIcon) {
    window_icon_unref(g_window.pBigIcon);
    g_window.pBigIcon = NULL;
  }
  g_window.pBigIcon = icon;
  SendMessage(g_window.hWindow, WM_SETICON, ICON_BIG, (LPARAM)g_window.pBigIcon->hIcon);
  return EXIT_SUCCESS;
}

int window_set_small_icon(struct window_icon_t* icon) {
  if (window_icon_ref(icon)) {
    return EXIT_FAILURE;
  }
  if (g_window.pSmallIcon) {
    window_icon_unref(g_window.pSmallIcon);
    g_window.pSmallIcon = NULL;
  }
  g_window.pSmallIcon = icon;
  SendMessage(g_window.hWindow, WM_SETICON, ICON_SMALL, (LPARAM)g_window.pSmallIcon->hIcon);
  return EXIT_SUCCESS;
}

int app_get_quit_requested(bool* result) {
  *result = g_quit_requested;
  return EXIT_SUCCESS;
}

int app_set_quit_requested(bool quit_requested) {
  g_quit_requested = quit_requested;
  return EXIT_SUCCESS;
}

