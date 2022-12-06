#include <stdio.h>
#include <stm32f1xx.h>
#include <gpio.hpp>
// #include <system.hpp>
#include <usart.hpp>

int main(void)
{
  USART::enable(USART1, USART::TransmitterDMARequest);
  // delay = 200;
  // SysTick_Config(Core::clock/1000);
  // NVIC_EnableIRQ(SysTick_IRQn);

  // GPIO::enable_port(GPIOC);
  // GPIO::setMode(GPIOC, GPIO::PIN_13,GPIO::OUTPUT_2MHZ);
  // GPIO::setConfig(GPIOC, GPIO::PIN_13,GPIO::OUTPUT_PUSH_PULL);
  // while (1)
  // {
  //   GPIO::toggle(GPIOC, GPIO::PIN_13);
  //   delay_ms(delay);
  // }
}