#include <stm32f1xx.h>

namespace Core
{
    extern uint32_t clock;
    extern volatile uint32_t ms_ticks;
} // namespace Core

static inline void delay_ms(uint32_t ms)
{
    uint64_t final = ms + Core::ms_ticks;
    while (Core::ms_ticks < final)
    {
        __asm("nop");
    }
}
