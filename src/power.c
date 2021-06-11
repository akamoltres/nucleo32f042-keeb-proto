#include <power.h>
#include <stdint.h>

typedef struct
{
    uint32_t cr;
    uint32_t csr;
} power_t;

#define POWER_BASE (power_t *)0x40007000;

void init_power(void)
{
    volatile power_t *power = POWER_BASE;
    power->cr |= (1U << 8);
}
