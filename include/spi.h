#pragma once

#include <stdbool.h>
#include <stdint.h>

void send_spi_apa102c(uint16_t *buffer, uint32_t bufsize);
void look_at_spi(void);
void init_spi_apa102c(uint32_t *input_buffer, uint32_t input_buffer_length);
bool spi_tx_finished(void);
