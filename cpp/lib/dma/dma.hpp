#include <stdint.h>
#pragma once
class DMA
{
public:
    constexpr static uint32_t PeripheralBase = 0x40000000UL;
    constexpr static uint32_t AHBBase = PeripheralBase + 0x00020000UL;
    constexpr static uint32_t DMA1Base = AHBBase + 0x00000000UL;

private:
    volatile uint32_t ISR;
    volatile uint32_t IFCR;

public:
};
