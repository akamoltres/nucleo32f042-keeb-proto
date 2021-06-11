#include <rcc.h>
#include <stdint.h>

typedef struct
{
    uint32_t ep0r;
    uint32_t ep1r;
    uint32_t ep2r;
    uint32_t ep3r;
    uint32_t ep4r;
    uint32_t ep5r;
    uint32_t ep6r;
    uint32_t ep7r;
    uint32_t res0;
    uint32_t res1;
    uint32_t res2;
    uint32_t res3;
    uint32_t res4;
    uint32_t res5;
    uint32_t res6;
    uint32_t res7;
    uint32_t cntr;
    uint32_t istr;
    uint32_t fnr;
    uint32_t daddr;
    uint32_t btable;
    uint32_t lpmcsr;
    uint32_t bcdr;
} usb_t;

typedef struct
{
    uint16_t addr_tx;
    uint16_t count_tx;
    uint16_t addr_rx;
    uint16_t count_rx;
} __attribute__((packed)) usb_buffer_descriptor_t;

#define USB_BASE (usb_t *)0x40005C00
#define USB_PMA (uint32_t *)0x40006000
#define NUM_ENDPOINTS 8

const static usb_buffer_descriptor_t bdtable[NUM_ENDPOINTS] =
{
    {
        .addr_tx = 64U,
        .count_tx = 16U,
        .addr_rx = 80U,
        .count_rx = 16U,
    },
    {
        .addr_tx = 96U,
        .count_tx = 16U,
        .addr_rx = 112U,
        .count_rx = 16U,
    },
    {
        .addr_tx = 128U,
        .count_tx = 16U,
        .addr_rx = 144U,
        .count_rx = 16U,
    },
    {
        .addr_tx = 160U,
        .count_tx = 16U,
        .addr_rx = 176U,
        .count_rx = 16U,
    },
    {
        .addr_tx = 192U,
        .count_tx = 16U,
        .addr_rx = 208U,
        .count_rx = 16U,
    },
    {
        .addr_tx = 224U,
        .count_tx = 16U,
        .addr_rx = 240U,
        .count_rx = 16U,
    },
    {
        .addr_tx = 256U,
        .count_tx = 16U,
        .addr_rx = 272U,
        .count_rx = 16U,
    },
    {
        .addr_tx = 288U,
        .count_tx = 16U,
        .addr_rx = 304U,
        .count_rx = 16U,
    },
};

void init_usb(void)
{
    volatile usb_t *usb = USB_BASE;

    usb->cntr &= ~(1U << 1);
    // TODO wait for at least 1 us
    usb->cntr &= ~(1U);
    usb->istr = 0U;

    // copy buffer descriptor table to PMA
    for (uint16_t i = 0; i < NUM_ENDPOINTS; ++i)
    {
        *(USB_PMA + 64 * i) = bdtable[i].addr_tx;
        *(USB_PMA + 64 * i + 16) = bdtable[i].count_tx;
        *(USB_PMA + 64 * i + 32) = bdtable[i].addr_rx;
        *(USB_PMA + 64 * i + 48) = bdtable[i].count_rx;
    }

    // endpoint 0: control endpoint
    usb->ep0r &= ~(1U << 10);
    usb->ep0r &= 1U << 9;
}
