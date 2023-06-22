#include <libopencm3/stm32/rcc.h>
#include <libopencm3/stm32/gpio.h>

int main(void) {
    rcc_periph_clock_enable(RCC_GPIOC);
    
    gpio_mode_setup(GPIOC, 
        GPIO_MODE_OUTPUT, // Set the pin direction to output
        GPIO_PUPD_NONE, // No pull-up, no pull-down
        GPIO8);

    while(1) {
        for (int i = 0; i < 1000000; i++) {
            __asm__("nop");
        }

        gpio_toggle(GPIOC, GPIO8);
    }
}
