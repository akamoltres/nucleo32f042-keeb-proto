#pragma once

#include <stdint.h>

void init_dma_spi1(volatile uint32_t *cpar, uint32_t *cmar, uint32_t cndtr);
void look_at_dma(void);
