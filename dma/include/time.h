#pragma once
#include<stdint.h>

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
 * @brief Event handler for systick timer overflow event
 * As address of this function is to be inserted in the vector table, this should not be made inline
 */
void SysTick_Handler(void);