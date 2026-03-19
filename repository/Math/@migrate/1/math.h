/// @file dx/core/math.h
/// @copyright Copyright (c) 2022-2023 Michael Heilmann. All rights reserved.
/// @author Michael Heilmann (michaelheilmann@primordialmachine.com)
#if !defined(DX_MATH_H_INCLUDED)
#define DX_MATH_H_INCLUDED

#include "dx/core/configuration.h"
#include "dx/core/core.h"

typedef struct DX_VEC3 DX_VEC3;
typedef struct DX_VEC4 DX_VEC4;
typedef struct DX_RGB_F32 DX_RGB_F32;
typedef struct DX_RGBA_F32 DX_RGBA_F32;

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

typedef struct DX_RGB_F32 {
  dx_f32 r;
  dx_f32 g;
  dx_f32 b;
} DX_RGB_F32;

static inline void dx_rgb_f32_set(DX_RGB_F32* c, dx_f32 r, dx_f32 g, dx_f32 b) {
  c->r = r;
  c->g = g;
  c->b = b;
}

void dx_rgb_f32_lerp(DX_RGB_F32 const* a, DX_RGB_F32 const* b, dx_f32 t, DX_RGB_F32* c);

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

typedef struct DX_RGBA_F32 {
  dx_f32 r;
  dx_f32 g;
  dx_f32 b;
  dx_f32 a;
} DX_RGBA_F32;

static inline void dx_rgba_f32_set(DX_RGBA_F32* c, dx_f32 r, dx_f32 g, dx_f32 b, dx_f32 a) {
  c->r = r;
  c->g = g;
  c->b = b;
  c->a = a;
}

void dx_rgba_f32_lerp(DX_RGBA_F32 const* a, DX_RGBA_F32 const* b, dx_f32 t, DX_RGBA_F32* c);

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

typedef struct DX_BGR_N8 {
  dx_n8 b;
  dx_n8 g;
  dx_n8 r;
} DX_BGR_N8;

static inline void dx_bgr_n8_set(DX_BGR_N8* c, dx_n8 b, dx_n8 g, dx_n8 r) {
  c->b = b;
  c->g = g;
  c->r = r;
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

typedef struct DX_RGB_N8 {
  dx_n8 r;
  dx_n8 g;
  dx_n8 b;
} DX_RGB_N8;

static inline void dx_rgb_u8_set(DX_RGB_N8* c, dx_n8 r, dx_n8 g, dx_n8 b) {
  c->r = r;
  c->g = g;
  c->b = b;
}

static inline void dx_rgb_n8_to_rgba_f32(DX_RGB_N8 const* source, dx_f32 a, DX_RGBA_F32* target) {
  target->r = ((dx_f32)source->r) / 255.f;
  target->g = ((dx_f32)source->g) / 255.f;
  target->b = ((dx_f32)source->b) / 255.f;
  target->a = a;
}

void dx_rgb_u8_lerp(DX_RGB_N8 const* a, DX_RGB_N8 const* b, dx_f32 t, DX_RGB_N8* c);

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

// Symbolic constant for the dx_f32 representation of PI.
#define DX_PI_F32 3.1415926f

// @brief Convert an angle in degrees into the corresponding angle in radians.
// @param a The angle in degrees.
// @return The corresponding angle in radians.
static inline dx_f32 dx_deg_to_rad(dx_f32 x) {
  return (x / 180.f) * DX_PI_F32;
}

// @brief Clamp a value to the range [0,1].
// @param x The value to be clamped.
// @return x clamped.
static inline dx_f32 dx_clamp(dx_f32 x) {
  if (x < 0.f) return 0.f;
  else if (x > 1.f) return 1.f;
  else return x;
}

static inline void dx_lerp(dx_f32 *result, dx_f32 start, dx_f32 end, dx_f32 t) {
  t = dx_clamp(t);
  if (t == 0.f) {
    *result = start;
  } else if (t == 1.f) {
    *result = end;
  } else {
    *result = (1.f - t) * start + t * end;
  }
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

typedef struct DX_VEC2_F32 {
  dx_f32 e[2];
} DX_VEC2_F32;

static inline void dx_vec2_f32_set(DX_VEC2_F32* v, dx_f32 x, dx_f32 y) {
  v->e[0] = x;
  v->e[1] = y;
}

/// @ingroup math
/// @brief Compute the sum of two vectors.
/// @param w Pointer to a DX_VEC2 object.
/// @param u Pointer to a DX_VEC2 object.
/// The object's values represent the augend (aka the 1st operand).
/// @param v Pointer toa DX_VEC2 object.
/// The object's values represent the addend (aka the 2nd operand).
/// @remarks @a w, @a u, and @a v all may refer to the same object.
/// @post <code>*w/<code> was assigned the values of the sum vector.
void dx_vec2_f32_add3(DX_VEC2_F32* w, DX_VEC2_F32 const* u, DX_VEC2_F32 const* v);

/// @ingroup math
/// @brief Compute the difference of two vectors.
/// @param w Pointer to a DX_VEC2 object.
/// @param u Pointer to a DX_VEC2 object.
/// The object's values represent the vector that is the minuend (aka the 1st operand).
/// @param v Pointer to a DX_VEC2 object.
/// The object's values represent hte vector that is the the subtrahend (aka the 2nd operand).
/// @remarks @a w, @a u, and @a v all may refer to the same object.
/// @post <code>*w/<code> was assigned the values of the difference vector.
void dx_vec2_f32_sub3(DX_VEC2_F32* w, DX_VEC2_F32 const* u, DX_VEC2_F32 const* v);

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

typedef struct DX_VEC3 {
  dx_f32 e[3];
} DX_VEC3;

static inline void dx_vec3_set(DX_VEC3* v, dx_f32 x, dx_f32 y, dx_f32 z) {
  v->e[0] = x;
  v->e[1] = y;
  v->e[2] = z;
}

static inline dx_bool dx_vec3_are_equal(DX_VEC3 const* u, DX_VEC3 const* v) {
  return u->e[0] == v->e[0]
      && u->e[1] == v->e[1]
      && u->e[2] == v->e[2];
}

// get the squared length of a vector
// @param v the vector
// @return the squared length of the vector
dx_f32 dx_vec3_sql(DX_VEC3 const* v);

// Compute a normalized vector.
// @param v the vector receiving the normalized vector
// @param u the vector to normalize
// @remarks The result is the normalized vector of the vector to be normalized if the vector to be normalized is a non-zero vector.
// Otherwise the result is the zero vector.
// @a v and @a u may refer to the same object.
void dx_vec3_norm(DX_VEC3* v, DX_VEC3 const* u);



/// @ingroup math
/// @brief Compute the cross product of two vectors.
/// @param w Pointer to a DX_VEC3 object.
/// @param u Pointer to a DX_VEC3 object.
/// The object's values represent the vector, that is the 1st operand.
/// @param v Pointer to a DX_VEC3 object.
/// The object's values represent the vector, that is the 2nd operand.
/// @remarks @a w, @a u, and @a v all may refer to the same object.
/// @post <code>*w/<code> was assigned the values of the cross product vector.
void dx_vec3_cross(DX_VEC3* w, DX_VEC3 const* u, DX_VEC3 const* v);


/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

typedef struct DX_VEC4 {
  dx_f32 e[4];
} DX_VEC4;

static inline void dx_vec4_set(DX_VEC4* v, dx_f32 x, dx_f32 y, dx_f32 z, dx_f32 w) {
  v->e[0] = x;
  v->e[1] = y;
  v->e[2] = z;
  v->e[3] = w;
}

static inline dx_bool dx_vec4_are_equal(DX_VEC4 const* u, DX_VEC4 const* v) {
  return u->e[0] == v->e[0]
      && u->e[1] == v->e[1]
      && u->e[2] == v->e[2]
      && u->e[3] == v->e[3];
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

// A 4x4 dx_f32 matrix POD.
typedef struct DX_MAT4 {
  // index i,j denotes i-th row and j-th colmn
  dx_f32 e[4][4];
} DX_MAT4;


/// Compute the product of two matrices.
/// @param c Pointer to a DX_MAT4 object.
/// @param a Pointer to a DX_MAT4 object.
/// The object's values represent the matrix that is the the multiplier (aka the 1st factor aka the 1st operand)
/// @param b Pointer to a DX_MAT4 object.
/// The object's values represent the matrix that is the multiplicand (aka the 2nd factor aka the 2nd operand).
/// @remarks @a c, @a b, and @a b all may refer to the same object.
/// @post <code>*c/<code> was assigned the values of the product matrix.
void dx_mat4_mul3(DX_MAT4* c, DX_MAT4 const* a, DX_MAT4 const* b);

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

/// @ingroup math
/// Transform a position vector.
/// @param u Pointer to a DX_VEC3 object. The object receives the transformed position vector.
/// @param v Pointer to a DX_VEC3 object. The object represents the position to transform.
/// @param m Pointer to a DX_MAT4 object. The object represents the transformation matrix.
void dx_transform_point(DX_VEC3* u, DX_VEC3 const* v, DX_MAT4 const* m);

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

/// @brief An offset in 2D space.
typedef struct DX_OFFSET2_F32 {
  dx_f32 x;
  dx_f32 y;
} DX_OFFSET2_F32;

static inline void dx_offset2_f32_set(DX_OFFSET2_F32* a, dx_f32 x, dx_f32 y) {
  a->x = x;
  a->y = y;
}

/// @brief An extend in 2D space.
typedef struct DX_EXTEND2_F32 {
  dx_f32 x;
  dx_f32 y;
} DX_EXTEND2_F32;

static inline void dx_extend2_f32_set(DX_EXTEND2_F32* a, dx_f32 x, dx_f32 y) {
  a->x = x;
  a->y = y;
}

typedef struct DX_RECT2_F32 {
  /// @brief An offset in 2D.
  DX_OFFSET2_F32 offset;
  /// @brief An extend in 2D.
  DX_EXTEND2_F32 extend;
} DX_RECT2_F32;

static inline void dx_rect2_f32_set(DX_RECT2_F32* a, dx_f32 left, dx_f32 bottom, dx_f32 right, dx_f32 top) {
  dx_offset2_f32_set(&a->offset, left, bottom);
  dx_extend2_f32_set(&a->extend, right - left, top - bottom);
}

static inline void dx_rect2_f32_set2(DX_RECT2_F32* a, dx_f32 left, dx_f32 bottom, dx_f32 width, dx_f32 height) {
  dx_offset2_f32_set(&a->offset, left, bottom);
  dx_extend2_f32_set(&a->extend, width, height);
}

static inline dx_f32 dx_rect2_f32_get_left(DX_RECT2_F32 const* a) {
  if (a->extend.x < 0.f) {
    return a->offset.x + a->extend.x;
  } else {
    return a->offset.x;
  }
}

static inline dx_f32 dx_rect2_f32_get_right(DX_RECT2_F32 const* a) {
  if (a->extend.x > 0.f) {
    return a->offset.x + a->extend.x;
  } else {
    return a->offset.x;
  }
}

static inline dx_f32 dx_rect2_f32_get_bottom(DX_RECT2_F32 const* a) {
  if (a->extend.y < 0.f) {
    return a->offset.y + a->extend.y;
  } else {
    return a->offset.y;
  }
}

static inline dx_f32 dx_rect2_f32_get_top(DX_RECT2_F32 const* a) {
  if (a->extend.y > 0.f) {
    return a->offset.y + a->extend.y;
  } else {
    return a->offset.y;
  }
}

static inline void dx_rect2_f32_union(DX_RECT2_F32* a, DX_RECT2_F32 const* x, DX_RECT2_F32 const* y) {
#pragma push_macro("MIN")
#pragma push_macro("MAX")
#define MIN(x,y) (x) < (y) ? (x) : (y)
#define MAX(x,y) (x) > (y) ? (x) : (y)

  dx_f32 l = MIN(dx_rect2_f32_get_left(x), dx_rect2_f32_get_left(y));
  dx_f32 b = MIN(dx_rect2_f32_get_bottom(x), dx_rect2_f32_get_bottom(y));
  dx_f32 r = MAX(dx_rect2_f32_get_right(x), dx_rect2_f32_get_right(y));
  dx_f32 t = MAX(dx_rect2_f32_get_top(x), dx_rect2_f32_get_top(y));

  a->offset.x = l;
  a->offset.y = b;
  a->extend.x = r - l;
  a->extend.y = t - b;

#undef MAX
#undef MIN
#pragma pop_macro("MAX")
#pragma pop_macro("MIN")
}

static inline void dx_rect2_f32_translate(DX_RECT2_F32* r, DX_VEC2_F32 const* t) {
  r->offset.x += t->e[0];
  r->offset.y += t->e[1];
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

#if defined(DX_MATH_WITH_TESTS) && 1 == DX_MATH_WITH_TESTS
Core_Result dx_math_tests();
#endif

#endif // DX_MATH_H_INCLUDED
