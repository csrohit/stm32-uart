#pragma once
#include <stm32f1xx.h>
#include <system.hpp>

typedef USART_TypeDef usart_t;
class USART
{
public:
    enum Feature : uint8_t{
    Transmitter,
    Receiver,
    TransmitterInterrupt,
    ReceiverInterrupt,
    TransmitterDMARequest,
    ReceiverDMARequest
};

private:
    USART_TypeDef *usart;

public:
    USART(USART_TypeDef *new_usart) : usart{new_usart} {};
    USART(const USART &old_usart) : usart{old_usart.usart} {};
    USART& operator=(const USART & p_usart);
    static void set_baudrate(usart_t * p_usart, uint32_t baud_rate);

    static void enable(usart_t *p_usart, Feature feature);
    ~USART();
};

USART::~USART()
{
}

inline USART& USART::operator=(const USART &new_usart){
    usart = new_usart.usart;
    return *this;
}



inline void set_baudrate(usart_t * p_usart, uint32_t baud_rate){
    p_usart->BRR = (uint32_t) baud_rate/Core::clock;
}

inline void USART::enable(usart_t *p_usart, Feature feature)
{
    switch (feature)
    {
    case Feature::Transmitter:
        p_usart->CR1 |= USART_CR1_TE;
        break;
    case Feature::Receiver:
        p_usart->CR1 |= USART_CR1_RE;
        break;
    case Feature::TransmitterInterrupt:
        p_usart->CR1 |= USART_CR1_TXEIE;
        break;
    case Feature::ReceiverInterrupt:
        p_usart->CR1 |= USART_CR1_RXNEIE;
        break;
    case Feature::TransmitterDMARequest:
        p_usart->CR3 |= USART_CR3_DMAT;
        break;
    case Feature::ReceiverDMARequest:
        p_usart->CR3 |= USART_CR3_DMAR;
        break;
    }
}

