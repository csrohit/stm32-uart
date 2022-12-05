#include<stm32f1xx.h>

class USART
{
private:
    USART_TypeDef * usart;
public:
    USART(USART_TypeDef *new_usart):usart{new_usart}{};
    USART(const USART& old_usart):usart{old_usart.usart}{};
    void enable(void);
    void enable(void);
    ~USART();
};


USART::~USART()
{
}
