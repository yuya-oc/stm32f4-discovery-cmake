
#include <libopencm3/stm32/rcc.h>
#include <libopencm3/stm32/gpio.h>
#include <vector>
#include <iostream>

//#define USE_FUNCTIONAL
#ifdef USE_FUNCTIONAL
	#include <functional>
#endif

void *__dso_handle;
extern "C"{
	extern void initialise_monitor_handles(void);
}

uint16_t exti_line_state;

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

static void button_setup(void)
{
	/* Enable GPIOA clock. */
	rcc_periph_clock_enable(RCC_GPIOA);

	/* Set GPIO0 (in GPIO port A) to 'input open-drain'. */
	gpio_mode_setup(GPIOA, GPIO_MODE_INPUT, GPIO_PUPD_NONE, GPIO0);
}

int main(void)
{
	std::vector<int> v;

	clock_setup();
	button_setup();
	gpio_setup();

	initialise_monitor_handles();

#ifdef USE_FUNCTIONAL
	std::function<void(int)> wait;
#else
	void (*wait)(int a);
#endif
	wait = [](auto num){ /* This lambda requires C++14 */
		for (auto i = 0; i < num; i++) {		/* Wait a bit. */
			__asm__("nop");
		}
	};

	/* Blink the LED (PD12) on the board. */
	int times = 0;
	while (true) {
		times++;
		std::cout << "times = " << times << std::endl;
		gpio_toggle(GPIOD, GPIO12);

		constexpr auto loop = 3000000;
		wait(loop);
	}

	return 0;
}
