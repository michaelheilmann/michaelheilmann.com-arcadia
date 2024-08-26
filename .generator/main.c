// The author of this software is Michael Heilmann (contact@michaelheilmann.com).
//
// Copyright(c) 2024 Michael Heilmann (contact@michaelheilmann.com).
//
// Permission to use, copy, modify, and distribute this software for any
// purpose without fee is hereby granted, provided that this entire notice
// is included in all copies of any software which is or includes a copy
// or modification of this software and in all copies of the supporting
// documentation for such software.
//
// THIS SOFTWARE IS BEING PROVIDED "AS IS", WITHOUT ANY EXPRESS OR IMPLIED
// WARRANTY.IN PARTICULAR, NEITHER THE AUTHOR NOR LUCENT MAKES ANY
// REPRESENTATION OR WARRANTY OF ANY KIND CONCERNING THE MERCHANTABILITY
// OF THIS SOFTWARE OR ITS FITNESS FOR ANY PARTICULAR PURPOSE.

// Last modified: 2024-08-29

#include "file.h"

#include "stringbuffer.h"

#include "arms1.h"
#include "r.h"

#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#define WIN32_LEAN_AND_MEAN
#include <windows.h>

/// @todo This code fails if an UTF-8 Byte sequence is split between to read operations.
static StringBuffer* File_getFileContents(StringBuffer* path) {
  R_FileHandle* file = R_FileHandle_create();
  R_FileHandle_openForReading(file, path->p);
  StringBuffer* w = StringBuffer_create();
  char p[5012]; size_t n;
  do {
    R_FileHandle_read(file, p, 5012, &n);
    if (n > 0) {
      StringBuffer_append_pn(w, p, n);
    }
  } while (n);
  R_FileHandle_close(file);
  return w;   
}

static void R_SetFileContents(StringBuffer* path, StringBuffer* contents) {
  R_FileHandle* file = R_FileHandle_create();
  R_FileHandle_openForWriting(file, path->p);
  R_FileHandle_write(file, contents->p, contents->sz);
  R_FileHandle_close(file);
}

static void R_CreateDirectory(StringBuffer* path) {
  if (!CreateDirectory(path->p, NULL)) {
    R_setStatus(R_Status_FileSystemOperationFailed);
    R_jump();
  }
}

static inline void SWAP_P(void** x, void** y) {
  void* t = *x;
  *x = *y;
  *y = t;
}

static inline void SWAP_SZ(size_t* x, size_t* y) {
  size_t t = *x;
  *x = *y;
  *y = t;
}

// replace '/' by '\'
// replace '\\' by '\'
void g_fs_normalize(StringBuffer* path) {
  StringBuffer*temporary = StringBuffer_create();
  char const* start = path->p;
  char const* end = path->p + path->sz;
  char const* p = start;
  char const* q = start;
  while (q != end) {
    if (*q <= 0x80) {
      // replace '/' by '\'.
      // replace '\\' by '\'.
      if ('\\' == *q || '/' == *q) {
        if (p != q) {
          StringBuffer_append_pn(temporary, p, q - p);
          p = q;
        }
        char y = '\\';
        StringBuffer_append_pn(temporary, &y, 1);
        do {
          q++;
        } while (q != end && ('\\' == *q || '/' == *q));
        p = q;
      } else {
        q++;
      }
    } else {
      // only utf8 strings with unicode symbols encoded in one byte are currently supported.
      R_setStatus(R_Status_ArgumentValueInvalid);
      R_jump();
    }
  }
  if (p != q) {
    StringBuffer_append_pn(temporary, p, q - p);
    p = q;
  }
  SWAP_P(&path->p, &temporary->p);
  SWAP_SZ(&path->sz, &temporary->sz);
  SWAP_SZ(&path->cp, &temporary->cp);
}

void test1() {
  StringBuffer* received = StringBuffer_create();
  StringBuffer* expected = StringBuffer_create();
  
#define TEST(RECEIVED, EXPECTED) \
  { \
    StringBuffer_clear(received); \
    StringBuffer_clear(expected); \
    StringBuffer_append_pn(received, RECEIVED, sizeof(RECEIVED) - 1); \
    StringBuffer_append_pn(expected, EXPECTED, sizeof(EXPECTED) - 1); \
    g_fs_normalize(received); \
    if (!StringBuffer_areEqual(received, expected)) { \
      R_setStatus(R_Status_ArgumentValueInvalid); /*@todo Add and use R_Status_TestFailed);*/\
      R_jump(); \
    } \
  }

  TEST("", "");
  TEST("\\", "\\");
  TEST("/", "\\");
  TEST("a\\b\\\\c/\\d", "a\\b\\c\\d");

#undef TEST
}

static void g_write_index_html() {
  StringBuffer* fn = StringBuffer_create(&fn);
  StringBuffer_append_pn(fn, PROJECT_DIRECTORY, sizeof(PROJECT_DIRECTORY) - 1);
  if (!StringBuffer_endsWith_pn(fn, "/", sizeof("/") - 1)) {
    StringBuffer_append_pn(fn, "/", sizeof("/") - 1);
  }
  StringBuffer_append_pn(fn, "index.html", sizeof("index.html") - 1);
  StringBuffer_append_pn(fn, "", sizeof(""));
  g_fs_normalize(fn);
  StringBuffer* contents = StringBuffer_create();

#define EMIT(TEXT) \
  StringBuffer_append_pn(contents, TEXT, sizeof(TEXT) - 1);

  EMIT("<!DOCTYPE html>");
  EMIT("<html class='my-theme-1' lang='en'>");
  EMIT("<head>");
  EMIT("<meta charset='utf-8'>");
  EMIT("<meta name='viewport' content='width=device-width, initial-scale=1'>");
  EMIT("<link rel='canonical' href='https://michaelheilmann.com/' />");

  EMIT("<link rel='icon' type='image/x-icon' href='https://michaelheilmann.com/assets/favicon/512x512.svg'>");

  // Crap specific to Safari. SVG must be single color with transparent background.
  EMIT("<link rel='mask-icon' href='https://michaelheilmann.com/assets/favicon/safari-mask-icon-512x512.svg' color = '#000000'>");

  // Crap specific to iOS. PNG must be 180 x 180 pixels. color attribute is obsolete.
  EMIT("<link rel='apple-touch-icon' href='https://michaelheilmann.com/assets/favicon/apple-touch-icon-180x180.png'>");

  EMIT("<link rel='stylesheet' href='https://michaelheilmann.com/assets/index.css'>");
  EMIT("<title>Michael Heilmann Contact Information</title>");
  EMIT("</head>");
  EMIT("<body style='font-size: 2rem; display: flex; flex-direction: column; min-width: max(64rem, 100vw); min-height: max(32rem, 100vh); width: max(64rem, 100vw); height: max(32rem, 100vh);'>");
  /* flex-direction: row ~ from left to right*/
  EMIT("<header style='flex-grow: 0; display: flex; flex-direction: row;'>");
  EMIT("<div style='flex-grow:0; display: flex; flex-direction: column; padding-left: 2rem; padding-top: 2rem;'>")
    EMIT("<div>michael heilmann</div>");
  EMIT("<div>information system architect</div>");
  EMIT("</div>")
    EMIT("<div style='flex-grow:1;'></div>");
  EMIT("<div style='flex-grow:0;'></div>");
  EMIT("</header>");
  EMIT("<main style='flex-grow: 1; display: flex; flex-direction: row;'>");
  EMIT("</main>");
  /* flex-direction: row ~ from left to right*/
  EMIT("<footer style='flex-grow: 0; display: flex; flex-direction: row;'>");
  EMIT("<div style='flex-grow:0; padding-left: 2rem; padding-bottom: 2rem;'>");
  EMIT("<div style='display: flex; flex-direction: row'>");
  EMIT("<a style='margin-right: 2rem; font-size: small; text-decoration: none;' href = 'https://michaelheilmann.com/repository/arms1'>ARMS</a>");
  EMIT("<a style='font-size: small; text-decoration: none;' href = 'https://michaelheilmann.com/repository/r1'>R</a>");
  EMIT("</div>");
  EMIT("</div>");
  EMIT("<div style='flex-grow:1;'></div>");
  EMIT("<div style='flex-grow:0; padding-right: 2rem; padding-bottom: 2rem;'><a style='text-decoration: none;' href='mailto:contact@michaelheilmann.com'>contact@michaelheilmann.com</a></div>");
  EMIT("</footer>");
  EMIT("</body>");
  EMIT("</html>");

#undef EMIT
  R_FileHandle* file = R_FileHandle_create();
  R_FileHandle_openForWriting(file, fn->p);
  fwrite(contents->p, 1, contents->sz, file->fd);
  R_FileHandle_close(file);
  file = NULL;
}

static void g_write_error_html() {
  StringBuffer* fn = StringBuffer_create();
  StringBuffer_append_pn(fn, PROJECT_DIRECTORY, sizeof(PROJECT_DIRECTORY) - 1);
  if (!StringBuffer_endsWith_pn(fn, "/", sizeof("/") - 1)) {
    StringBuffer_append_pn(fn, "/", sizeof("/") - 1);
  }
  StringBuffer_append_pn(fn, "error.html", sizeof("error.html") - 1);
  StringBuffer_append_pn(fn, "", sizeof("")); // Append the zero terminator.
  g_fs_normalize(fn);
  StringBuffer* contents = StringBuffer_create();

#define EMIT(TEXT) \
  StringBuffer_append_pn(contents, TEXT, sizeof(TEXT) - 1);

  EMIT("<!DOCTYPE html>");
  EMIT("<html class='my-theme-1' lang='en'>");
  EMIT("<head>");
  EMIT("<meta charset='utf-8'>");
  EMIT("<meta name='viewport' content='width=device-width, initial-scale=1'>");
  EMIT("<link rel='icon' type='image/x-icon' href='https://michaelheilmann.com/assets/favicon/512x512.svg'>");

  // Crap specific to Safari. SVG must be single color with transparent background.
  EMIT("<link rel='mask-icon' href='https://michaelheilmann.com/assets/favicon/safari-mask-icon-512x512.svg' color = '#000000'>");

  // Crap specific to iOS. PNG must be 180 x 180 pixels. color attribute is obsolete.
  EMIT("<link rel='apple-touch-icon' href='https://michaelheilmann.com/assets/favicon/apple-touch-icon-180x180.png'>");

  EMIT("<link rel='stylesheet' href='https://michaelheilmann.com/assets/index.css'>");
  EMIT("<title>Something went wrong ...</title>");
  EMIT("</head>");
  EMIT("<body style='font-size: 2rem; display: flex; flex-direction: column; min-width: max(64rem, 100vw); min-height: max(32rem, 100vh); width: max(64rem, 100vw); height: max(32rem, 100vh);'>");
  /* flex-direction: row ~ from left to right*/
  EMIT("<header style='flex-grow: 0; display: flex; flex-direction: row;'>");
  EMIT("</header>");
  EMIT("<main style='flex-grow: 1; display: flex; flex-direction: row;'>");
  EMIT("<div style='padding-left: 2rem; padding-top: 2rem;'>Something went wrong ...</div>")
  EMIT("</main>");
  /* flex-direction: row ~ from left to right*/
  EMIT("<footer style='flex-grow: 0; display: flex; flex-direction: row;'>");
  EMIT("</footer>");
  EMIT("</body>");
  EMIT("</html>");

#undef EMIT
  R_FileHandle* file = R_FileHandle_create();
  R_FileHandle_openForWriting(file, fn->p);
  fwrite(contents->p, 1, contents->sz, file->fd);
  R_FileHandle_close(file);
  file = NULL;
}

static void main1(int argc, char** argv) {
  test1();
  g_write_index_html();
  g_write_error_html();
}

static void registerTypes() {
  _R_FileHandle_registerType();
  _R_ByteBuffer_registerType();
  _StringBuffer_registerType();
}

int main(int argc, char** argv) {
  R_Status status[2];
  status[0] = R_startup();
  if (status[0]) {
    return EXIT_FAILURE;
  }
  R_JumpTarget jumpTarget;
  R_pushJumpTarget(&jumpTarget);
  if (R_JumpTarget_save(&jumpTarget)) {
    registerTypes();
    main1(argc, argv);
    R_popJumpTarget();
  }
  status[0] = R_getStatus();
  status[1] = R_shutdown();
  if (status[1] || status[0]) {
    return EXIT_FAILURE;
  }
  return EXIT_SUCCESS;
}
