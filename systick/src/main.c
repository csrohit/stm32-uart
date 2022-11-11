/**
 ******************************************************************************
 * @file           : main.c
 * @author         : Rohit Nimkar <nehalnimkar@gmail.com> <https://csrohit.github.io>
 * @brief          : Main program body
 ******************************************************************************
 * @attention
 *
 * This software component is licensed by Rohit Nimkar under BSD 3-Clause license,
 * the "License"; You may not use this file except in compliance with the
 * License. You may obtain a copy of the License at:
 *                        opensource.org/licenses/BSD-3-Clause
 *
 ******************************************************************************
 */

#include <stm32f1xx.h>

volatile uint32_t msTicks = 0;

/**
 * @brief Interrupt handler function
 * 
 */
void SysTick_Handler(void)
{
	msTicks++;
}

/**
 * @brief Add blocking delay
 *
 * @param ms delay in milliseconds
 */
void delay(int ms)
{
	uint32_t expected_ticks = msTicks + ms;
	while (msTicks < expected_ticks)
	{
		__asm("nop");
	}
}

/**
 * @brief Initialise GPIOC pin 13
 * - Enable clock for GPIOC
 * - set pin13 as push pull output
 */
void led_init()
{
	RCC->APB2ENR |= RCC_APB2ENR_IOPCEN;
	GPIOC->CRH = 0x02 << ((13 - 8) << 2);
}

/**
 * @brief Set GPIOC pin 13
 *
 */
void led_on()
{
	GPIOC->BSRR = 1 << 13;
}

/**
 * @brief Reset GPIOC pin 13
 *
 */
void led_off()
{
	GPIOC->BRR = 1 << 13;
}

int main(void)
{
	// Initialise systick timer
	int ret = SysTick_Config(SystemCoreClock / 1000);
	if (ret < 0)
		while (1)
			;

	led_init();
	while (1)
	{
		led_on();
		delay(1000);
		led_off();
		delay(1000);
	}
}
