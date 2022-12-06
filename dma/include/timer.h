
#include<stdint.h>

#ifndef __TIMER_H__
#define __TIMER_H__

/**
 * @brief Stores number of systick interrupts
 * 
 */
extern volatile uint32_t msTicks;

/**
 * @brief Generate delay in milloseconds
 * 
 * @param ms number of milliseconds
 */
void delay(uint32_t ms);

/**
 * @brief Interrupt handler for systick timer
 * should not be made inline as address of this handler is to be placed in the vector table
 */
void SysTick_Handler(void);

#endif