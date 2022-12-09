#include<stdint.h>


#pragma once

class RCC
{
private:
    volatile uint32_t CR;
    volatile uint32_t CFGR;
    volatile uint32_t CIR;
    volatile uint32_t APB2RSTR;
    volatile uint32_t APB1RSTR;
    volatile uint32_t AHBENR;
    volatile uint32_t APB2ENR;
    volatile uint32_t APB1ENR;
    volatile uint32_t BDCR;
    volatile uint32_t CSR;
public:
    RCC(/* args */);
    ~RCC();
};

RCC::RCC(/* args */)
{
}

RCC::~RCC()
{
}
