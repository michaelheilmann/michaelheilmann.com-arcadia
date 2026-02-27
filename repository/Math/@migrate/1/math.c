#include "dx/core/math.h"

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

// sinf, sin
// cosf, cos
#include <math.h>

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

void dx_rgb_u8_lerp(DX_RGB_N8 const* a, DX_RGB_N8 const* b, dx_f32 t, DX_RGB_N8* c) {
  t = dx_clamp(t);
  if (t == 0.f) {
    *c = *a;
  } else if (t == 1.f) {
    *c = *b;
  } else {
    dx_f32 s = 1.f - t;
    c->r = s * ((dx_f32)a->r) + t * ((dx_f32)b->r);
    c->g = s * ((dx_f32)a->g) + t * ((dx_f32)b->g);
    c->b = s * ((dx_f32)a->b) + t * ((dx_f32)b->b);
  }
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

void dx_vec3_norm(DX_VEC3* u, DX_VEC3 const* v) {
  dx_f32 sql = dx_vec3_sql(v);
  if (sql == 0.f) {
    u->e[0] = 0.f;
    u->e[1] = 0.f;
    u->e[2] = 0.f;
    return;
  }
  dx_f32 l = sqrtf(sql);
  u->e[0] = v->e[0] / l;
  u->e[1] = v->e[1] / l;
  u->e[2] = v->e[2] / l;
}

void dx_vec3_cross(DX_VEC3* w, DX_VEC3 const* u, DX_VEC3 const* v) {
  dx_f32 t[3];
  t[0] = u->e[1] * v->e[2] - u->e[2] * v->e[1];
  t[1] = u->e[2] * v->e[0] - u->e[0] * v->e[2];
  t[2] = u->e[0] * v->e[1] - u->e[1] * v->e[0];
  w->e[0] = t[0];
  w->e[1] = t[1];
  w->e[2] = t[2];
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

void dx_mat4_mul3(DX_MAT4* c, DX_MAT4 const* a, DX_MAT4 const* b) {
  if (c!= a && c != b) {
    for (Core_Size i = 0; i < 4; ++i) {
      for (Core_Size j = 0; j < 4; ++j) {
        c->e[i][j] = 0.f;
        for (Core_Size k = 0; k < 4; ++k) {
          c->e[i][j] += a->e[i][k] * b->e[k][j];
        }
      }
    }
  } else {
    dx_f32 t[4][4];

    for (Core_Size i = 0; i < 4; ++i) {
      for (Core_Size j = 0; j < 4; ++j) {
        t[i][j] = 0.f;
        for (Core_Size k = 0; k < 4; ++k) {
          t[i][j] += a->e[i][k] * b->e[k][j];
        }
      }
    }
    for (Core_Size i = 0; i < 4; ++i) {
      for (Core_Size j = 0; j < 4; ++j) {
        c->e[i][j] = t[i][j];
      }
    }
  }
}

/// Assign this matrix the value a of a view matrix.
/// @param source the position vector of the point at which the viewer is located
/// @param target the position vector of the point at which the viewer is looking at
/// @param uo the direction vector indicating the upward direction of the viewer
/// @remarks
/// This function constructs a view matrix <code>V</code>given
/// - the position the viewer is located at <code>source</code>,
/// - the position the viewer is looking at <code>target</code>, and
/// - the vector indicating the up direction of the viewer <code>up</code>.
/// The view matrix <code>V</code> is constructed as follows
/// Let
/// @code
/// forward := norm(target - source)
/// right := forward x norm(up)
/// up' := right x forward
/// @endcode
/// Then the view matrix <code>V</code> is given by
/// @code
/// V :=
/// | right.x    | right.y    | right.z    | 0
/// | up'.x      | up'.y      | up'.z      | 0
/// | -forward.x | -forward.y | -forward.z | 0
/// | 0          | 0          | 0          | 1
/// @endcode
void dx_mat4_set_look_at(DX_MAT4* a, DX_VEC3 const* source, DX_VEC3 const* target, DX_VEC3 const* up) {
  DX_VEC3 forward, right, up1, up2;
  DX_MAT4 r, t;

  // forward := norm(target - source)
  dx_vec3_sub3(&forward, target, source);
  dx_vec3_norm(&forward, &forward);
  // right := forward x norm(up)
  dx_vec3_norm(&up1, up);
  dx_vec3_cross(&right, &forward, &up1);
  // up' := right x forward
  dx_vec3_cross(&up2, &right, &forward);

  // column #1
  r.e[0][0] = right.e[0];
  r.e[1][0] = up2.e[0];
  r.e[2][0] = -forward.e[0];
  r.e[3][0] = 0.f;
  // column #2
  r.e[0][1] = right.e[1];
  r.e[1][1] = up2.e[1];
  r.e[2][1] = -forward.e[1];
  r.e[3][1] = 0.f;
  // column #3
  r.e[0][2] = right.e[2];
  r.e[1][2] = up2.e[2];
  r.e[2][2] = -forward.e[2];
  r.e[3][2] = 0.f;
  // column #4
  r.e[0][3] = 0.f;
  r.e[1][3] = 0.f;
  r.e[2][3] = 0.f;
  r.e[3][3] = 1.f;

  dx_mat4_set_translate(&t, -source->e[0], -source->e[1], -source->e[2]);

  dx_mat4_mul3(a, &r, &t);
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

void dx_transform_point(DX_VEC3* u, DX_VEC3 const* v, DX_MAT4 const* m) {
  dx_f32 e[3];

  e[0] = m->e[0][0] * v->e[0]
       + m->e[0][1] * v->e[1]
       + m->e[0][2] * v->e[2]
       + m->e[0][3] * 1.f;

  e[1] = m->e[1][0] * v->e[0]
       + m->e[1][1] * v->e[1]
       + m->e[1][2] * v->e[2]
       + m->e[1][3] * 1.f;

  e[2] = m->e[2][0] * v->e[0]
       + m->e[2][1] * v->e[1]
       + m->e[2][2] * v->e[2]
       + m->e[2][3] * 1.f;

  u->e[0] = e[0];
  u->e[1] = e[1];
  u->e[2] = e[2];
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

#if defined(DX_MATH_WITH_TESTS) && 1 == DX_MATH_WITH_TESTS
Core_Result dx_math_tests() {
  DX_VEC3 p = { 0.f, 0.f, -1.f };
  DX_VEC3 q;
  DX_MAT4 a;

#define EQ(x,y) dx_almost_equal_f32((x), (y), 2, FLT_EPSILON*2)

  // f is a counter-clockwise rotation around the y-axis by 0 degrees.
  // it follows that f((0,0,-1)) = (0,0,-1)
  dx_mat4_set_rotate_y(&a, 0.f);
  dx_transform_point(&q, &p, &a);
  if (!(EQ(q.e[0], 0.f) && EQ(q.e[1], 0.f) && EQ(q.e[2], -1.f))) {
    return Core_Failure;
  }

  // f is a counter-clockwise rotation around the y-axis by 90 degrees.
  // it follows that f((0,0,-1)) = (-1,0,0)
  dx_mat4_set_rotate_y(&a, 90.f);
  dx_transform_point(&q, &p, &a);
  if (!(EQ(q.e[0], -1.f) && EQ(q.e[1], 0.f) && EQ(q.e[2], 0.f))) {
    return Core_Failure;
  }

  // f is a counter-clockwise rotation around the y-xis by 180 degrees.
  // it follows that f((0,0,-1))= (0,0,1)
  dx_mat4_set_rotate_y(&a, 180.f);
  dx_transform_point(&q, &p, &a);
  if (!(EQ(q.e[0], 0.f) && EQ(q.e[1], 0.f) && EQ(q.e[2], 1.f))) {
    return Core_Failure;
  }

  // f is a counter-clockwise rotation around the y-xis by 270 degrees.
  // it follows that f((0,0,-1)) = (1,0,0)
  dx_mat4_set_rotate_y(&a, 270.f);
  dx_transform_point(&q, &p, &a);
  if (!(EQ(q.e[0], 1.f) && EQ(q.e[1], 0.f) && EQ(q.e[2], 0.f))) {
    return Core_Failure;
  }
#undef EQ
  return Core_Success;
}
#endif
