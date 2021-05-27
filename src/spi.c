#include <dma.h>
#include <gpio.h>
#include <spi.h>
#include <stdbool.h>
#include <stdint.h>

typedef struct
{
    uint32_t cr1;
    uint32_t cr2;
    uint32_t sr;
    uint32_t dr;
    uint32_t crcpr;
    uint32_t rxcrcr;
    uint32_t txcrcr;
    uint32_t i2scfgr;
    uint32_t i2spr;
} spi_t;

#define SPI_BASE_1 (spi_t *)0x40013000;

void look_at_spi(void)
{
    volatile spi_t *spi1 = SPI_BASE_1;
    (void) spi1;
}

void send_spi_apa102c(uint16_t *buffer, uint32_t bufsize)
{
    // configure PA5 (SCK) and PA7 (COPI) to alternate function
    // with push-pull (so pull-up/down doesn't matter)
    set_pushpull(GPIO_A, 4);
    set_af(GPIO_A, 4);
    set_pushpull(GPIO_A, 5);
    set_af(GPIO_A, 5);
    set_pushpull(GPIO_A, 6);
    set_af(GPIO_A, 6);
    set_pushpull(GPIO_A, 7);
    set_af(GPIO_A, 7);

    uint32_t index = 0;

    volatile spi_t *spi1 = SPI_BASE_1;
    spi1->dr = 0U;
    spi1->cr1 = 0b1100000010111111U;
    spi1->cr2 = 0b0000111100000000U;
    spi1->cr1 |= (1U << 6); // SPI enable on

    while (1)
    {
        if (spi1->sr & 0x2U)
        {
            if (index < bufsize)
            {
                spi1->dr = buffer[index];
                index += 1;
            }
            else
            {
                while (spi1->sr & (1U << 7));
                break;
            }
        }
    }
    spi1->cr1 &= ~(0x1U << 6);
    write_output(GPIO_A, 1, true);
}

// per ST rm0091 28.5.7
void init_spi_apa102c(uint32_t *input_buffer, uint32_t input_buffer_length)
{
    volatile spi_t *spi1 = SPI_BASE_1;

    // configure PA5 (SCK) and PA7 (COPI) to alternate function
    // with push-pull (so pull-up/down doesn't matter)
    set_af(GPIO_A, 4);
    set_pushpull(GPIO_A, 4);
    set_af(GPIO_A, 5);
    set_pushpull(GPIO_A, 5);
    set_af(GPIO_A, 6);
    set_pushpull(GPIO_A, 6);
    set_af(GPIO_A, 7);
    set_pushpull(GPIO_A, 7);

    // configure SPI_CR1
    spi1->cr1 &= ~(0x7U << 3); // baud rate to f_pclk/2
    spi1->cr1 |= 3U; // CPHA and CPOL both 1 (SPI mode 3)
    spi1->cr1 |= (3U << 14); // half duplex, output enabled
    spi1->cr1 |= (3U << 15); // half duplex, output enabled
    spi1->cr1 &= ~(1U << 7); // MSB first
    spi1->cr1 |= (1U << 2); // SPI controller
    spi1->cr1 |= (1U << 9); // software peripheral management
    spi1->cr1 |= (1U << 8); // turn on internal peripheral select

    // configure SPI_CR2
    // spi1->cr2 |= (1U << 7); // tx buffer empty interrupt enabled
    spi1->cr2 |= (1U << 1); // tx DMA enable
    spi1->cr2 |= (0b1111 << 8); // 16 bit spi transfer

    // configure DMA
    // SPI1_TX is on DMA channel 3
    init_dma_spi1(&spi1->dr, input_buffer, input_buffer_length);
    spi1->cr1 |= (1U << 6); // SPI enable
}

bool spi_tx_finished(void)
{
    volatile spi_t *spi1 = SPI_BASE_1;
    uint32_t temp = 0;
    while (1)
    {
        if (temp == 0)
        {
            temp = spi1->dr;
        }
    }
    if ((spi1->sr & 0x0680) == 0)
    {
        return true;
    }
    return false;
}
