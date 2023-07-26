#include <libopencm3/stm32/rcc.h>
#include <libopencm3/stm32/gpio.h>
#include <libopencm3/stm32/timer.h>
void init_gpio(void);
void setup_pwm(void);

void init_gpio(void)
{
    int i;

    /* Enable GPIOB clock. */
    rcc_periph_clock_enable(RCC_GPIOB);

    /* Set GPIO0 (in GPIO port B) to 'output push-pull'. */
    for(i = 0; i < 16; i++)
    {
        if(i != 12)
        {
            gpio_set_mode(GPIOB, GPIO_MODE_OUTPUT_2_MHZ,
                          GPIO_CNF_OUTPUT_PUSHPULL, (1 << i));
            gpio_clear(GPIOB, (1 << i));
        }
    }

    /* Set GPIO12 (in GPIO port B) to 'output alternate function push-pull'. */
    gpio_set_mode(GPIOB, GPIO_MODE_OUTPUT_2_MHZ,
                  GPIO_CNF_OUTPUT_ALTFN_PUSHPULL, GPIO12);
}

void setup_pwm(void)
{
    /* Reset TIM4 peripheral. */
    rcc_periph_reset_pulse(RST_TIM4);

    /* Clock division and mode. */
    timer_set_mode(TIM4, TIM_CR1_CKD_CK_INT, TIM_CR1_CMS_EDGE, TIM_CR1_DIR_UP);

    /* Reset prescaler value. */
    timer_set_prescaler(TIM4, 0);

    /* Enable preload. */
    timer_disable_preload(TIM4);

    /* Continous mode. */
    timer_continuous_mode(TIM4);

    /* Period (36MHz/1000). */
    timer_set_period(TIM4, 1000);

    /* Disable outputs. */
    timer_disable_oc_output(TIM4, TIM_OC1);
    timer_disable_oc_output(TIM4, TIM_OC2);
    timer_disable_oc_output(TIM4, TIM_OC3);
    timer_disable_oc_output(TIM4, TIM_OC4);

    /* -- OC1 configuration -- */

    /* Configure global mode of line 1. */
    timer_disable_oc_clear(TIM4, TIM_OC1);
    timer_disable_oc_preload(TIM4, TIM_OC1);
    timer_set_oc_slow_mode(TIM4, TIM_OC1);
    timer_set_oc_mode(TIM4, TIM_OC1, TIM_OCM_PWM1);

    /* Set the capture compare value for OC1. */
    timer_set_oc_value(TIM4, TIM_OC1, 100);

    /* Enable OC1. */
    timer_enable_oc_output(TIM4, TIM_OC1);

    /* ---- */

    /* ARR reload enable. */
    timer_disable_preload(TIM4);

    /* Counter enable. */
    timer_enable_counter(TIM4);

    /* Enable commutation interrupt. */
    timer_enable_irq(TIM4, TIM_DIER_CC1IE);

    /* Enable TIM4. */
    timer_enable_counter(TIM4);
}

int main(void)
{
    /* Initialize GPIOs. */
    init_gpio();

    /* Setup PWM. */
    setup_pwm();

    /* Main loop. */
    while (1)
    {
        int i;
        // for(i = 0; i <= 100; i++)
        // {
        //     timer_set_oc_value(TIM4, TIM_OC1, i);
        //     for(int j = 0; j < 100000; j++) /* Delay */
        //     {
        //         __asm__("nop");
        //     }
        // }        
    }

    return 0;
}