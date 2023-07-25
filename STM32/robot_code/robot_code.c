#include <libopencm3/stm32/rcc.h>
#include <libopencm3/stm32/gpio.h>
#include <libopencm3/stm32/usart.h>
#include <libopencm3/cm3/nvic.h>
#include <libopencm3/stm32/timer.h>

int main(void) {
    // Enable clock for GPIOA and TIM2
    rcc_periph_clock_enable(RCC_GPIOA);
    rcc_periph_clock_enable(RCC_TIM2);

    // Set PA6 to alternate function (AF) mode for TIM2_CH3
    gpio_set_mode(GPIOA, GPIO_MODE_OUTPUT_50_MHZ, GPIO_CNF_OUTPUT_ALTFN_PUSHPULL, GPIO_TIM2_CH3);

// PWM setup
// Reset TIM2
// timer_reset(TIM2);

// Set the Timer mode to no divisor (72MHz), Edge-aligned, up-counting
timer_set_mode(TIM2, TIM_CR1_CKD_CK_INT, TIM_CR1_CMS_EDGE, TIM_CR1_DIR_UP);

// Set the prescaler to 72
timer_set_prescaler(TIM2, 72);

// Disable preload
timer_disable_preload(TIM2);

// Continuous mode
timer_continuous_mode(TIM2);

// Set the auto-reload value (ARR)
timer_set_period(TIM2, 1000);

// Set the PWM mode for channel 3 - PWM mode 1
timer_set_oc_mode(TIM2, TIM_OC3, TIM_OCM_PWM1);

// Set the output compare value for OC1
timer_set_oc_value(TIM2, TIM_OC3, 500);

// Enable the output compare - OC1
timer_enable_oc_output(TIM2, TIM_OC3);

// Enable the Timer
timer_enable_counter(TIM2);

    // Enable clock for USART1 and GPIOA
    rcc_periph_clock_enable(RCC_USART1);
    rcc_periph_clock_enable(RCC_GPIOA);

    // Set PA9 to alternate function (USART1_TX) and PA10 to input (USART1_RX)
    gpio_set_mode(GPIOA, GPIO_MODE_OUTPUT_50_MHZ, GPIO_CNF_OUTPUT_ALTFN_PUSHPULL, GPIO_USART1_TX);
    gpio_set_mode(GPIOA, GPIO_MODE_INPUT, GPIO_CNF_INPUT_FLOAT, GPIO_USART1_RX);

// USART setup
usart_set_baudrate(USART1, 9600);
usart_set_databits(USART1, 8);
usart_set_stopbits(USART1, USART_STOPBITS_1);
usart_set_mode(USART1, USART_MODE_TX_RX);
usart_set_parity(USART1, USART_PARITY_NONE);
usart_set_flow_control(USART1, USART_FLOWCONTROL_NONE);

usart_enable(USART1);

    // Enable USART1 interrupt
    nvic_enable_irq(NVIC_USART1_IRQ);
    nvic_set_priority(NVIC_USART1_IRQ, 0);

while (1) {
    // Check if there is data available to read
    if (usart_get_flag(USART1, USART_FLAG_RXNE)) {
        char received_data = usart_recv(USART1);

        // Here you can process the received data
        // For example, let's print it back to the USART
        usart_send_blocking(USART1, received_data);
    }
}

    return 0;
}

void usart1_isr(void) {
    if (usart_get_flag(USART1, USART_FLAG_RXNE)) {
        char received_data = usart_recv(USART1);
        // Process received_data
    }
}
