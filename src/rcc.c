#include <rcc.h>
#include <stdint.h>

typedef struct
{
    uint32_t cr;
    uint32_t cfgr;
    uint32_t cir;
    uint32_t apb2rstr;
    uint32_t apb1rstr;
    uint32_t ahbenr;
    uint32_t apb2enr;
    uint32_t apb1enr;
    uint32_t bdcr;
    uint32_t csr;
    uint32_t ahbrstr;
    uint32_t cfgr2;
    uint32_t cfgr3;
    uint32_t cr2;
} rcc_t;

#define RCC_BASE (rcc_t *)0x40021000;

void init_rcc(void)
{
    rcc_t *rcc = RCC_BASE;
    rcc->ahbenr |= (1U << 17); // GPIO port A clock enable
    // rcc->ahbenr |= 1U; // DMA1 clock enable
    rcc->apb2enr |= (1U);
    rcc->apb2enr |= (1U << 12); // SPI1 clock enable
}
