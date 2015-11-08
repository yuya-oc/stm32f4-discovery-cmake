
#include <libopencm3/stm32/rcc.h>
#include <libopencm3/stm32/gpio.h>
#include <stdio.h>

uint16_t exti_line_state;

extern void  initialise_monitor_handles(void);

/* Set STM32 to 168 MHz. */
static void clock_setup(void)
{
	rcc_clock_setup_hse_3v3(&hse_8mhz_3v3[CLOCK_3V3_168MHZ]);
}

static void gpio_setup(void)
{
	/* Enable GPIOD clock. */
	rcc_periph_clock_enable(RCC_GPIOD);

	/* Set GPIO12 (in GPIO port D) to 'output push-pull'. */
	gpio_mode_setup(GPIOD, GPIO_MODE_OUTPUT,
			GPIO_PUPD_NONE, GPIO12 | GPIO13 | GPIO14 | GPIO15);
}

int main(void)
{
	clock_setup();
	gpio_setup();

	initialise_monitor_handles();
	printf("Hello world\n");


	/* Blink the LED (PD12) on the board. */
	int loop = 0;
	while (1) {
	  loop++;
	  printf("loop = %d\n", loop);
		gpio_toggle(GPIOD, GPIO12);

		int i;
    for (i = 0; i < 3000000; i++) {    /* Wait a bit. */
      __asm__("nop");
    }
	}

	return 0;
}
