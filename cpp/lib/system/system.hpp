#include <stm32f1xx.h>

namespace Core
{
    uint32_t clock;
    volatile uint32_t ms_ticks;
} // namespace Core

void delay_ms(uint32_t ms)
{
    uint64_t final = ms + Core::ms_ticks;
    while (Core::ms_ticks < final)
    {
        __asm("nop");
    }
}
