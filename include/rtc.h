#pragma once

#include <stdint.h>

void init_rtc(void);
// uint32_t rtc_get_seconds(void);
uint16_t rtc_get_ss(void);
