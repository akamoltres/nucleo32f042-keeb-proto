#include <rtc.h>

typedef struct
{
    uint32_t tr;
    uint32_t dr;
    uint32_t cr;
    uint32_t isr;
    uint32_t prer;
    uint32_t wutr;
    uint32_t alrmar;
    uint32_t wpr;
    uint32_t ssr;
    uint32_t shiftr;
    uint32_t tstr;
    uint32_t tsdr;
    uint32_t tsssr;
    uint32_t calr;
    uint32_t tafcr;
    uint32_t alrmassr;
    uint32_t bkpr[5];
} rtc_t;

#define RTC_BASE (rtc_t *)0x40002800

uint32_t rtc_get_seconds(void)
{
    rtc_t *rtc = RTC_BASE;

    uint32_t tens = (rtc->tr & 0x00000070) >> 4;
    uint32_t ones = (rtc->tr & 0x0000000F);
    return (tens * 10 + ones);
}
