#include <apa102c.h>
#include <dma.h>
#include <gpio.h>
#include <power.h>
#include <rcc.h>
#include <rtc.h>
#include <spi.h>

static const apa102c_t led[11] = {
    APA102C_START_FRAME,
    APA102C(0x01U, 0x01U, 0x00U, 0x00U),
    APA102C(0x02U, 0x01U, 0x00U, 0x00U),
    APA102C(0x03U, 0x01U, 0x00U, 0x00U),
    APA102C(0x01U, 0x10U, 0x00U, 0x00U),
    APA102C(0x02U, 0x10U, 0x00U, 0x00U),
    APA102C(0x03U, 0x10U, 0x00U, 0x00U),
    APA102C(0x01U, 0xFFU, 0x00U, 0x00U),
    APA102C(0x02U, 0xFFU, 0x00U, 0x00U),
    APA102C(0x03U, 0xFFU, 0x00U, 0x00U),
    APA102C_END_FRAME,
};

int main()
{
    init_power();
    init_rtc();
    init_rcc();

    set_input(GPIO_A, 0);
    set_pulldown(GPIO_A, 0);
    set_output(GPIO_A, 1);
    set_pushpull(GPIO_A, 1);

    rtc_get_ss();

    // init_spi_apa102c((uint32_t *) led, 11);
    send_spi_apa102c((uint16_t *) led, 11 * 2);
    while (1);

    bool spi_complete = false;
    while (1)
    {
        look_at_dma();
        // write_output(GPIO_A, 1, read_input(GPIO_A, 0));
        if (read_input(GPIO_A, 0))
        {
            look_at_spi();
        }
        if (spi_tx_finished())
        {
            spi_complete = true;
        }
        write_output(GPIO_A, 1, spi_complete);
    }
}
