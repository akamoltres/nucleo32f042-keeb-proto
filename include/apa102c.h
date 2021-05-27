#pragma once

#include <stdint.h>

typedef uint32_t apa102c_t;

#define APA102C_START_FRAME 0U

#define APA102C(gl, r, g, b) \
    ((0x7U << 5) | (gl))     \
    | ((b) << 8)             \
    | ((g) << 16)            \
    | (r << 24)

#define APA102C_END_FRAME 0xFFFFFFFFU
