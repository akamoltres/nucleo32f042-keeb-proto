#pragma once

#include <stdbool.h>
#include <stdint.h>

typedef enum {
    GPIO_A = 0,
    GPIO_B = 1,
    GPIO_C = 2,
    GPIO_D = 3,
    GPIO_E = 4,
    GPIO_F = 5,
} gpio_port;

void set_input(gpio_port port_e, uint8_t pin_idx);
void set_pulldown(gpio_port port_e, uint8_t pin_idx);
bool read_input(gpio_port port_e, uint8_t pin_idx);
void set_output(gpio_port port_e, uint8_t pin_idx);
void set_pushpull(gpio_port port_e, uint8_t pin_idx);
void write_output(gpio_port port_e, uint8_t pin_idx, bool value);
void set_af(gpio_port port_e, uint8_t pin_idx);
