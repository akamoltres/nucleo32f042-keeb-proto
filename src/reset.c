#include <proto.h>
#include <stm32f042k6t6.h>
#include <stdint.h>

extern uint32_t _estack;
extern uint32_t _sbss;
extern uint32_t _ebss;
extern uint32_t _sdata;
extern uint32_t _edata;
extern uint32_t _etext;
extern uint32_t _appstart;

void reset_handler(void);
void nmi_handler();
void hardfault_handler();

__attribute__ ((section(".vector_table")))
const VectorTable vector_table = {
    .sp         = (void *) (&_estack),
    .reset      = (void *) &reset_handler,
    .nmi        = (void *) &nmi_handler,
    .hardfault  = (void *) &hardfault_handler,
};

void reset_handler(void)
{
    // zero out bss
    for (uint32_t *bss_ptr = &_sbss; bss_ptr < &_ebss; ++bss_ptr)
    {
        *bss_ptr = 0;
    }

    // init data
    uint32_t *src = &_etext;
    uint32_t *dst = &_sdata;
    while (dst < &_edata)
    {
        *(dst++) = *(src++);
    }

    // jump to application
    main();
}

void nmi_handler(void)
{
    while (1);
}

void hardfault_handler(void)
{
    while (1);
}
