#pragma once

#include <stm32f1xx.h>
inline void lcd_init()
{
    RCC->APB2ENR |= RCC_APB2ENR_IOPAEN_Msk;
    GPIOA->CRL = 0x22222222;
}