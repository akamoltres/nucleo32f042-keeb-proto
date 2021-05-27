#include <dma.h>
#include <stdint.h>

typedef struct
{
    uint32_t ccr;
    uint32_t cndtr;
    uint32_t cpar;
    uint32_t cmar;
    uint32_t reserved;
} dma_channel_t;

typedef struct
{
    uint32_t isr;
    uint32_t ifcr;
    dma_channel_t channel[5];
} dma_t;

#define DMA_BASE (dma_t *)0x40020000;

// per ST rm0091 A.5.1
void init_dma_spi1(volatile uint32_t *cpar, uint32_t *cmar, uint32_t cndtr)
{
    volatile dma_t *dma = DMA_BASE;

    dma->channel[2].cpar = (uint32_t) cpar;
    dma->channel[2].cmar = (uint32_t) cmar;
    dma->channel[2].cndtr = cndtr;
    dma->channel[2].ccr |= (1U << 4); // memory -> peripheral
    dma->channel[2].ccr &= ~(1U << 9); // peripheral size: 16 bits
    dma->channel[2].ccr |= (1U << 8);
    dma->channel[2].ccr &= ~(1U << 10); // memory size: 32 bits
    dma->channel[2].ccr |= (1U << 11);
    // dma->channel[2].ccr |= (1U << 5); // enable circular mode
    // dma->channel[2].ccr &= ~(1U << 5); // actively disable circular mode
    dma->channel[2].ccr |= (1U << 1); // enable transfer complete interrupt
    dma->channel[2].ccr |= (1U << 2); // half transfer interrupt enable
    dma->channel[2].ccr |= (1U << 3); // transfer error interrupt enable
    dma->channel[2].ccr |= 1U; // enable
}

void look_at_dma(void)
{
    volatile dma_t *dma = DMA_BASE;
    (void) dma;
}
