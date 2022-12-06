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
#include <stdint.h>
#include <stdio.h>
#include <stm32f1xx.h>

#include <time.h>
#include <uart.h>

char msg[28] = "Hello world\r\n\0";

int main(void)
{
	RCC->AHBENR |= RCC_AHBENR_DMA1EN;

	DMA1_Channel4->CPAR = (uint32_t) &USART1->DR;
	DMA1_Channel4->CMAR = (uint32_t) msg;
	DMA1_Channel4->CNDTR = 13U;
	DMA1_Channel4->CCR |= DMA_CCR_MINC | DMA_CCR_CIRC | DMA_CCR_DIR;

	  // enable clock for GPIOA and USART1
    RCC->APB2ENR |= RCC_APB2ENR_USART1EN | RCC_APB2ENR_IOPAEN;

    // reset pin configurations for PA9 and PA10
    GPIOA->CRH &= ~(GPIO_CRH_MODE10 | GPIO_CRH_MODE9 | GPIO_CRH_CNF10 | GPIO_CRH_CNF9);

    // PA9 as Output@50Hz Alternate function
    GPIOA->CRH |= GPIO_CRH_MODE9_0 | GPIO_CRH_MODE9_1 | GPIO_CRH_CNF9_1;

    // PA10 as floating input
    GPIOA->CRH |= GPIO_CRH_CNF10_0;

    uint32_t baud = (uint32_t)(SystemCoreClock / 9600);

    USART1->BRR = baud;

    USART1->CR3 |= USART_CR3_DMAT;

	DMA1_Channel4->CCR |= DMA_CCR_EN;
    // transmitter enable, receiver enable, receiver interrupt enable and USART enable
    USART1->CR1 = USART_CR1_TE | USART_CR1_RE | USART_CR1_RXNEIE | USART_CR1_UE;



    // enable USART1 interrupt
    // NVIC_EnableIRQ(USART1_IRQn);



	// USART1_init(9600U);
	
	int ret = SysTick_Config(SystemCoreClock/1000);
	if (ret < 0)
		while (1)
			;

	while (1)
	{	
		// USART1_puts(msg);
		// delay(5000U);
	}
	
	
}
