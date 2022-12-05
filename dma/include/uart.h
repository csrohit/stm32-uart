#pragma once

/**
 * @brief Initialize USART peripheral
 * Enable clock source for USART peripheral and associated GPIO port
 */
static inline void USART_init(USART_TypeDef *pusart)
{
    if(pusart == USART1){
        // enable clock for GPIOA and USART1
        RCC->APB2ENR |= RCC_APB2ENR_USART1EN | RCC_APB2ENR_IOPAEN;

        // reset pin configurations for PA9 and PA10
        GPIOA->CRH &= ~(GPIO_CRH_MODE10 | GPIO_CRH_MODE9 | GPIO_CRH_CNF10 | GPIO_CRH_CNF9);

        // PA9 as Output@50Hz Alternate function
        GPIOA->CRH |= GPIO_CRH_MODE9_0 | GPIO_CRH_MODE9_1 | GPIO_CRH_CNF9_1;

        // PA10 as floating input
        GPIOA->CRH |= GPIO_CRH_CNF10_0;
    }
    
}

/**
 * @brief Enable clock for complete USART peripheral
 * 
 * @param pusart USART instance
 */
static inline USART_enable(USART_TypeDef *pusart){
    pusart->CR1 |= USART_CR1_UE;
}


/**
 * @brief Enable clock for complete USART peripheral
 * 
 * @param pusart USART instance
 */
static inline USART_disable(USART_TypeDef *pusart){
    pusart->CR1 &= ~USART_CR1_UE;
}

/**
 * @brief Enable clock for complete USART peripheral
 * 
 * @param pusart USART instance
 */
USART_set_baud(USART_TypeDef *pusart, uint32_t baudrate){
    uint32_t baud = (uint32_t)(SystemCoreClock / baudrate);
    USART1->BRR = baud;
}

/**
 * @brief Enable transmitter clock 
 * 
 * @param pusart USART instance
 */
static inline USART_tx_enable(USART_TypeDef *pusart){
    pusart->CR1 |= USART_CR1_TE;
}

/**
 * @brief Enable dma requests from transmitter
 * 
 * @param pusart USART instance
 */
static inline USART_tx_dma_enable(USART_TypeDef *pusart){
    pusart->CR3 |= USART_CR3_DMAT;
}
/**
 * @brief Enable clock for complete USART peripheral
 * 
 * @param pusart USART instance
 */
static inline USART_tx_dma_disable(USART_TypeDef *pusart){
    pusart->CR3 &= ~USART_CR3_DMAT;
}

/**
 * @brief Enable receiver buffer
 * 
 * @param pusart USART instance
 */
static inline USART_rx_enable(USART_TypeDef *pusart){
    pusart->CR1 |= USART_CR1_RE;
}

/**
 * @brief Enable clock for complete USART peripheral
 * 
 * @param pusart USART instance
 */
static inline USART_rx_interrupt_enable(USART_TypeDef *pusart){
    pusart->CR1 |= USART_CR1_TXEIE;
}

/**
 * @brief Enable clock for complete USART peripheral
 * 
 * @param pusart USART instance
 */
static inline USART_rx_dma_enable(USART_TypeDef *pusart){
    pusart->CR3 | USART_CR3_DMAR;
}

/**
 * @brief Transmit 1 character
 * 
 * @param c character to be transmitted
 */
void USART1_putch(char c);

/**
 * @brief Transmit string 
 * 
 * @param str pointer to the string
 */
void USART1_puts(const char *str);

/**
 * @brief Interrupt service routine for USART1 related interrupts
 * 
 */
void USART1_IRQHandler(void);