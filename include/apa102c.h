#pragma once

#include <stdint.h>

typedef uint32_t apa102c_t;

#define FLIP_TWO(x)       \
    ((((x) & 0x1) << 1) | \
    (((x) & 0x2) >> 1))

#define FLIP_FOUR(x)               \
    ((FLIP_TWO((x) & 0x3U) << 2) | \
    (FLIP_TWO(((x) & 0xCU) >> 2)))

#define FLIP_EIGHT(x)                \
    ((FLIP_FOUR((x) & 0x0FU) << 4) | \
    (FLIP_FOUR(((x) & 0xF0U) >> 4)))

#define APA102C_START_FRAME 0U

#define APA102C(gl, r, g, b) 		 \
    (FLIP_EIGHT((0x7U << 5) | (gl))) \
    | ((FLIP_EIGHT(b)) << 8)         \
    | ((FLIP_EIGHT(g)) << 16)        \
    | ((FLIP_EIGHT(r)) << 24)

#define APA102C_END_FRAME 0xFFFFFFFFU
