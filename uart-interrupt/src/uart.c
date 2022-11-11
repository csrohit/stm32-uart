#include <stm32f1xx.h>
#include <uart.h>


void putch(char c)
{
    while (!(USART1->SR & USART_SR_TXE))
        ;
    USART1->DR = 0x000000ff & c;
}

void putstr(const char *ch)
{
    uint8_t i = 0;
    while (ch[i])
    {
        putch(ch[i++]);
    }
}

void USART1_IRQHandler(void)
{
    if (USART1->SR & USART_SR_RXNE)
    {
        putch(USART1->DR & 0xff);
    }
}