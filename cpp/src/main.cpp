/**
 * @file main.cpp
 * @author Rohit Nimkar (nehalnimkar@gmail.com)
 * @brief Main program body
 * @version 1.2
 * @date 2022-12-07
 *
 * @copyright Copyright (c) 2022
 * @attention
 *
 * This software component is licensed by Rohit Nimkar under BSD 3-Clause license,
 * the "License"; You may not use this file except in compliance with the
 * License. You may obtain a copy of the License at: opensource.org/licenses/BSD-3-Clause
 *
 */

#include <stdio.h>
#include "../include/stm32f1xx.h"
// #include <dma.hpp>
#include <dma_channel.hpp>
#include <usart.hpp>

const char *msg = "Hello, World!\r\n";
int main(void)
{

  SysTick_Config(8000);

  RCC->AHBENR |= RCC_AHBENR_DMA1EN;
  // enable clock for GPIOA and USART1
	RCC->APB2ENR |= RCC_APB2ENR_USART1EN | RCC_APB2ENR_IOPAEN;

	// reset pin configurations for PA9 and PA10
	GPIOA->CRH &= ~(GPIO_CRH_MODE10 | GPIO_CRH_MODE9 | GPIO_CRH_CNF10 | GPIO_CRH_CNF9);

	// PA9 as Output@50Hz Alternate function
	GPIOA->CRH |= GPIO_CRH_MODE9_0 | GPIO_CRH_MODE9_1 | GPIO_CRH_CNF9_1;

	// PA10 as floating input
	GPIOA->CRH |= GPIO_CRH_CNF10_0;

  USART * my_usart = USART::get_instance(USART1);
  my_usart->set_baudrate(115200);
  my_usart->enable_peripheral(USART::peripheral_t::Transmitter);
  my_usart->enable_dma_request(USART::dma_req_t::TransmitterRequest);

  DMA_Channel *tx_channel = (DMA_Channel *)0x40020044;
  tx_channel->setPeripheralAddress((uint32_t *)&USART1->DR);
  tx_channel->setMemoryAddress((uint32_t *)msg);
  tx_channel->setTransferDirection(DMA_Channel::MemoryToPeripheral);
  tx_channel->enableMemoryIncrementMode();
  tx_channel->enableCircularMode();
  tx_channel->enableInterrupt(DMA_Channel::TransferComplete);
  tx_channel->reload(15);
  tx_channel->start();

  my_usart->start();

  while (1)
  {
    delay_ms(2000);
  }
  

}