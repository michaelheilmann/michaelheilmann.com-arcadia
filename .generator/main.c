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

#include "file.h"
#include "stringbuffer.h"

#include "arcadia/arms1.h"
#include "arcadia/r1.h"

#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#define WIN32_LEAN_AND_MEAN
#include <windows.h>

static void g_create_directory(StringBuffer* path) {
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
  File* file = File_create();
  file->fd = fopen(fn->p, "wb");
  if (!file->fd) {
    R_setStatus(R_Status_FileSystemOperationFailed);
    R_jump();
  }
  fwrite(contents->p, 1, contents->sz, file->fd);
  fclose(file->fd);
  file->fd = NULL;
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
  File* file = File_create();
  file->fd = fopen(fn->p, "wb");
  if (!file->fd) {
    R_setStatus(R_Status_FileSystemOperationFailed);
    R_jump();
  }
  fwrite(contents->p, 1, contents->sz, file->fd);
  fclose(file->fd);
  file->fd = NULL;
}

static void g_main(int argc, char** argv) {
  test1();
  g_write_index_html();
  g_write_error_html();
}

static void registerType(char const* name, size_t nameLength, Arms_VisitCallbackFunction* visit, Arms_FinalizeCallbackFunction* finalize) {
  Arms_Status status;
  status = Arms_registerType(name, nameLength, visit, finalize);
  switch (status) {
    case Arms_Status_Success: {
      return;
    } break;
    case Arms_Status_AllocationFailed: {
      R_setStatus(R_Status_AllocationFailed);
    } break;
    case Arms_Status_ArgumentValueInvalid: {
      R_setStatus(R_Status_ArgumentValueInvalid);
    } break;
    case Arms_Status_OperationInvalid: 
    case Arms_Status_TypeExists: {
      R_setStatus(Arms_Status_OperationInvalid);
    } break;
    case Arms_Status_TypeNotExists:
    default: {
      // This should not happen.
      R_setStatus(Arms_Status_OperationInvalid);
    } break;
  };
}

static void registerTypes() {
  _File_registerType();
  _StringBuffer_registerType();
}

int main(int argc, char** argv) {
  Arms_Status armsStatus = Arms_startup();
  if (Arms_Status_Success != armsStatus) {
    return EXIT_FAILURE;
  }
  R_JumpTarget jumpTarget;
  R_pushJumpTarget(&jumpTarget);
  if (R_JumpTarget_save(&jumpTarget)) {
    registerTypes();
    g_main(argc, argv);
    R_popJumpTarget();
  }
  R_Status status = R_getStatus();
  armsStatus = Arms_run();
  if (Arms_Status_Success != armsStatus) {
    Arms_shutdown();
    return EXIT_FAILURE;
  }
  armsStatus = Arms_shutdown();
  if (Arms_Status_Success != armsStatus) {
    return EXIT_FAILURE;
  }
  return status ? EXIT_FAILURE : EXIT_SUCCESS;
}
