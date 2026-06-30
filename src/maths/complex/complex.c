#include "maths/complex/complex.h"

#define CX_REAL f32
#define CX_TYPE complex32
#define CX_PREFIX cx32
#include "maths/complex/complex_template.h"

#undef CX_REAL
#undef CX_TYPE
#undef CX_PREFIX

#define CX_REAL f64
#define CX_TYPE complex64
#define CX_PREFIX cx64
#include "maths/complex/complex_template.h"

#undef CX_REAL
#undef CX_TYPE
#undef CX_PREFIX