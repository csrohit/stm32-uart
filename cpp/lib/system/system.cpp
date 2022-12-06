#include<system.hpp>


uint32_t Core::clock = 8000000U;
volatile uint32_t Core::ms_ticks = 0;

void SysTick_Handler(void){
    Core::ms_ticks ++;
}
