#include <gpio.h>
#include <stdbool.h>

typedef struct
{
    uint32_t moder;
    uint32_t otyper;
    uint32_t ospeedr;
    uint32_t pupdr;
    uint32_t idr;
    uint32_t odr;
    uint32_t bsrr;
    uint32_t lckr;
    uint32_t afrl;
    uint32_t arfh;
    uint32_t brr;
} gpio_t;

#define GPIO_BASE_A (gpio_t *)0x48000000;
#define GPIO_BASE_B (gpio_t *)0x48000400;
#define GPIO_BASE_F (gpio_t *)0x48001400;
// C/D/E are inaccessible or unused on Nucleo-32 STM32F042K6T6
#define GPIO_BASE_C (gpio_t *)0x48000800;
#define GPIO_BASE_D (gpio_t *)0x48000C00;
#define GPIO_BASE_E (gpio_t *)0x48001000;

static gpio_t *get_port(gpio_port port_e)
{
    switch (port_e)
    {
        case GPIO_A:
            return GPIO_BASE_A;
        case GPIO_B:
            return GPIO_BASE_B;
        case GPIO_C:
            return GPIO_BASE_C;
        case GPIO_D:
            return GPIO_BASE_D;
        case GPIO_E:
            return GPIO_BASE_E;
        case GPIO_F:
            return GPIO_BASE_F;
    }
}

void set_input(gpio_port port_e, uint8_t pin_idx)
{
    volatile gpio_t *port = get_port(port_e);
    port->moder &= ~(3U << (2 * pin_idx));
}

void set_pulldown(gpio_port port_e, uint8_t pin_idx)
{
    volatile gpio_t *port = get_port(port_e);
    port->pupdr &= ~(1U << (2 * pin_idx));
    port->pupdr |= (1U << (2 * pin_idx + 1));
}

bool read_input(gpio_port port_e, uint8_t pin_idx)
{
    volatile gpio_t *port = get_port(port_e);
    return (port->idr & (1U << pin_idx));
}

void set_output(gpio_port port_e, uint8_t pin_idx)
{
    volatile gpio_t *port = get_port(port_e);
    port->moder &= ~(1U << (2 * pin_idx + 1));
    port->moder |= (1U << (2 * pin_idx));
}

void set_pushpull(gpio_port port_e, uint8_t pin_idx)
{
    volatile gpio_t *port = get_port(port_e);
    port->otyper &= ~(1U << pin_idx);
    port->pupdr &= ~(3U << pin_idx);
}

void write_output(gpio_port port_e, uint8_t pin_idx, bool value)
{
    volatile gpio_t *port = get_port(port_e);
    if (value)
    {
        port->odr |= (1U << pin_idx);
    }
    else
    {
        port->odr &= ~(1U << pin_idx);
    }
}

void set_af(gpio_port port_e, uint8_t pin_idx)
{
    volatile gpio_t *port = get_port(port_e);
    port->moder |= (1U << (2 * pin_idx + 1));
    port->moder &= ~(1U << (2 * pin_idx));
}
