#ifndef ABACUS_GPIO_H
#define ABACUS_GPIO_H

#include <stdbool.h>
#include <stdint.h>

enum gpio_pud {
	GPIO_PUD_OFF,
	GPIO_PUD_DOWN,
	GPIO_PUD_UP,
};

enum gpio_function {
	GPIO_FUNC_INP = 0,
	GPIO_FUNC_OUT = 1,
	GPIO_FUNC_ALT0 = 4,
	GPIO_FUNC_ALT1 = 5,
	GPIO_FUNC_ALT2 = 6,
	GPIO_FUNC_ALT3 = 7,
	GPIO_FUNC_ALT4 = 3,
	GPIO_FUNC_ALT5 = 2,
};

enum gpio_pin {
	GPIO_PIN_0,
	GPIO_PIN_1,
	GPIO_PIN_2,
	GPIO_PIN_3,
	GPIO_PIN_4,
	GPIO_PIN_5,
	GPIO_PIN_6,
	GPIO_PIN_7,
	GPIO_PIN_8,
	GPIO_PIN_9,
	GPIO_PIN_10,
	GPIO_PIN_11,
	GPIO_PIN_12,
	GPIO_PIN_13,
	GPIO_PIN_14,
	GPIO_PIN_15,
	GPIO_PIN_16,
	GPIO_PIN_17,
	GPIO_PIN_18,
	GPIO_PIN_19,
	GPIO_PIN_20,
	GPIO_PIN_21,
	GPIO_PIN_22,
	GPIO_PIN_23,
	GPIO_PIN_24,
	GPIO_PIN_25,
	GPIO_PIN_26,
	GPIO_PIN_27,
	GPIO_PIN_28,
	GPIO_PIN_29,
	GPIO_PIN_30,
	GPIO_PIN_31,
	GPIO_PIN_32,
	GPIO_PIN_33,
	GPIO_PIN_34,
	GPIO_PIN_35,
	GPIO_PIN_36,
	GPIO_PIN_37,
	GPIO_PIN_38,
	GPIO_PIN_39,
	GPIO_PIN_40,
	GPIO_PIN_41,
	GPIO_PIN_42,
	GPIO_PIN_43,
	GPIO_PIN_44,
	GPIO_PIN_45,
	GPIO_PIN_46,
	GPIO_PIN_47,
	GPIO_PIN_48,
	GPIO_PIN_49,
	GPIO_PIN_50,
	GPIO_PIN_51,
	GPIO_PIN_52,
	GPIO_PIN_53,
};

void
gpio_pud_mode(enum gpio_pud pud);

inline void
gpio_pudclk_hold(void)
{
	for (int index = 0; index < 150; index ++);
}

void
gpio_pudclk_signal(enum gpio_pin pin);

void
gpio_pin_setup(enum gpio_pin pin, enum gpio_function function);

#endif // ABACUS_GPIO_H
