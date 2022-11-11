#pragma once

// void uart_init();


static inline void USART1_init(uint32_t baudrate)
{
    // enable clock for GPIOA and USART1
    RCC->APB2ENR |= RCC_APB2ENR_USART1EN_Msk | RCC_APB2ENR_IOPAEN_Msk;

    // reset pin configurations for PA9 and PA10
    GPIOA->CRH &= ~(GPIO_CRH_MODE10 | GPIO_CRH_MODE9 | GPIO_CRH_CNF10 | GPIO_CRH_CNF9);

    // PA9 as Output@50Hz Alternate function
    GPIOA->CRH |= GPIO_CRH_MODE9_0 | GPIO_CRH_MODE9_1 | GPIO_CRH_CNF9_1;

    // PA10 as floating input
    GPIOA->CRH |= GPIO_CRH_CNF10_0;

    uint32_t baud = (uint32_t)(SystemCoreClock / baudrate);

    USART1->BRR = baud;

    // transmitter enable, receiver enable, receiver interrupt enable and USART enable
    USART1->CR1 = USART_CR1_TE | USART_CR1_RE | USART_CR1_RXNEIE | USART_CR1_UE;

    NVIC_EnableIRQ(USART1_IRQn);
}

void putch(char c);
void putstr(const char *str);