#include <rtc.h>

typedef struct
{
    uint32_t tr;
    uint32_t dr;
    uint32_t cr;
    uint32_t isr;
    uint32_t prer;
    uint32_t wutr;
    uint32_t reserved0;
    uint32_t alrmar;
    uint32_t reserved1;
    uint32_t wpr;
    uint32_t ssr;
    uint32_t shiftr;
    uint32_t tstr;
    uint32_t tsdr;
    uint32_t tsssr;
    uint32_t calr;
    uint32_t tafcr;
    uint32_t alrmassr;
    uint32_t reserved2;
    uint32_t reserved3;
    uint32_t bkpr[5];
} rtc_t;

#define RTC_BASE (rtc_t *)0x40002800

void init_rtc(void)
{
    rtc_t *rtc = RTC_BASE;
    rtc->wpr = 0xCAU;
    rtc->wpr = 0x53U;
}

/*
uint32_t rtc_get_seconds(void)
{
    rtc_t *rtc = RTC_BASE;

    uint32_t tens = (rtc->tr & 0x00000070) >> 4;
    uint32_t ones = (rtc->tr & 0x0000000F);
    return (tens * 10 + ones);
}
*/

uint16_t rtc_get_ss(void)
{
    volatile rtc_t *rtc = RTC_BASE;
    uint32_t a, b;
    while (1)
    {
        a = rtc->ssr;
        b = rtc->tstr;
    }
}
