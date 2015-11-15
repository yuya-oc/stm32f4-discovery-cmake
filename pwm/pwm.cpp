#include <libopencm3/stm32/rcc.h>
#include <libopencm3/stm32/gpio.h>
#include <libopencm3/stm32/timer.h>
#include <stdio.h>

extern "C"{
  void initialise_monitor_handles(void);
}

/* Set STM32 to 168 MHz. */
static void clock_setup(void)
{
	rcc_clock_setup_hse_3v3(&hse_8mhz_3v3[CLOCK_3V3_168MHZ]);

	/* Enable GPIOD clock. */
	rcc_periph_clock_enable(RCC_GPIOD);

	// Enable TIM4 clock.
	rcc_periph_clock_enable(RCC_TIM4);
}

static void gpio_setup(void)
{
  // Assign Alternate function TIM4-CHx
  gpio_set_af(GPIOD, GPIO_AF2, GPIO12 | GPIO13 | GPIO14 | GPIO15);
  gpio_set_output_options(GPIOD, GPIO_OTYPE_PP, GPIO_OSPEED_50MHZ, GPIO12 | GPIO13 | GPIO14 | GPIO15);

  /* Set GPIO12-15 (in GPIO port D) to 'output push-pull'. */
  gpio_mode_setup(GPIOD, GPIO_MODE_AF, GPIO_PUPD_NONE,
    GPIO12 | GPIO13 | GPIO14 | GPIO15);

}

constexpr auto tim4_period = 1000;

static void my_pwm_setup(void){
  auto tim = TIM4;
  // Set TIM4
  timer_reset(tim);
  timer_set_mode(tim, TIM_CR1_CKD_CK_INT, TIM_CR1_CMS_EDGE, TIM_CR1_DIR_UP); // div=1, edge align, incremental
  timer_enable_preload(tim);

  timer_enable_oc_preload(tim, TIM_OC1);
  timer_set_oc_mode(tim, TIM_OC1, TIM_OCM_PWM1);
  timer_enable_oc_output(tim, TIM_OC1);

  timer_set_oc_value(tim, TIM_OC1, 10);
  timer_set_period(tim, tim4_period);

  timer_generate_event(tim, TIM_EGR_UG);
  timer_enable_counter(tim);
  return;
}

int main(void)
{
	clock_setup();
	gpio_setup();
	my_pwm_setup();
  initialise_monitor_handles();

	/* Blink the LEDs (PD12, PD13, PD14 and PD15) on the board. */
	while (true) {
	  printf("duty[%%] = ");
    fflush(stdout);
	  int i;
	  scanf("%d", &i);
	  int val = tim4_period * i / 100;
	  timer_set_oc_value(TIM4, TIM_OC1, val);
	}

	return 0;
}
