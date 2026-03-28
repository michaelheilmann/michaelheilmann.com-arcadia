#include "dx/core/math.h"

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

// sinf, cosf, sqrtf
#include <math.h>

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

void dx_rgb_u8_lerp(Core_InlineRgbN8 const* a, Core_InlineRgbN8 const* b, Core_Real32 t, Core_InlineRgbN8* c) {
  t = dx_clamp(t);
  if (t == 0.f) {
    *c = *a;
  } else if (t == 1.f) {
    *c = *b;
  } else {
    Core_Real32 s = 1.f - t;
    c->r = s * ((Core_Real32)a->r) + t * ((Core_Real32)b->r);
    c->g = s * ((Core_Real32)a->g) + t * ((Core_Real32)b->g);
    c->b = s * ((Core_Real32)a->b) + t * ((Core_Real32)b->b);
  }
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

void Core_InlineVector2R32_mul_vs(Core_InlineVector2R32* RETURN, Core_InlineVector2R32 const* operand1, Core_Real32 operand2) {
  RETURN->e[0] = operand1->e[0] * operand2;
  RETURN->e[1] = operand1->e[1] * operand2;
}

void Core_InlineVector2R32_mulc_vv(Core_InlineVector2R32* RETURN, Core_InlineVector2R32 const* operand1, Core_InlineVector2R32 const* operand2) {
  RETURN->e[0] = operand1->e[0] * operand2->e[0];
  RETURN->e[1] = operand1->e[1] * operand2->e[1];
}

void Core_InlineVector2R32_sub_vv(Core_InlineVector2R32* RETURN, Core_InlineVector2R32 const* operand1, Core_InlineVector2R32 const* operand2) {
  RETURN->e[0] = operand1->e[0] - operand2->e[0];
  RETURN->e[1] = operand1->e[1] - operand2->e[1];
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

void dx_vec3_norm(DX_VEC3* u, DX_VEC3 const* v) {
  Core_Real32 sql = dx_vec3_sql(v);
  if (sql == 0.f) {
    u->e[0] = 0.f;
    u->e[1] = 0.f;
    u->e[2] = 0.f;
    return;
  }
  Core_Real32 l = sqrtf(sql);
  u->e[0] = v->e[0] / l;
  u->e[1] = v->e[1] / l;
  u->e[2] = v->e[2] / l;
}

void dx_vec3_cross(DX_VEC3* w, DX_VEC3 const* u, DX_VEC3 const* v) {
  Core_Real32 t[3];
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
    Core_Real32 t[4][4];

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

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

void dx_transform_point(DX_VEC3* u, DX_VEC3 const* v, DX_MAT4 const* m) {
  Core_Real32 e[3];

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
