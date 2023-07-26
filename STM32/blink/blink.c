#include <libopencm3/stm32/rcc.h>
#include <libopencm3/stm32/gpio.h>

int main(void) {
rcc_periph_clock_enable(RCC_GPIOB);
gpio_set_mode(GPIOB, GPIO_MODE_OUTPUT_2_MHZ, GPIO_CNF_OUTPUT_PUSHPULL, GPIO12);
while(1) {
    gpio_set(GPIOB, GPIO12);
    for (int i = 0; i < 1000000; ++i) __asm__("nop");
    gpio_clear(GPIOB, GPIO12);
    for (int i = 0; i < 500000; ++i) __asm__("nop");
}
}