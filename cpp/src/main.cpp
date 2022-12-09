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

const char *msg = "Hello, World!\r\n";
int main(void)
{
  RCC->AHBENR |= RCC_AHBENR_DMA1EN;
  DMA_Channel *tx_channel = DMA_Channel::get_instance(DMA1_Channel4);
  tx_channel->set_peripheral_address((uint32_t *)&USART1->DR);
  tx_channel->set_memory_address((uint32_t *)msg);
  tx_channel->set_transfer_direction(DMA_Channel::MemoryToPeripheral);
  tx_channel->enableMemoryIncrementMode();
  tx_channel->enableCircularMode();

  tx_channel->enable_interrupt(DMA_Channel::TransferComplete);
  tx_channel->reload(15);
  tx_channel->start();
  tx_channel->stop();
  tx_channel->start();
}