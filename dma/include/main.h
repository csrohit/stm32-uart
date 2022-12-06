#ifndef __MAIN_H__

#define __MAIN_H__
int main(void);

/**
 * @brief enable clock for dma1 peripheral registers
 */
void dma1_clock_enable(void);
/**
 * @brief Configure DMA1 channel 4 to work with USART1 transmitter
 * It reads from memory and writes to USART data register
 */
void dma_usart_tx_init(void);

/**
 * @brief Configure DMA1 channel 5 to work with USART1 receiver
 * It reads from USART data register and writes to memory
 */
void dma_usart_rx_init(void);

/**
 * @brief Enable DMA to accept request for channel 4
 */
void dma_usart_tx_enable(void);

/**
 * @brief Enable DMA to accept request for channel 5
 */
void dma_usart_rx_enable(void);

/**
 * @brief Configure USART1 on PA9 and PA10
 * Enable Transmitter with DMA
 */
void usart1_init(void);

/**
 * @brief Enable USART1 prescalers and output
 */
void usart1_enable(void);

#endif