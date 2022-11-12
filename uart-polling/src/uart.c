#include <stm32f1xx.h>
#include <uart.h>


void USART1_putc(char c)
{
    // wait for tx data register to be empty
    while (!(USART1->SR & USART_SR_TXE))
        ;
    USART1->DR = 0x000000ff & c;
}

void USART1_puts(const char *ch)
{
    while (*ch)
    {
        putch(*ch);
        ch++;
    }
}

void USART1_IRQHandler(void)
{
    if (USART1->SR & USART_SR_RXNE)
    {
        // this clears RXNE flag
        putch(USART1->DR & 0xff);
    }
}